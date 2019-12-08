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
	char string[184];//строка содержащая данные из файла "slova"
	int pos_w[30]; //позиции первых символов в строке string
	char word[30]; //строка для храния слов
	int cnt = 0; 
	int n = 0;
	char *ptr=0;
	char *p=string;
	int flag = 0;
	int begin = 1;//позиция начала слова
	int end = 1;//позиция конца слова
	char *str=word;
	int z = 0;//запоминатель для конца слова
	int found = 0;//признак совпадения слова с ключевым словом
	int f_counter = 0;//считчик символов в строке
	char c=0;// просто символ

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
	}


	sl = fopen("slova.txt", "r");//открытия фала где хранятся ключевые слова
	if (sl == NULL)
		return 0;


	while (!feof(sl))
	{
		*p=fgetc(sl);//посимвольное считывание
		if (*p == ' ')
		{
			*p = '\0';//пробелы заменяются на символ конца строки
			flag = 1;
		}
		else if (flag != 0)//если первый символ после пробела
		{
			pos_w[n++]= cnt;// запоминается позиция этого слова
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
		found = 0;
		begin = 1;
		end = 1;
		flag = 0;
		cnt = 0;
		z = 0;
		c = 1;
		free(ptr);
		f_counter = 0;
		
		while (c != '\n')
		{
			c = fgetc(fpin);
			f_counter++;
		}

		fseek(fpin, -f_counter-1, SEEK_CUR);
		ptr = (char*)malloc((f_counter+2) * sizeof(char));
		fgets(ptr, f_counter+2, fpin);
		if (ptr == NULL)
			break;

		while (cnt != 10)
		{
			for (int i = z; *(ptr + i) != '\0'; i++)//рассматириваем строку
			{
				zero(word);//обнуление массива со словами
				for (n = 0; (*(ptr + i) >= 'a' && *(ptr + i) <= 'z'); n++)// если символы буквы, то они записываются как слово
				{
					if (flag == 0)
					{
						flag = 1;
						begin = i;//запоминание начала слова
					}
					*(str + n) = *(ptr + i);
					i++;
					end = i;//запоминание конца слова
				}
				if (flag == 1)//если есть слово
				{
					flag = 0;
					for (int j = 0; j < 29; j++)
					{
						if (strcmp(word, &string[pos_w[j]]) == 0)//сравниваем слово на совпадение с ключевыми словами
						{
							found = 1;//признак совпадения
							break;
						}
					}
				}
				if (found == 1)// если есть совпадение, выход из цикла
					break;
			}
			SetConsoleTextAttribute(hConsoleHandle, 15);//белый цвет шрифта
			for (int i = z; i<end; i++)//от позиции начала строки или предыдущего слова до конца текущего слова
			{
				if (found == 1)//если было совпадение
				{
					if (i == begin)//при начале слова
						SetConsoleTextAttribute(hConsoleHandle, 10);//зеленый цвет
				}
				printf("%c", *(ptr + i));//вывод символов на экран
			}
			z = end;//запоминание конца предыдущего слова 
			cnt++;
			found = 0;
			flag = 0;
		}
		SetConsoleTextAttribute(hConsoleHandle, 15);
		for(int i = end; *(ptr+i)!='\0';i++)//вывод остатка слова
			printf("%c", *(ptr + i));	
	}
	free(ptr);
	return 0;
}