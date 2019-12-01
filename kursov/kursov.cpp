#include "pch.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 150

FILE *file;

struct flight
{
	int number;
	char departures[19] = { 0 };
	char arrivals[19] = { 0 };
	char time_d[13] = { 0 };
	char time_a[13] = { 0 };
	unsigned int price;
};

void zero(char str[])
{
	for (int i = 0; i < sizeof(str); i++)
	{
		str[i] = '\0';
	}
}

void read(struct flight * reys)
{
	file = fopen("base.txt", "r");

	char line[MAXLINE] = { 0 };
	char number[3] = { 0 };
	char price[14] = { 0 };
	int p = 0, n = 0;
	fgets(line, MAXLINE, file);
	fgets(line, MAXLINE, file);

	while (line != NULL)
	{
		for (int i = 0; i<sizeof(number); i++)
			number[i] = line[i];
		reys[n].number = atoi(number);

		for (int i = 78; line[i] != ' '; i++)
			price[i - 78] = line[i];
		reys[n].price = atoi(price);

		for (int i = 4; line[i] != ' '; i++)
			reys[n].departures[i - 4] = line[i];

		for (int i = 25; line[i] != ' '; i++)
			reys[n].arrivals[i - 25] = line[i];

		for (int i = 46; line[i] != ' '; i++)
			reys[n].time_d[i - 46] = line[i];

		for (int i = 62; line[i] != ' '; i++)
			reys[n].time_a[i - 62] = line[i];

		n++;
		zero(number);
		zero(price);
		fgets(line, MAXLINE, file);
	}
}

void replenishment()
{

}

void editing()
{
	
}

void deleting()
{
	
}



void minPrice()
{
	
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int number;
	struct flight reys[20];
	read(reys);

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
