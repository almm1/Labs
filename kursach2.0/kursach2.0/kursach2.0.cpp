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

void read(struct flight * reys);
void load(struct flight * reys, int n);
int replenishment(struct flight * reys, int n);
void editing(struct flight * reys);
int deleting(struct flight * reys, int n);
void minPrice(struct flight * reys);
void minTime(struct flight * reys);
int counter_struct();
void print();

void print()
{
	system("CLS");
	file = fopen("base.txt", "r");
	char line[MAXLINE];
	while (!feof(file))
	{
		fgets(line, MAXLINE, file);
		if (*line == NULL)
			break;
		printf("%s", line);
	}
	fclose(file);

	getchar();
}


struct flight
{
	int number;
	char departures[19] = { 0 };
	char arrivals[19] = { 0 };
	char time_d[5] = { 0 };
	char time_a[5] = { 0 };
	unsigned int price;
};

int counter_struct()
{
	char line[MAXLINE];
	char *ptr = line;
	int i;
	file = fopen("base.txt", "r");
	fgets(line, MAXLINE, file);
	fgets(line, MAXLINE, file);
	for (i = 0; line[5] != ' '||line[0]=='-'; i++)
	{
		if (ptr == NULL)
			break;
		ptr = fgets(line, MAXLINE, file);

	}
	fclose(file);
	return i;
}

void read(struct flight * reys)
{
	file = fopen("base.txt", "r");

	char line[MAXLINE];
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
		memset(number, '\0', sizeof(number));
		memset(price, '\0', sizeof(price));
		//zero(number);
		//zero(price);
		fgets(line, MAXLINE, file);
	}
	fclose(file);
}

void load(struct flight * reys, int n)
{
	char line[MAXLINE];
	char sum[15];
	char num[3];
	memset(line, ' ', MAXLINE);
	//probel_line(line);
	file = fopen("base.txt", "w+");
	fputs(header, file);
	for (int i = 0;  i<n; i++)
	{
		line[posDep - 1] = line[posArr - 1] = line[posPri - 1] = line[posT_a - 1] = line[posT_d - 1] = line[93] = '|';
		line[94] = '\n';
		line[95] = '\0';
		if (reys[i].number == 0)
		{   
			line[0] = '-';
			fputs(line, file);
			continue;
		}
		_itoa(reys[i].number, num, 10);
		_itoa(reys[i].price, sum, 10);

		for (int n = 0; n < strlen(num); n++)
			line[n] = num[n];

		for (int n = posDep; (n - posDep) < strlen(reys[i].departures); n++)
			line[n] = reys[i].departures[n - posDep];

		for (int n = posArr; (n - posArr) < strlen(reys[i].arrivals); n++)
			line[n] = reys[i].arrivals[n - posArr];

		for (int n = posT_d; (n - posT_d) < 5; n++)
			line[n] = reys[i].time_d[n - posT_d];

		for (int n = posT_a; (n - posT_a) < 5; n++)
			line[n] = reys[i].time_a[n - posT_a];

		for (int n = posPri; (n - posPri) < strlen(sum); n++)
			line[n] = sum[n - posPri];

		fputs(line, file);
		memset(line, ' ', MAXLINE);
		memset(num, ' ', 3);
		memset(sum, ' ', 15);
		//probel_line(line);
		//probel(sum);
		//probel(num);
	}
	memset(line, '\0', MAXLINE);
	//zero(line);
	fclose(file);
	printf("Загрузка выполнена успешно. Нажмите любую клавишу для продолжения. ");
	getchar();
	getchar();
}

int replenishment(struct flight * reys, int n)
{
	system("CLS");
	int cnt = 0;
	int flag = 0;
	for (int i = 0; reys[i].number >0; i++)
	{
		cnt++;
	}
	if (reys[cnt].number == -1)
	{
		n = n;
	}
	else
		n++;

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
	printf("Запись добавлена.\nВыполните загрузку чтобы сохранить изменения. \nНажмите любую клавишу для продолжения. ");
	getchar();
	getchar();
	return n;
}

