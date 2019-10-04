#include "pch.h"
#include <iostream>
#include <stdio.h>

#define MAXLINE 1024

int main()
{
	FILE *fpin;
	FILE *fpout;

	char line[MAXLINE];
	char *ptr;

	fpin = fopen("test.txt", "a+");
	if (fpin == NULL)
		return 0;

	fpout = fopen("result.txt", "w+");
	if (fpout == NULL)
		return 0;

	while (!feof(fpin))
	{
		ptr = fgets(line, MAXLINE, fpin);

		if (ptr == NULL)    
		break;

		while (*ptr != '\0')
		{
			if (*ptr == ' ' || *ptr == '.' || *ptr == ',' || *ptr == '\n' || *ptr =='\0')
			{
				
			}
		}
	}
}