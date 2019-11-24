#include "pch.h"
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
	char blank[87] = {NULL};
	char destination[34] = { '\0' };
	char time_d[6] = { '\0' };
	char time_a[6] = { '\0' };
	char price[11] = { '\0' };
	char *ptr;
	char *l;
	int i = 0;
	int flag = 0;
	int cnt = 0;

	system("CLS");

	while (flag == 0)
	{
		cnt++;
		l = fgets(line, MAXLINE, file);
		if (*l != ' ' && *(l + 4) == ' ')
			flag = 1;
		else
			flag = 0;
	}
	cnt--;
	flag = 0;

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
				flag = 1;			
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
			flag = 1;
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

	fseek(file, 88*cnt, SEEK_SET);
	fputs(blank, file);
	fseek(file, 88*cnt, SEEK_SET);
	fputs(line, file);
	fclose(file);
}

void editing()
{
	file = fopen("base.txt", "r+");
	char line[MAXLINE];
	char blank[87] = { NULL };
	char destination[34] = { '\0' };
	char time_d[6] = { '\0' };
	char time_a[6] = { '\0' };
	char price[11] = { '\0' };
	char *ptr;
	char *l;
	char flight[3] = {'\0'};

	system("CLS");

	printf("- Редактирование базы данных -\n");
	printf("Введите номер рейса для редактирования: ");
	scanf("%s", &flight);

	l = fgets(line, MAXLINE, file);
	l = fgets(line, MAXLINE, file);

	for (int i = 0; i < 3; i++)
	{

	}



}

void deleting()
{

}

int main()
{
	setlocale(LC_ALL, "Russian");

	FILE *f = NULL; 

	int number;

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
	case 0:
		return 0;
	}
	return 0;
}
