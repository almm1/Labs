#include "pch.h"
#include <stdio.h>
#include <string.h> 
#include <windows.h>


int main(int argc, char* argv[])
{
	FILE *fpin = NULL;
	FILE *sl;

	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	char filename[100] = { 0 }; // путь до файла
	char line[1024];
	char string[184];
	int pos_w[30];
	char word[30];
	int cnt = 0;
	int n = 0;
	char *ptr;
	char *p=string;
	int flag = 0;
	char *str=word;

/*
	if (argc == 2)
		strcpy(filename, argv[1]);
	else
	{
		do
		{
			printf("Please enter a address file : ");
			gets_s(filename);

			if ((fpin = fopen(filename, "r")) == NULL) //Открытие файла для чтения 
			{
				printf("Cannot open input file.\n");
			}
		} while (fpin == NULL);
	}*/

	fpin = fopen("test.txt", "r");// результирующий файл
	if (fpin == NULL)
		return 0;

	sl = fopen("slova.txt", "r");
	if (sl == NULL)
		return 0;


	while (!feof(sl))
	{
		*p=fgetc(sl);
		if (*p == ' ')
		{
			*p = '\0';
			flag = 1;
		}
		else if (flag != 0)
		{
			pos_w[n++]= cnt;
			flag = 0;
		}
		cnt++;
		*p++;
	}
	n = 0;
	cnt = 0;
	flag = 0;
	while (!feof(fpin))
	{
		ptr = fgets(line, 1024, fpin);

		if (ptr == NULL)
			break;

		for (int i = 0; *(ptr + i) != '\0'; i++)
		{
			SetConsoleTextAttribute(hConsoleHandle, 15);
			for (n = 0; (*(ptr + i) >= 'a' && *(ptr + i) <= 'z'); n++)
			{
				if (flag == 0)
				{
					flag = 1;
					cnt = i;
				}
					*(str + n) = *(ptr + i);
					i++;
			}
			if (flag == 1)
			{
				flag = 0;
				for (int j = 0; j < 29; j++)
				{
					if (strcmp(word, &string[pos_w[j]]) == 0)
						flag = 1;
				}
			}

		}
	}
}