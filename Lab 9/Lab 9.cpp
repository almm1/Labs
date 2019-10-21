#include "pch.h"
#include <iostream>
#include <stdio.h>

#define YES 1
#define NO 0
#define MAXLINE 1024

int main(int argc, char* argv[])
{
	FILE *fpin;
	FILE *fpout;

	char line[MAXLINE];
	char filename[100] = {0};
	char *ptr;
	int cnt = 0;
	int cnt_2 = 0;
	int numberStr = 0;
	int rez = 0;
	int flag = YES;


	if (argc == 2)
		strcpy(filename, argv[1]);
	else {
	tr:
		printf("Please enter a address file : ");
		gets_s(filename);
	}
	if ((fpin = fopen(filename, "r")) == NULL) //Открытие файла для чтения 
	{
		printf("Cannot open input file.\n");
		goto tr;
	}

	fpout = fopen("result.txt", "w+");
	if (fpout == NULL)
		return 0;

	while (!feof(fpin))
	{
		ptr = fgets(line, MAXLINE, fpin);
		numberStr++;

		if (ptr == NULL)    
		break;

		while (*ptr != '\0')
		{
			if (*ptr == ' ')
			{
				if (flag == YES)
				{
					cnt++;
				}
				flag = YES;
			}
			if ((*ptr < 'a' || *ptr > 'z') && (*ptr < 'A' || *ptr > 'Z'))
			{
				flag = NO;
			}
			ptr++;
		}
		if (cnt > cnt_2)
		{
			cnt_2 = cnt;
			rez = numberStr;
		}
		cnt = 0;
	}

	numberStr = 0;
	rewind(fpin);
	
	while (!feof(fpin))
	{
		ptr = fgets(line, MAXLINE, fpin);
		numberStr++;

		if (rez != numberStr)
		fputs(line, fpout);
	}
	rez = 0;
	fclose(fpin);
	fclose(fpout);
	return 0;
}