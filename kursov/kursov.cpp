#include "pch.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 150

FILE *file;

void put(char str[], int n)
{
	for (int i = 0; str[i+n] != '|'; i++)
		str[i+n] = ' ';
}

void zero(char str[])
{
	for (int i = 0; i < sizeof(str); i++)
	{
		str[i] = '\0';
	}
}

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
		*l++;
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
	flag = 0;
	i = 32;
	while (*ptr != '\0')
	{
		*(l + i) = *ptr;
		*l++;
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
	flag = 0;
	i = 43;
	while (*ptr != '\0')
	{
		*(l + i) = *ptr;
		*l++;
		*ptr++;
	}

	printf("\nВведите стоимость билета: ");
	scanf("%s", &price);
	ptr = price;
	i = 54;

	while (*ptr != '\0')
	{
		*(l + i) = *ptr;
		*l++;
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
	char *l;
	char *ptr;
	int flag = 0;
	int flight = 0;
	int n = 0;
	int number = 0;

	system("CLS");

	l = fgets(line, MAXLINE, file);

	printf("- Редактирование базы данных -\n");
	do {
		printf("Введите номер рейса для редактирования: ");
		scanf("%d", &flight);

		for (int i = 0; i < flight; i++)
		{
			l = fgets(line, MAXLINE, file);
		}
		if (l == NULL)
		{
			printf("Error!");
		}

		if (*(l + 4) != ' ')
			flag = 1;
		else
		{
			printf("Рейса с таким номером не существует\n");
			flag = 0;
			rewind(file);
			l = fgets(line, MAXLINE, file);
		}
	} while (flag == 0);
	flag = 0;

	system("CLS");
	printf("Выберете что требуется изменить: \n");
	printf("1 - Пункт прилета(Destination) \n");
	printf("2 - Время вылета() \n");
	printf("3 - Время прилета() \n");
	printf("4 - Стоимость() \n");
	printf("0 - Назад \n");
	scanf("\n%d", &number);

	if ((number < 1) && (number > 4))
		printf("Ошибка. Выбрано несуществующее действие");

	switch (number)
	{
	case 1:
		system("CLS");

		n = 4;
		put(line, n);
		printf("Введите новый пункт прилета: ");
		scanf("%s", &destination);

		for (int i = 0; destination[i] != '\0'; i++)
		{
			*(l + n+i) = destination[i];
		}

		break;

	case 2:
		system("CLS");

		n = 38;
		put(line, n);
		do
		{
			printf("Введите новое время вылета в фромате '00:00': ");
			scanf("%s", &time_d);
			ptr = time_d;
			if ((*ptr >= '0' && *ptr <= '9') && (*(ptr + 1) >= '0' && *(ptr + 1) <= '9') && (*(ptr + 3) >= '0' && *(ptr + 3) <= '9') && (*(ptr + 4) >= '0' && *(ptr + 4) <= '9') && (*(ptr + 2) == ':'))
				flag = 1;
			else
				printf("Неверный формат\n");
		} while (flag == 0);
		flag = 0;

		for (int i = 0; time_d[i] != '\0'; i++)
		{
			*(l + n + i) = time_d[i];
		}

		break;
	case 3:
		system("CLS");

		n = 54;
		put(line, n);
		do
		{
			printf("Введите новое время прилета в фромате '00:00': ");
			scanf("%s", &time_a);
			ptr = time_a;
			if ((*ptr >= '0' && *ptr <= '9') && (*(ptr + 1) >= '0' && *(ptr + 1) <= '9') && (*(ptr + 3) >= '0' && *(ptr + 3) <= '9') && (*(ptr + 4) >= '0' && *(ptr + 4) <= '9') && (*(ptr + 2) == ':'))
				flag = 1;
			else
				printf("Неверный формат\n");
		} while (flag == 0);
		flag = 0;

		for (int i = 0; time_a[i] != '\0'; i++)
		{
			*(l + n + i) = time_a[i];
		}
		break;
	case 4:
		system("CLS");

		n = 70;
		put(line, n);
		printf("Введите новую стоимость: ");
		scanf("%s", &price);

		for (int i = 0; price[i] != '\0'; i++)
		{
			*(l + n + i) = price[i];
		}

		*(l + n + 1) = ' ';
		*(l + n + 2) = 'r';
		*(l + n + 3) = 'u';
		*(l + n + 4) = 'b';
		break;
	}
	fseek(file, 88 * flight, SEEK_SET);
	fputs(blank, file);
	fseek(file, 88 * flight, SEEK_SET);
	fputs(line, file);
	
	fclose(file);
}

void deleting()
{
	file = fopen("base.txt", "r+");
	char line[MAXLINE];
	char *l;
	int flight = 0;

	system("CLS");

	l = fgets(line, MAXLINE, file);

	printf("- Удаление записей -\n");
	
		printf("Введите номер рейса который требуется удалить: ");
		scanf("%d", &flight);

		for (int i = 0; i < flight; i++)
			l = fgets(line, MAXLINE, file);

		if (l == NULL)
		{
			printf("Error!");
		}
		put(line, 4);
		put(line, 38);
		put(line, 54);
		put(line, 70);

		fseek(file, 88 * flight, SEEK_SET);
		fputs(line, file);

		fclose(file);
}



void minPrice()
{
	file = fopen("base.txt", "r+");
	char line[MAXLINE];
	char *l;
	char price[11] = { '\0' };
	char *ptr;
	int a = 0, sum = 10000000;
	int cnt = 0;
	int string = 0;

	l = fgets(line, MAXLINE, file);
	ptr = price;

	system("CLS");

	while (!feof(file))
	{
	
		l = fgets(line, MAXLINE, file);
		cnt++;

		if (l == NULL)
			break;

		if (line[4] != ' ')
		{
			for (int i = 0; *(l + i + 70) != ' '; i++)
			{
				*(ptr + i) = *(l + i + 70);
			}

			a = atoi(price);

			if (a < sum)
			{
				sum = a;
				string = cnt;
			}
		}
		zero(price);
	}
	rewind(file);

	fgets(line, MAXLINE, file);
	printf("%s", line);

	for(int i = 0; i<string;i++)
		fgets(line, MAXLINE, file);

	printf("%s", line);
	getchar();
	getchar();
	fclose(file);
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int number;

	do {
		system("CLS");
		printf("Выберете действие: \n");
		printf("1 - Пополнение базы \n");
		printf("2 - Редактирование базы \n");
		printf("3 - Удаление записей \n");
		printf("4 - Подбор маршрута с наименьшим временем ожидания при пересадке \n");
		printf("5 - Подбор маршрута с наименьшей стоимостью \n");
		printf("0 - Выход \n\n");
		scanf("%d", &number);

		if ((number < 0) || (number > 5))
		{
			printf("Ошибка. Выбрано несуществующее действие");
		}

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
			minPrice();
			break;
		}
	} while (number != 0);
	return 0;
}
