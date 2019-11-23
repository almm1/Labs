﻿#include "pch.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 150



FILE *file;

void replenishment()
{ 
	file = fopen("base.txt", "r+");
	char line[MAXLINE];
	char destination[34] = { '\0' };
	char time_d[6] = { '\0' };
	char time_a[6] = { '\0' };
	char price[11] = { '\0' };
	char *ptr;
	char *l;
	int i = 0;
	int flag = 0;
	int cnt = 0;

	do
	{
		l = fgets(line, MAXLINE, file);
	} while (*l == ' ');

	printf("- Пополнение базы данных -\n");
	printf("Введите пункт прилета: ");	
	scanf("%s", &destination);
	i = 4;
	ptr = destination;
	

	while (*ptr != '\0')
	{
		*(l + i) = *ptr;
		*(l++)+i;
		*ptr++;
	}

	do
	{
		printf("\nВведите время вылета в фромате '00:00': ");
		scanf("%s", &time_d);
		ptr = time_d;
			if ((*ptr >= '0' && *ptr <= '9') && (*(ptr+1) >= '0' && *(ptr+1) <= '9') && (*(ptr+3) >= '0' && *(ptr+3) <= '9') && (*(ptr+4) >= '0' && *(ptr+4) <= '9') && (*(ptr+2) == ':'))
			{
				flag = 1;
			}
			else
			printf("Неверный формат\n");
	} while (flag==0);
	i = 33;
	while (*ptr != '\0')
	{
		*(l + i) = *ptr;
		*(l++) + i;
		*ptr++;
	}

	do
	{
		printf("\nВведите время прилета в фромате '00:00': ");
		scanf("%s", &time_a);
		ptr = time_a;
		if ((*ptr >= '0' && *ptr <= '9') && (*(ptr + 1) >= '0' && *(ptr + 1) <= '9') && (*(ptr + 3) >= '0' && *(ptr + 3) <= '9') && (*(ptr + 4) >= '0' && *(ptr + 4) <= '9') && (*(ptr + 2) == ':'))
		{
			flag = 1;
		}
		else
			printf("Неверный формат\n");
	} while (flag == 0);
	i = 44;
	while (*ptr != '\0')
	{
		*(l + i) = *ptr;
		*(l++) + i;
		*ptr++;
	}

	printf("\nВведите стоимость билета: ");
	scanf("%s", &price);
	ptr = price;
	i = 55;

	while (*ptr != '\0')
	{
		*(l + i) = *ptr;
		*(l++) + i;
		*ptr++;
	}
	*(l + i + 1) = ' ';
	*(l + i + 2) = 'r';
	*(l + i + 3) = 'u';
	*(l + i + 4) = 'b';

	fseek(file, 88, SEEK_SET);
	fputs(line, file);
}

void editing()
{

}

void deleting()
{

}

int main()
{
	setlocale(LC_ALL, "Russian");

	FILE *f = NULL; 

	int number;


	system("CLS");
	printf("Выберете действие: \n");
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
		replenishment();
		system("CLS");
		break;
	case 2:
		editing();
		system("CLS");
		break;
	case 3:
		deleting();
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
