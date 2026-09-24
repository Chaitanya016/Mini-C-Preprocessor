#include "header.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("USAGE: ./my_preprocessor src_file\n");
        return 1;
    }

    /* Create output filename */
    int lenn = strlen(argv[1]);

    if (lenn < 2)
    {
        printf("Invalid source filename\n");
        return 1;
    }

    char *iFile = calloc(lenn + 1, sizeof(char));
    if (iFile == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    strcpy(iFile, argv[1]);

    /* Change .c to .i */
    iFile[lenn - 1] = 'i';

    /*
     * First check whether the input file exists.
     * Do NOT create the output file before this check.
     */
    FILE *fpp = fopen(argv[1], "r");

    if (fpp == NULL)
    {
        printf("File is not present\n");
        free(iFile);
        return 1;
    }

    /* Find source file size */
    if (fseek(fpp, 0, SEEK_END) != 0)
    {
        printf("Unable to determine file size\n");
        fclose(fpp);
        free(iFile);
        return 1;
    }

    int size = (int)ftell(fpp);

    if (size < 0)
    {
        printf("Unable to determine file size\n");
        fclose(fpp);
        free(iFile);
        return 1;
    }

    fclose(fpp);

    /*
     * Now create the output .i file.
     */
    FILE *Main = fopen(iFile, "w");

    if (Main == NULL)
    {
        printf("Unable to create output file\n");
        free(iFile);
        return 1;
    }

    free(iFile);

    /* Open source file for reading */
    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL)
    {
        printf("File is not present\n");
        fclose(Main);
        return 1;
    }

    /*
     * fgetc() returns int because it must be able to represent
     * every character plus EOF.
     */
    int ch;

    char *data = calloc((size_t)size + 1, sizeof(char));

    if (data == NULL)
    {
        printf("Memory allocation failed\n");
        fclose(fp);
        fclose(Main);
        return 1;
    }

    int i = 0;
    int longLine = 0;
    int c = 0;

    while ((ch = fgetc(fp)) != EOF)
    {
        c++;
        data[i++] = (char)ch;

        if (ch == '\n')
        {
            if (c > longLine)
                longLine = c;

            c = 0;
        }
    }

    data[i] = '\0';

    /* Remove comments */
    removeComments(data);

    /* Create temporary file */
    FILE *ft = fopen("t", "w");

    if (ft == NULL)
    {
        printf("Unable to create temporary file\n");
        free(data);
        fclose(fp);
        fclose(Main);
        return 1;
    }

    i = 0;

    while (data[i])
        fputc(data[i++], ft);

    fclose(ft);

    /* Include header files */
    headerInclusion(Main, "t", (int)size);

    /* Open temporary file for macro processing */
    FILE *ftt = fopen("t", "r");

    if (ftt == NULL)
    {
        printf("Unable to open temporary file\n");
        free(data);
        fclose(fp);
        fclose(Main);
        remove("t");
        return 1;
    }

    char *line = calloc((size_t)longLine + 1, sizeof(char));
    char *s = calloc((size_t)size + 1, sizeof(char));
    char *name = calloc((size_t)longLine + 1, sizeof(char));
    char *body = calloc((size_t)longLine + 1, sizeof(char));

    if (line == NULL || s == NULL || name == NULL || body == NULL)
    {
        printf("Memory allocation failed\n");

        free(data);
        free(line);
        free(s);
        free(name);
        free(body);

        fclose(fp);
        fclose(Main);
        fclose(ftt);

        remove("t");

        return 1;
    }

    int j = 0;
    int k = 0;
    int f = 0;
    int len = 0;
    int flag = 0;
    int m = 0;
    int Index = 0;

    /*
     * Replace macros
     */
    while (fgets(line, longLine + 1, ftt))
    {
        if (strstr(line, "#define"))
        {
            if (strstr(data, line))
            {
                for (i = 0, k = 0, f = 0, j = 0, flag = 0, m = 0;
                     line[i];
                     i++)
                {
                    if (f == 0)
                    {
                        if (line[i] == ' ')
                            m = 1;

                        if (m == 1)
                        {
                            if ((line[i] >= 'a' && line[i] <= 'z') ||
                                (line[i] >= 'A' && line[i] <= 'Z') ||
                                line[i] == '_' ||
                                (line[i] >= '0' && line[i] <= '9'))
                            {
                                f = 1;
                            }
                        }
                    }

                    if (f == 1)
                    {
                        if (line[i] == '(')
                            flag = 1;

                        if (flag == 0)
                        {
                            if (line[i] == ' ')
                            {
                                f = 2;
                                continue;
                            }
                        }

                        if (flag == 1)
                        {
                            if (line[i] == ')')
                                flag = 0;
                        }

                        name[j++] = line[i];
                    }

                    if (f == 2)
                    {
                        if (line[i] == '\n')
                            continue;

                        body[k++] = line[i];
                    }
                }

                name[j] = '\0';
                body[k] = '\0';

                replaceMacro(&data, &s, name, body, &size);
            }
        }
    }

    /*
     * Locate main() so that the generated .i file
     * contains the processed source from main().
     */
    len = strlen(data);

    if (len > 0)
    {
        data[len] = '\0';
    }

    char st[20] = "main(";

    for (i = 0, Index = 0, f = 0; data[i]; i++)
    {
        if (data[i] == '\n')
            Index = i + 1;

        for (j = 0, k = i; st[j]; j++, k++)
        {
            if (st[j] != data[k])
                break;
        }

        if (st[j] == '\0')
        {
            f = 1;
            break;
        }
    }

    if (f == 1)
        i = Index;
    else
        i = 0;

    while (data[i])
        fputc(data[i++], Main);

    /* Cleanup */
    free(name);
    free(body);
    free(line);

    remove("t");

    fclose(fp);
    fclose(Main);
    fclose(ftt);

    return 0;
}