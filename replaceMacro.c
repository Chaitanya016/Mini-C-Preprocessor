#include "header.h"

void replaceMacro(char **data,char **s,char *name, char *body ,int * size)
{
	int i,j,k,f;

	/*printf("Executiiing macro function\n");
	  printf("MacroName : %s\n",name);
	  printf("MacroBody : %s\n",body);*/

	int op = 0, m = 0;
	*s = realloc(*s , *size + 1);

	if(strchr(name,'('))
		op = 1;

	if(op == 0)    // macro without arguments replacement
	{
		for(i = 0,m = 0,f = 0; data[0][i] ; i++,m++)
		{
			if(data[0][i] == '"')  // if inside string macroname found dont replace it
				f++;
			if(f == 0)
			{
				if(i > 0)
					if((data[0][i-1] >= 'a' && data[0][i-1] <= 'z') || (data[0][i-1] >= 'A' && data[0][i-1] <= 'Z')) // if middle word dont replace
						goto l;

				for(j = 0,k = i; name[j] ; j++,k++)
					if(data[0][k] != name[j])  // comparing body with word
						break;

				if(name[j] == 0 && ((data[0][k] > 0 && data[0][k] < 47) || (data[0][k] > 57 && data[0][k] < 65) || (data[0][k] > 90 && data[0][k] < 97) || (data[0][k] > 122))) // if not middle word then proceed
				{
					int lenBody = strlen(body);  
					int lenName = strlen(name);
					*size += lenBody - lenName + 1; // calculating length and size based on that allocating memory 

					*s = realloc(*s, *size * sizeof(char));  // reallocating memory

					for(j = 0; body[j]; j++)    
						s[0][m++] = body[j];  // replacement of macros
					m--;
					i = k - 1;
					continue;
				}
			}
l:	
			s[0][m] = data[0][i];   // normal copying data into temp buff

			if(f == 2)
				f = 0;
		}
	}
	else if(op == 1)  // macro with arguments replacement
	{
		for( i = 0,m = 0,f = 0; data[0][i]; i++,m++)
		{
			if(data[0][i] == '"') // if inside string dont replace it 
				f++;
			if(f == 0)
			{
				if(i > 0)
					if((data[0][i-1] >= 'a' && data[0][i-1] <= 'z') || (data[0][i-1] >= 'A' && data[0][i-1] <= 'Z')) // if middle word dont replace it
						goto v;
				for(j = 0,k = i; name[j]; j++,k++)
					if(data[0][k] == name[j]) 
					{
						if(name[j] == '(')
							break;
					}
					else
						break;

				if(name[j] == '(')// && ((name[j+1] != data[0][k+1]) || (name[j+2] != data[0][k+2]) ))  // if all name is matching then start replacing
				{
					char *tBody = replaceArguments(*data + k, name , body);  // changing formal arg into original argument
					int lenName = strlen(name);
					int lenBody = strlen(body);
					*size += lenBody - lenName +1;
					*s = realloc(*s , *size * sizeof(char)); // reallocating memory to add more data

					for(j = 0; tBody[j]; j++)
						s[0][m++] = tBody[j];  // replacing macro with arguments
					m--;
					k++;
					for(int c = 1 ; data[0][k] ; k++) {  // upto macro change index
						if(data[0][k] == '(')
							c++;
						if(data[0][k] == ')')
							c--;
						if(c == 0)
							break;
					}
					i = k;
					free(tBody);
					continue;
				}
			}
v:
			s[0][m] = data[0][i]; // normal copying data

			if(f == 2)
				f = 0;
		}
	}
	s[0][m] = 0;

	*data = realloc(*data, (*size + 1) * sizeof(char));  // reallocating memory for original data string
	i = 0;
	while(s[0][i])  
	{
		data[0][i] = s[0][i]; // copying temp string to original string
		i++;
	}
	data[0][i] = s[0][i];
	int length = strlen(*data);
	*data = realloc(*data , length + 1);  // reallocating based on length main data

	for(i = 0; name[i]; i++)
		name[i] = 0;
	for(i = 0; body[i];i++)
		body[i] = 0;

	free(*s);
}

