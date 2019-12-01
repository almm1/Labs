#include "pch.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 150
#define sizeline 95
#define posDep 4
#define posArr 25
#define posT_d 46
#define posT_a 62
#define posPri 78

FILE *file;

struct flight
{
	int number;
	char departures[19] = { 0 };
	char arrivals[19] = { 0 };
	char time_d[5] = { 0 };
	char time_a[5] = { 0 };
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
	char number[4] = { 0 };
	char price[14] = { 0 };
	int p = 0, n = 0;
	fgets(line, MAXLINE, file);
	fgets(line, MAXLINE, file);

	while (!feof(file))
	{
		for (int i = 0; line[i]!=' '; i++)
			number[i] = line[i];
		reys[n].number = atoi(number);

		for (int i = posPri; line[i] != ' '; i++)
			price[i - posPri] = line[i];
		reys[n].price = atoi(price);

		for (int i = posDep; line[i] != ' '; i++)
			reys[n].departures[i - posDep] = line[i];

		for (int i = posArr; line[i] != ' '; i++)
			reys[n].arrivals[i - posArr] = line[i];

		for (int i = posT_d; line[i] != ' '; i++)
			reys[n].time_d[i - posT_d] = line[i];

		for (int i = posT_a; line[i] != ' '; i++)
			reys[n].time_a[i - posT_a] = line[i];

		n++;
		zero(number);
		zero(price);
		fgets(line, MAXLINE, file);
	}
	fclose(file);
}

void load(struct flight * reys, int str)
{
	file = fopen("base.txt", "w+");
	fseek(file, str*sizeline, SEEK_SET);
}

int replenishment(struct flight * reys)
{
	system("CLS");
	int cnt = 0;
	int flag = 0;
	for (int i = 0; reys[i].departures[0] != '\0'; i++)
	{
		cnt++;
	}
	reys[cnt].number = cnt + 1;
	printf("- Пополнение базы данных -\n");
	printf("Введите пункт вылета: ");
	scanf("%s", &reys[cnt].departures);
	printf("Введите пункт прилета: ");
	scanf("%s", &reys[cnt].arrivals);
	do
	{
		printf("Введите время вылета в фромате '00:00': ");
		scanf("%s", &reys[cnt].time_d);
		if ((reys[cnt].time_d[0] >= '0' && reys[cnt].time_d[0] <= '2') && 
			(reys[cnt].time_d[1] >= '0'&&reys[cnt].time_d[1] <= '9') &&
			(reys[cnt].time_d[2] == ':') && 
			(reys[cnt].time_d[3] >= '0'&&reys[cnt].time_d[3] <= '5') && 
			(reys[cnt].time_d[4] >= '0'&&reys[cnt].time_d[4] <= '9'))
		{
			flag = 1;
			if (reys[cnt].time_d[0] == '2')
			{ 
				if((reys[cnt].time_d[1] >= '0' && reys[cnt].time_d[1] <= '3'))
				flag = 1;
				else
				{
					flag = 0;
					printf("Неверный формат\n");
				}
			}
		}
		else
		{
			flag = 0;
			printf("Неверный формат\n");
		}
	} while (flag == 0);
	flag = 0;

	do
	{
		printf("Введите время прилета в фромате '00:00': ");
		scanf("%s", &reys[cnt].time_a);
		if ((reys[cnt].time_a[0] >= '0' && reys[cnt].time_a[0] <= '2') &&
			(reys[cnt].time_a[1] >= '0'&&reys[cnt].time_a[1] <= '9') &&
			(reys[cnt].time_a[2] == ':') &&
			(reys[cnt].time_a[3] >= '0'&&reys[cnt].time_a[3] <= '5') &&
			(reys[cnt].time_a[4] >= '0'&&reys[cnt].time_a[4] <= '9'))
		{
			flag = 1;
			if (reys[cnt].time_a[0] == '2')
			{
				if ((reys[cnt].time_a[1] >= '0' && reys[cnt].time_a[1] <= '3'))
					flag = 1;
				else
				{
					flag = 0;
					printf("Неверный формат\n");
				}
			}
		}
		else
		{
			flag = 0;
			printf("Неверный формат\n");
		}
	} while (flag == 0);
	flag = 0;
	do
	{
		printf("Введите стоимость: ");
		scanf("%d", &reys[cnt].price);
		if (reys[cnt].price > 0)
			flag = 1;
		else
		{
			printf("Ошибка.!");
			flag = 0;
		}
	} while (flag == 0);
		flag = 0;
		return reys[cnt].number;
}

void editing(struct flight * reys)
{
	
}

void deleting(struct flight * reys)
{
	
}



void minPrice(struct flight * reys)
{
	
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int number;
	int str = 0;
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
			str=replenishment(reys);
			load(reys, str);
			break;
		case 2:
			editing(reys);
			//load(reys);
			break;
		case 3:
			deleting(reys);
			//load(reys);
			break;
		case 4:
			printf("в разработке");
			break;
		case 5:
			minPrice(reys);
			break;
		}
	} while (number != 0);
	return 0;
}
