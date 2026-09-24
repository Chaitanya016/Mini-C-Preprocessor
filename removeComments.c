#include "header.h"

void removeComments(char *s)   // removing comments 
{
	int i = 0;

	for(i = 0 ; s[i] ;i++)
	{
		if(s[i] == '/')
		{
			if(s[i+1] == '/')
			{
				while(s[i] != '\n' && s[i])  // removing single line comment
					s[i++] = 32;
				continue;
			}
			if(s[i+1] == '*')
			{
				while(s[i])   // removing multi line comment
				{
					if(s[i] == '*')
						if(s[i+1] == '/')
						{
							s[i] = 32;
							s[i+1] = 32;

							break;
						}
					if(s[i] == '\n')
					{
						i++;
						continue;
					}
					s[i++] = 32;
				}
			}
		}
	}
}

