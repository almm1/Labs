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
	int cnt = 0;
	int cnt_2 = 0;
	int numberStr = 0;
	int rez = 0;

	fpin = fopen("test.txt", "a+");
	if (fpin == NULL)
		return 0;

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
				cnt++;
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
	fclose(fpin);
	fclose(fpout);
}