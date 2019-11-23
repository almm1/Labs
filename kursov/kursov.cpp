#include "pch.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>

#define MAXLINE 1024

void replenishment()
{

}

void editing()
{

}

void deleting()
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

	printf("Выберете действие: \n");
	printf("1 - Пополнение базы \n");
	printf("2 - Редактирование базы \n");
	printf("3 - Удаление записей \n");
	printf("4 - Подбор маршрута с наименьшим временем ожидания при пересадке \n");
	printf("5 - Подбор маршрута с наименьшей стоимостью \n");
	scanf("%d", &number);

	if ((number < 1) && (number > 5))
		printf("Ошибка. Выбрано несуществующее действие");
	switch (number)
	{
	case 1:
		replenishment();
		break;
	case 2:
		editing();
		break;
	case 3:
		deleting();
		break;
	case 4:
		printf("в разработке");
		break;
	case 5:
		printf("в разработке");
		break;
	}
	return 0;
}
