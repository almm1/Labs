#include "pch.h"
#include <stdio.h>
#include <string.h> 
#include <windows.h>

void zero(char str[])
{
	for (int i = 0; i < 30; i++)
		str[i] = '\0';
}

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
	int begin = 1;
	int end = 1;
	char *str=word;
	int found = 0;

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
	int z = 0;
	flag = 0;
	while (!feof(fpin))
	{
		ptr = fgets(line, 1024, fpin);

		if (ptr == NULL)
			break;
		z = 0;
		while (cnt != 3)
		{
			for (int i = z; *(ptr + i) != '\0'; i++)
			{
				zero(word);
				for (n = 0; (*(ptr + i) >= 'a' && *(ptr + i) <= 'z'); n++)
				{
					if (flag == 0)
					{
						flag = 1;
						begin = i;
					}
					*(str + n) = *(ptr + i);
					i++;
					end = i;
				}
				if (flag == 1)
				{
					flag = 0;
					for (int j = 0; j < 29; j++)
					{
						if (strcmp(word, &string[pos_w[j]]) == 0)
						{
							found = 1;
							break;
						}
					}
				}
				if (found == 1)
					break;
			}
			SetConsoleTextAttribute(hConsoleHandle, 15);
			for (int i = z; i<end; i++)
			{
				if (found == 1)
				{
					if (i == begin)
						SetConsoleTextAttribute(hConsoleHandle, 10);
				}
				printf("%c", *(ptr + i));
			}
			z = end;
			cnt++;
			found = 0;
			begin = 1;
			flag = 0;
		}
		SetConsoleTextAttribute(hConsoleHandle, 15);
		for(int i = end; *(ptr+i)!='\0';i++)
			printf("%c", *(ptr + i));

		found = 0;
		begin = 1;
		end = 1;
		flag = 0;
		cnt = 0;
	
	}
}