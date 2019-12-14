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
#define header "   |     Departures     |      Arrivals      |Time departures| Time arrivals |     Price     |\n"  

FILE *file;

void zero(char str[]);
void read(struct flight * reys);
void load(struct flight * reys);
void replenishment(struct flight * reys);
void editing(struct flight * reys);
void deleting(struct flight * reys);
void minPrice(struct flight * reys);
void minTime(struct flight * reys);


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

void probel(char str[])
{
	for (int i = 0; i < strlen(str); i++)
	{
		str[i] = ' ';
	}
}

void probel_line(char str[])
{
	for (int i = 0; i < 149; i++)
	{
		str[i] = ' ';
	}
	str[149] = '\0';
}


void read(struct flight * reys)
{
	file = fopen("base.txt", "r");

	char line[MAXLINE]; //= { 0 };
	char number[4] = { 0 };
	char price[14] = { 0 };
	int p = 0, n = 0;

	rewind(file);
	fgets(line, MAXLINE, file);
	fgets(line, MAXLINE, file);

	while (!feof(file))
	{
		for (int i = 0; line[i] != ' '; i++)
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

void load(struct flight * reys)
{
	char line[MAXLINE];
	char sum[15];
	char num[3];
	probel_line(line);
	file = fopen("base.txt", "w+");
	fputs(header, file);
	for(int i = 0; reys[i].departures[0] != 0 ; i++)
	{
		line[posDep-1] = line[posArr-1] = line[posPri-1] = line[posT_a-1] = line[posT_d-1] = line[93] = '|';
		line[94] = '\n';
		line[95] = '\0';

		_itoa(reys[i].number, num, 10);
		_itoa(reys[i].price, sum, 10);

		for (int n = 0; n<strlen(num); n++)
			line[n] = num[n];

		for (int n = posDep; (n-posDep) < strlen(reys[i].departures); n++)
			line[n] = reys[i].departures[n - posDep];

		for (int n = posArr; (n - posArr) < strlen(reys[i].arrivals); n++)
			line[n] = reys[i].arrivals[n - posArr];

		for (int n = posT_d; (n - posT_d ) < 5; n++)
			line[n] = reys[i].time_d[n - posT_d];

		for (int n = posT_a; (n-posT_a)<5; n++)
			line[n] = reys[i].time_a[n - posT_a];

		for (int n = posPri; (n - posPri) < strlen(sum); n++)
			line[n] = sum[n - posPri];

		fputs(line, file);
		probel_line(line);
		probel(sum);
		probel(num);
	}
	zero(line);
	fclose(file);
	getchar();
}

void replenishment(struct flight * reys)
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
				if ((reys[cnt].time_d[1] >= '0' && reys[cnt].time_d[1] <= '3'))
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
}

void editing(struct flight * reys)
{
	system("CLS");
	int tr = 0;
	int n = 0;
	int flag = 0;

	do
	{
		system("CLS");
		printf("- Редактирование базы данных -\n");
		do
		{
			do
			{
				printf("Введите номер рейса для редактирования: \n");
				scanf("%d", &tr);
				if (tr == 0)
					goto g;
				if (tr > 0)
					flag = 1;
				else
					flag = 0;
			} while (flag == 0);
			flag = 0;
			if (reys[tr - 1].departures[0] == 0)
			{
				printf("Ошибка. Рейса с данным номером не существует \n");
				flag = 0;
			}
			else
				flag = 1;
		} while (flag == 0);
		flag = 0;
		do
		{
		a:
			system("CLS");
			printf("Выберете что требуется изменить: \n");
			printf("1 - Пункт вылета \n");
			printf("2 - Пункт прилета \n");
			printf("3 - Время вылета() \n");
			printf("4 - Время прилета() \n");
			printf("5 - Стоимость() \n");
			printf("0 - Назад \n\n");
			scanf("%d", &n);
			if (n < 0 || n>5)
			{
				printf("Ошибка. Выбрано не существующее действие");
				goto a;
			}
			switch (n)
			{
			case 1:
				system("CLS");
				zero(reys[tr - 1].departures);
				printf("Введите новый пункт вылета: ");
				scanf("%s", &reys[tr - 1].departures);
				break;
			case 2:
				system("CLS");
				zero(reys[tr - 1].arrivals);
				printf("Введите новый пункт прилета: ");
				scanf("%s", &reys[tr - 1].arrivals);
				break;
			case 3:
				system("CLS");
				zero(reys[tr - 1].time_d);
				do
				{
					printf("Введите новое время вылета в фромате '00:00': ");
					scanf("%s", &reys[tr - 1].time_d);
					if ((reys[tr - 1].time_d[0] >= '0' && reys[tr - 1].time_d[0] <= '2') &&
						(reys[tr - 1].time_d[1] >= '0'&&reys[tr - 1].time_d[1] <= '9') &&
						(reys[tr - 1].time_d[2] == ':') &&
						(reys[tr - 1].time_d[3] >= '0'&&reys[tr - 1].time_d[3] <= '5') &&
						(reys[tr - 1].time_d[4] >= '0'&&reys[tr - 1].time_d[4] <= '9'))
					{
						flag = 1;
						if (reys[tr - 1].time_d[0] == '2')
						{
							if ((reys[tr - 1].time_d[1] >= '0' && reys[tr - 1].time_d[1] <= '3'))
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
				break;
			case 4:
				system("CLS");
				zero(reys[tr - 1].time_a);
				do
				{
					printf("Введите новое время прилета в фромате '00:00': ");
					scanf("%s", &reys[tr - 1].time_a);
					if ((reys[tr - 1].time_a[0] >= '0' && reys[tr - 1].time_a[0] <= '2') &&
						(reys[tr - 1].time_a[1] >= '0'&&reys[tr - 1].time_a[1] <= '9') &&
						(reys[tr - 1].time_a[2] == ':') &&
						(reys[tr - 1].time_a[3] >= '0'&&reys[tr - 1].time_a[3] <= '5') &&
						(reys[tr - 1].time_a[4] >= '0'&&reys[tr - 1].time_a[4] <= '9'))
					{
						flag = 1;
						if (reys[tr - 1].time_a[0] == '2')
						{
							if ((reys[tr - 1].time_a[1] >= '0' && reys[tr - 1].time_a[1] <= '3'))
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
				break;
			case 5:
				system("CLS");
				reys[tr - 1].price = 0;
				do
				{
					printf("Введите стоимость: ");
					scanf("%d", &reys[tr - 1].price);
					if (reys[tr - 1].price > 0)
						flag = 1;
					else
					{
						printf("Ошибка.!");
						flag = 0;
					}
				} while (flag == 0);
				flag = 0;
				break;
			}

		} while (n != 0);
	} while (flag == 0);
g:	flag = 0;
}

void deleting(struct flight * reys)
{
	int tr = 0;
	int flag = 0;
	system("CLS");
	printf("- Удаление -\n");
	do
	{
		printf("Введите номер рейса для удаления: ");
		scanf("%d", &tr);
		if (tr == 0)
			goto g;
		if (tr > 0)
			flag = 1;
		else
			flag = 0;
	} while (flag == 0);
	flag = 0;
	zero(reys[tr - 1].departures);
	zero(reys[tr - 1].arrivals);
	zero(reys[tr - 1].time_d);
	zero(reys[tr - 1].time_a);
	reys[tr - 1].price = 0;
g: flag = 0;
}



void minPrice(struct flight * reys)
{
	system("CLS");
	char dep[19];
	char arr[19];
	char dep_t[19];
	char line[MAXLINE];
	int cnt = 0;
	unsigned int prices = 10000000;
	unsigned int temp_price = 0;
	int flag = 0;
	printf("Введите пункт вылета: ");
	scanf("%s", &dep);
	printf("Введите пункт прилета: ");
	scanf("%s", &arr);
	printf("\n" header);
	strcpy(dep_t, dep);
	//line[posDep] = line[posArr] = line[posPri] = line[posT_a] = line[posT_d] = line[95] = '|';
	for (int i = 0; i < 20; i++)
	{
		if ((strcmp(dep, reys[i].departures) == 0) && (strcmp(arr, reys[i].arrivals) == 0))
		{
			temp_price = reys[i].price;
			if (prices > temp_price)
			{
				prices = temp_price;
			}
		}
	}
	for (int i = 0; i < 20; i++)
	{
		if ((strcmp(dep_t, reys[i].departures) == 0) && (strcmp(arr, reys[i].arrivals) != 0))
		{
			strcpy(dep_t, reys[i].arrivals);
		}
	}
}

void minTime(struct flight * reys)
{
	system("CLS");
	char dep[19];
	char arr[19];
	int cnt = 0;
	unsigned int delay = 10000000;
	unsigned int temp_delay = 0;
	int flag = 0;
	printf("Введите пункт вылета: ");
	scanf("%s", &dep);
	printf("Введите пункт прилета: ");
	scanf("%s", &arr);

	for (int i = 0; delay > temp_delay; i++)
	{
		if (strcmp(reys[i].departures, dep) == 0)
		{

		}


	}

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
		printf("6 - Загрузка \n");
		printf("0 - Выход \n\n");
		scanf("%d", &number);

		if ((number < 0) || (number > 6))
		{
			printf("Ошибка. Выбрано несуществующее действие");
		}

		switch (number)
		{
		case 1:
			replenishment(reys);
			break;
		case 2:
			editing(reys);
			break;
		case 3:
			deleting(reys);
			break;
		case 4:
			minTime(reys);
			break;
		case 5:
			minPrice(reys);
			break;
		case 6:
			load(reys);
			break;
		}
	} while (number != 0);
	return 0;
}