char * replaceArguments(char *data, char *name , char *body)
{
	int i, j, f = 0;

	/*	for(i = 0; name[i] ; i++)   // counting arguments count
		{
		if(name[i] == '(')
		f = 1;
		if(f == 1)
		if((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z'))
		arg++;
		}*/

      /*printf("Name = %s\n",name);
	  printf("body = %s\n",body);
	  printf("data = %s\n",data);
        */

	arg *head=0;
	arg *prev;
	int c = 0, k;

     /* storing formal parameters in struct */

	for(i = 0, f = 0 ; name[i] ; i++)
	{
		if(name[i] == '(') {
			c = 1;
			continue;
		}
		if(c == 0)
			continue;
		if(f == 0)
			if((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z') || name[i] == '_')
				f = 1;

		if(name[i] == ')')
			break;

		if(f == 1)
		{
			int k = 0;
			arg *new = calloc(1, sizeof(arg)); // creating new based on parameter count

			for(j = i ; (name[j] >= 'a' && name[j] <= 'z') || (name[j] >= 'A' && name[j] <= 'Z') || (name[j] >= '0' && name[j] <= '9') ; j++ , k++) 
				new->formal[k] = name[j];

			i = j - 1;
			f = 0;

			if(head == 0) {
				head = new;
				prev = new;
			}
			else {
				prev->next = new;
				prev = new;
			}
		}
	}

	arg *p = head;

	for(i = 0, f = 0, c = 0; data[i] ; i++) {
		if(f == 0)
			if(data[i] == '(') {
				f = 1;
				continue;
			}
		if(data[i] == ')')
			break;
		if(f == 1) {
			for(j = i, k = 0, c = 0; data[j] ; j++,k++) {     // storing actual parameter
				if(data[j] == '(')
					c++;
				if(data[j] == ')')
					c--;
				if(data[j] == ',')
					if(c == 0)
						break;
				if(c < 0)
					break;
				p->actual[k] = data[j];
			}
			i = j;
			p = p->next;
			if(p == 0)
				break;
		}
	}

	p = head;

	/*while(p) {
	  printf("Formal = %s\n",p->formal);
	  printf("Actual = %s\n",p->actual);
	  p = p->next;
	  }*/

	char *tBody = 0;

	p = head;
	int allocation = 1;
	int Index = 0;
	int len;
	for( i = 0 ; body[i] ; i++) {
		p = head;
		f = 0;
		while(p) {
			int k = 0;
			for( j = i; p->formal[k] && body[j] ; k++,j++)
				if(p->formal[k] != body[j])
					break;

			if(p->formal[k] == 0) {
				for(j = 0; p->actual[j] ; j++) {    // replacing the arguments in main
					tBody = realloc(tBody , allocation * sizeof(char));
					tBody[Index] = p->actual[j];
					allocation++;
					Index++;
				}
				len = strlen(p->formal);
				i += len - 1;
				f = 1;
				break;
			}
			p = p->next;
		}
		if(f == 0) {
			tBody = realloc(tBody , allocation * sizeof(char));
			tBody[Index] = body[i];
			allocation++;
			Index++;
		}
	}

	len = strlen(tBody);
	//printf("Length = %d\n",len);

	tBody = realloc(tBody, allocation * sizeof(char));
	tBody[Index] = '\0';

	/*printf("SOMETHING IS THERE \n\n\n");
	  for( i = 0 ; tBody[i] ; i++)
	  printf("%c -> %d\n",tBody[i],tBody[i]);
	  printf("%c -> %d\n",tBody[i],tBody[i]); */

	p = head;
	//printf("\n\n%s\n\n",tBody);

	while(p) {
		head = p->next;
		free(p);
		p = head;
	}

	return tBody;

}



/*
   for(j = 0,i = 0,f = 0; name[i] ; i++) // storing formal arguments in one arry
   {
   if(name[i] == '(')
   f = 1;
   if(f == 1)
   if((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z'))
   formalArg[j++] = name[i];
   }

   for(j = 0,i = 0,f = 0; data[i] ; i++)  // storing actual arguments in one arry
   {
   if(data[i] == '(')
   f = 1;
   if(f == 1)
   for( i ; data[i] != ')' ; i++) {
   if(actualArg == 0) {
   actualArg = calloc(2, sizeof(char));
   actualArg[0] = data[i];
   }
   else {
   int len = strlen(actualArg);
   actualArg = realloc(actualArg, (len + 2) * sizeof(char));
   actualArg[len-1] = data[i];
   }
   }
//if((data[i] >= 'a' && data[i] <= 'z') || (data[i] >= 'A' && data[i] <= 'Z') || (data[i] >= '0' && data[i] <= '9'))
if(data[i] == ')')
break;
}

//printf("Formal : %s\n",formalArg);
//printf("Actual : %s\n",actualArg);

int len = strlen(body);

char *tBody = calloc(len + 1 , sizeof(char));

strcpy(tBody , body); // copying body into one temporary arry

for(i = 0; tBody[i] ; i++)
for(j = 0; formalArg[j] ;j++)
if(formalArg[j] == tBody[i])     // modifying formal to actual arg in body
tBody[i] = actualArg[j];
for( i = 0,f = 0 ; formalArg[i] ; i++)
{
for(j = 0 ; tBody[j] ; j++)
if(tBody[j] == formalArg[i])
{
int c = 0,k = 0;
while( c < f)
{
if(actualArg[k] == ',' || actualArg[k] == 0)
c++;
k++;
}
int len = strlen(tBody);


//free(formalArg);
//free(actualArg);
//return tBody;
}
}
free(formalArg);
free(actualArg);
return tBody;
}*/


