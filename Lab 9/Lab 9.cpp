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
	char filename[100] = {0}; // путь до файла
	char *ptr;
	int cnt = 0; //счетчик слов
	int cnt_2 = 0;
	int numberStr = 0; //номер большой строки
	int rez = 0; //резерв
	int flag = YES; //признак лишних символов


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

	fpout = fopen("result.txt", "w+");// результирующий файл
	if (fpout == NULL)
		return 0;

	while (!feof(fpin))//пока не конец файла
	{
		ptr = fgets(line, MAXLINE, fpin);// считывание строки из файла
		numberStr++;

		if (ptr == NULL)    
		break;

		while (*ptr != '\0')// до конца строки
		{
			if (*ptr == ' ')// до разделитель
			{
				if (flag == YES)
				{
					cnt++;//счетчик слов
				}
				flag = YES;
			}
			if ((*ptr < 'a' || *ptr > 'z') && (*ptr < 'A' || *ptr > 'Z'))
			{
				flag = NO;
			}
			ptr++;//передвижение указателя
		}
		if (cnt > cnt_2)// сравнения строк
		{
			cnt_2 = cnt;
			rez = numberStr;//запись номера строки в резерв
		}
		cnt = 0;//обнуления счетчика слов
	}

	numberStr = 0;// обнуление позиции строки
	rewind(fpin);// перемещение в начало файла
	
	while (!feof(fpin))
	{
		ptr = fgets(line, MAXLINE, fpin);
		numberStr++;

		if (rez != numberStr)
		fputs(line, fpout);// запись в результирующий файл
	}
	rez = 0;
	fclose(fpin);  //закрытие
	fclose(fpout); //файлов
	return 0;
}