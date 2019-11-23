#include "pch.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 100

void replenishment(FILE *file)
{
	printf("- Пополнение базы данных -");
	printf("");
	printf("");
	printf("");
}

void editing(FILE *file)
{

}

void deleting(FILE *file)
{

}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	FILE *f = NULL; 

	char filename[100] = { 0 };
	char *ptr;
	char line[MAXLINE];
	int number;

	if (argc == 2)
		strcpy(filename, argv[1]);
	else
	{
		do
		{
			printf("Please enter a address file : ");
			gets_s(filename);

			if ((f = fopen(filename, "r+")) == NULL) //Открытие файла для чтения 
			{
				printf("Cannot open input file.\n");
			}
		} while (f == NULL);
	}

	printf("\nВыберете действие: \n");
	printf("1 - Пополнение базы \n");
	printf("2 - Редактирование базы \n");
	printf("3 - Удаление записей \n");
	printf("4 - Подбор маршрута с наименьшим временем ожидания при пересадке \n");
	printf("5 - Подбор маршрута с наименьшей стоимостью \n");
	printf("0 - Выход \n\n");
	scanf("%d", &number);

	if ((number < 0) && (number > 5))
		printf("Ошибка. Выбрано несуществующее действие");
	switch (number)
	{
	case 1:
		replenishment(f);
		system("CLS");
		break;
	case 2:
		editing(f);
		system("CLS");
		break;
	case 3:
		deleting(f);
		system("CLS");
		break;
	case 4:
		printf("в разработке");
		break;
	case 5:
		printf("в разработке");
		break;
	case 0:
		return 0;
	}
	return 0;
}
