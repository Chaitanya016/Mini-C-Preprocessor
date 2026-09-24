#include "header.h"

void headerInclusion(FILE * Main,char *file,int size)  // Header file Inclusion
{
	char *s = malloc(size + 1);
	char path[100] = "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/";
	char h[30];
	int i = 0,j = 0,len,k = 0;
	int ch;
	char f = 0;

	FILE *temp = fopen(file,"r");

	if(temp == 0)
	{
		printf("In Header : file is not present\n");
		return;
	}

	len = strlen(path);

	while(fgets(s,size + 1,temp)) 
	{
		if(strstr(s,"main"))  
			break;
		if(!strstr(s,"#include"))
			goto l;
		for(i = 0,j = 0,k = len,f = 0; s[i] ; i++)
		{
			if(f == 1 && s[i] == '>')
				break;
			if(f == 1)
				path[k++] = s[i];
			if(f == 2 && s[i] == '"')
				break;
			if(f == 2)
				h[j++] = s[i];
			if(s[i] == '<')
				f = 1;
			if(s[i] == '"')
				f = 2;
		}
		if(f == 1)
		{
			path[k] = 0;
			if(!strstr(s,"#include"))
				continue;
			FILE *fp = fopen(path,"r");
			if(fp == 0)
			{
				printf("%s header file is not present\n",path);
				continue;
			}
			while((ch = fgetc(fp)) != EOF)
			fputc(ch, Main);
			fclose(fp);
			continue;
		}
		if(f == 2)
		{
			h[j] = 0;
			if(!strstr(s,"#include"))
				continue;
			UserDefinedHeader(Main , h , size);   // User defined headerfile inclusion
			continue;
			/*
			   FILE *fp = fopen(h,"r");
			   if(fp == 0)
			   {
			   printf("%s header file is not present\n",h);
			   continue;
			   }
			   while((ch = fgetc(fp)) != EOF)  // including userdefined header inclusion
			   fputc(ch,Main);

			   fclose(fp);*/
		}
l:
		if(strstr(s,"#define"))
			continue;
		if(strstr(s,"main()"))
			break;
		for(int i = 0; s[i] ; i++)
			fputc(s[i] , Main);

	}
	fclose(temp);
	free(s);
}


void UserDefinedHeader(FILE * Main, char *file, int size)
{
	//printf("USER DEFined eXexuted\n");
	char *s = malloc(size + 1);
	char path[100] = "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/";
	char h[30];
	int i = 0,j = 0,len,k = 0;
	int ch;
	char f = 0;

	FILE *temp = fopen(file,"r");

	if(temp == 0)
	{
		printf("In Header : file is not present\n");
		return;
	}

	len = strlen(path);

	while(fgets(s,size + 1,temp)) 
	{
		if(!strstr(s,"#include"))
			goto l;	
		for(i = 0,j = 0,k = len,f = 0; s[i] ; i++)
		{
			if(f == 1 && s[i] == '>')
				break;
			if(f == 1)
				path[k++] = s[i];
			if(f == 2 && s[i] == '"')
				break;
			if(f == 2)
				h[j++] = s[i];
			if(s[i] == '<')
				f = 1;
			if(s[i] == '"')
				f = 2;
		}
		if(f == 1)
		{
			path[k] = 0;
			if(!strstr(s,"#include"))
				continue;
			FILE *fp = fopen(path,"r");
			if(fp == 0)
			{
				printf("%s header file is not present\n",path);
				continue;
			}
			while((ch = fgetc(fp)) != EOF)  // including predefined header inclusion
				fputc(ch,Main);
			continue;
			fclose(fp);
		}
l:
		for(int i = 0 ; s[i] ; i++)
			fputc(s[i] ,Main);
	}
	free(s);
}