void editing(struct flight * reys)
{
	system("CLS");
	int tr = 0;
	int n = 0;
	int flag = 0;

	//do
	//{
		system("CLS");
		printf("- Редактирование базы данных -\n");
		do
		{
			do
			{
				printf("Введите номер рейса для редактирования: ");
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
		//a:
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
				//goto a;
				continue;
			}
			switch (n)
			{
			case 1:
				system("CLS");
				memset(reys[tr - 1].departures, '\0', sizeof(reys[tr - 1].departures));
				//zero(reys[tr - 1].departures);
				printf("Введите новый пункт вылета: ");
				scanf("%s", &reys[tr - 1].departures);
				break;
			case 2:
				system("CLS");
				memset(reys[tr - 1].arrivals, '\0', sizeof(reys[tr - 1].arrivals));
				//zero(reys[tr - 1].arrivals);
				printf("Введите новый пункт прилета: ");
				scanf("%s", &reys[tr - 1].arrivals);
				break;
			case 3:
				system("CLS");
				memset(reys[tr - 1].time_d, '\0', sizeof(reys[tr - 1].time_d));
				//zero(reys[tr - 1].time_d);
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
				memset(reys[tr - 1].time_a, '\0', sizeof(reys[tr - 1].time_a));
				//zero(reys[tr - 1].time_a);
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
	//} while (flag == 0);
	printf("Запись изменена.\nВыполните загрузку чтобы сохранить изменения. \nНажмите любую клавишу для продолжения. ");
	getchar();
	getchar();
g:	flag = 0;
}

int deleting(struct flight * reys, int n)
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
		{
			if (reys[tr - 1].departures[0] == 0)
			{
				printf("Ошибка. Рейса с данным номером не существует, введите другой. \n");
				flag = 0;
			}
			else
				flag = 1;
		}
		else
			flag = 0;
	} while (flag == 0);
	memset(reys[tr - 1].arrivals, '\0', sizeof(reys[tr - 1].arrivals));
	memset(reys[tr - 1].departures, '\0', sizeof(reys[tr - 1].departures));
	memset(reys[tr - 1].time_d, '\0', sizeof(reys[tr - 1].time_d));
	memset(reys[tr - 1].time_a, '\0', sizeof(reys[tr - 1].time_a));
	reys[tr - 1].price = 0;
	reys[tr - 1].number = -1;
g: flag = 0;
	printf("Запись удалена.\nВыполните загрузку чтобы сохранить изменения. \nНажмите любую клавишу для продолжения. ");
	getchar();
	getchar();
	for (int i = 0; i < n; i++)
	{
		if (reys[i].number == -1)
			n--;
	}
	return n;
}

void minPrice(struct flight * reys, int n)
{
	system("CLS");
	char dep[19];
	char arr[19];
	char arr_t[19];
	char dep_t[19];
	char line[MAXLINE];
	int cnt[10] = { 0 };
	int x = 0;
	int z = 0;
	unsigned int prices = 10000000;
	unsigned int temp_price = 0;
	int flag = 0;
	printf("Введите пункт вылета: ");
	scanf("%s", &dep);
	printf("Введите пункт прилета: ");
	scanf("%s", &arr);
	
	/*while ((strcmp(dep, dep_t)!=0) && (strcmp(arr, arr_t) != 0))
	{
		strcpy(dep_t, reys[x].departures);
		strcpy(arr_t, reys[z].arrivals);

	}*/
	/*for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (strcmp(arr, ) == 0);
		}
	}*/
	for (int i = 0; i < n; i++)
	{
		if (strcmp(arr, reys[i].arrivals) == 0)
		{
			cnt[x++] = reys[i].number;
		}
	}
	x = 0;

}

void minTime(struct flight * reys, int n)
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

}

struct flight *reys;

int main()
{
	
	setlocale(LC_ALL, "Russian");
	int number;
	int n;
	n=counter_struct();
	
	reys = (struct flight*)calloc(1000, sizeof(struct flight));
	reys = (struct flight*)realloc(reys, (n + 1) * sizeof(struct flight));

	read(reys);

	do {
		system("CLS");
		printf("Выберете действие: \n");
		printf("1 - Пополнение базы. \n");
		printf("2 - Редактирование базы. \n");
		printf("3 - Удаление записей. \n");
		printf("4 - Подбор маршрута с наименьшим временем ожидания при пересадке. \n");
		printf("5 - Подбор маршрута с наименьшей стоимостью. \n");
		printf("6 - Загрузка. \n");
		printf("7 - Просмотр записей. \n");
		printf("0 - Выход. \n\n");
		scanf("%d", &number);

		if ((number < 0) || (number > 7))
		{
			printf("Ошибка. Выбрано несуществующее действие.");
		}

		switch (number)
		{
		case 1:
			n=replenishment(reys, n);
			reys = (struct flight*)realloc(reys, (n + 1) * sizeof(struct flight));
			break;
		case 2:
			editing(reys);
			break;
		case 3:
			n=deleting(reys, n);
			reys = (struct flight*)realloc(reys, (n + 1) * sizeof(struct flight));
			break;
		case 4:
			minTime(reys, n);
			break;
		case 5:
			minPrice(reys, n);
			break;
		case 6:
			load(reys, n);
			break;
		case 7:
			load(reys, n);
			print();
		}
	} while (number != 0);
	free(reys);
	return 0;
}