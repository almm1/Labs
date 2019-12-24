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
struct flight *reys;

void read();
int index(int n);
void load(int n);
int find(char dep[], char arr[], int n, int * a, int *b);
int replenishment(int n);
void editing();
int deleting(int n);
void minPrice(int n);
void minTime(int n);
int counter_struct();
void print();

void print()
{
	system("CLS");
	file = fopen("base.txt", "r");
	char line[MAXLINE];
	char *ptr = line;
	while (!feof(file))
	{
		ptr = fgets(line, MAXLINE, file);
		if (ptr == NULL)
			break;
		printf("%s", line);
	}
	fclose(file);
}

struct flight
{
	int number;
	char departures[19] = { 0 };
	char arrivals[19] = { 0 };
	char time_d[6] = { 0 };
	char time_a[6] = { 0 };
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

void read()
{
	file = fopen("base.txt", "r");
	char line[MAXLINE], number[4] = { 0 }, price[14] = { 0 };
	int n = 0;
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
		fgets(line, MAXLINE, file);
	}
	fclose(file);
}

void load(int n)
{
	char line[MAXLINE], num[3], sum[15];
	memset(line, ' ', MAXLINE);
	file = fopen("base.txt", "w+");
	fputs(header, file);
	for (int i = 0;  i<n; i++)
	{
		line[posDep - 1] = line[posArr - 1] = line[posPri - 1] = line[posT_a - 1] = line[posT_d - 1] = line[93] = '|';
		line[94] = '\n';
		line[95] = '\0';
		if (reys[i].number == -1)
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
	}
	fclose(file);
}

int replenishment(int n)
{
	system("CLS");
	int cnt = 0, flag = 0;
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
	return n;
}

void editing()
{
	system("CLS");
	int tr = 0, n = 0, flag = 0;
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
			continue;
		}
		switch (n)
		{
		case 1:
			system("CLS");
			memset(reys[tr - 1].departures, '\0', sizeof(reys[tr - 1].departures));
			printf("Введите новый пункт вылета: ");
			scanf("%s", &reys[tr - 1].departures);
			break;
		case 2:
			system("CLS");
			memset(reys[tr - 1].arrivals, '\0', sizeof(reys[tr - 1].arrivals));
			printf("Введите новый пункт прилета: ");
			scanf("%s", &reys[tr - 1].arrivals);
			break;
		case 3:
			system("CLS");
			memset(reys[tr - 1].time_d, '\0', sizeof(reys[tr - 1].time_d));
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
	}while (n != 0);
g:	flag = 0;
}

int deleting(int n)
{
	int tr = 0, flag = 0;
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
	for (int i = 0; i < n; i++)
	{
		if (reys[i].number == -1)
			n--;
	}
	return n;
}
struct target
{
	int number;
	char point[4] = { '\0' };
};
struct target *from;
struct target *to;
int func(int x, int z, int n, int * m, int * k, int *t_1, int * t_2)
{
	for (int i=*t_1; i < z; i++)
	{
		for (int j =*t_2; j < x; j++)
		{
			{
				if ((strcmp(to[i].point, from[j].point) == 0) || (to[i].number == from[j].number))
				{
					*m = to[i].number;
					*k = from[j].number;
					*t_1 = i;
					*t_2 = ++j;
					if (j == x)
					{
						*t_2 = 0;
						++*t_1;
					}
					return 0;
				}
			}
		}
	}
}

int find(char dep[], char arr[], int n, int * a, int *b)
{
	int x = 0, z = 0, flag1 = 0, flag2 = 0;
	for (int i = 0; i < n; i++)
	{
		if (strcmp(dep, reys[i].departures) == 0)
		{
			flag1 = 1;
			to[z++].number = reys[i].number;
		}
		if (strcmp(arr, reys[i].arrivals) == 0)
		{
			flag2 = 1;
			from[x++].number = reys[i].number;
		}
	}
	if (flag1 == 1 && flag2 == 1)
	{
		for (int i = 0; i < z; i++)
		{
			for (int p = 0; p < 4; p++)
				to[i].point[p] = reys[index(to[i].number)].arrivals[p];
		}
		for (int i = 0; i < x; i++)
		{
			for (int p = 0; p < 4; p++)
				from[i].point[p] = reys[index(from[i].number)].departures[p];
		}
		*a = x;
		*b = z;
	}
	else
	{
		printf("Не удалось найти заданый маршрут");
		return 0;
	}
	return 1;
}

int index(int n)
{
	int i=0;
	while (reys[i].number != n) i++;
	return i;
}

int convert_time(int n1, int n, char mod)
{
	int min = 0, hour=0;
	char line[20] = { 0 };
	if (mod == 'd')
		strcpy(line, reys[index(n1)].time_d);
	if (mod == 'a')
		strcpy(line, reys[index(n1)].time_a);
	char * ptr=strtok(line, ":");
	hour = atoi(line)*60;
	min = atoi(ptr+3)+hour;
	return min;
}

void minPrice(int n)
{
	system("CLS");
	char dep[5], arr[5];
	int prices = 10000000, temp_price = 0, timeD=0, timeA=0, cnt[5], x = 0, z = 0, t_1 = 0, t_2 = 0;
	to = (struct target*)calloc(n, sizeof(struct target));
	from = (struct target*)calloc(n, sizeof(struct target));
	printf("Введите пункт вылета: ");
	scanf("%s", &dep);
	printf("Введите пункт прилета: ");
	scanf("%s", &arr);
	if (find(dep, arr, n, &x, &z)==1)
	{
		for (int i = 0; ((i < x) && (i < z)); i++)
		{
			func(x, z, n, &cnt[0], &cnt[1], &t_1, &t_2);
			if ((timeA = convert_time(cnt[0], n, 'a')) > (timeD = convert_time(cnt[1], n, 'd')) && cnt[0] != cnt[1])
				continue;
			if (cnt[0] != cnt[1])
				temp_price = reys[index(cnt[0])].price + reys[index(cnt[1])].price;
			else
				temp_price = reys[index(cnt[0])].price;
			if (temp_price < prices)
			{
				prices = temp_price;
				cnt[3] = cnt[0];
				cnt[4] = cnt[1];
			}
		}
		system("CLS");
		printf("Маршрут с наименьшей стоимостью:\n");
		if ((cnt[3] == cnt[4])>0)
			printf("%d | %s - %s | %s - %s | %d\n", reys[index(cnt[3])].number, reys[index(cnt[3])].departures,
				reys[index(cnt[3])].arrivals, reys[index(cnt[3])].time_d, reys[index(cnt[3])].time_a, reys[index(cnt[3])].price);
		else if ((cnt[3] != cnt[4]) > 0)
		{
			printf("%d | %s - %s | %s - %s | %d\n", reys[index(cnt[3])].number, reys[index(cnt[3])].departures,
				reys[index(cnt[3])].arrivals, reys[index(cnt[3])].time_d, reys[index(cnt[3])].time_a, reys[index(cnt[3])].price);
			printf("%d | %s - %s | %s - %s | %d\n", reys[index(cnt[4])].number, reys[index(cnt[4])].departures,
				reys[index(cnt[4])].arrivals, reys[index(cnt[4])].time_d, reys[index(cnt[4])].time_a, reys[index(cnt[4])].price);
		}
		printf("Общая стоимость: %d", prices);
	}
	free(to);
	free(from);
	getchar(); getchar();
}


void minTime(int n)
{
	system("CLS");
	char dep[5], arr[5];
	int delay = 10000000, temp_delay = 0, timeD = 0, timeA = 0, cnt[10], x = 0, z = 0, t_1 = 0, t_2 = 0, minTime = 100000;
	to = (struct target*)calloc(n, sizeof(struct target));
	from = (struct target*)calloc(n, sizeof(struct target));
	printf("Введите пункт вылета: ");
	scanf("%s", &dep);
	printf("Введите пункт прилета: ");
	scanf("%s", &arr);
	if (find(dep, arr, n, &x, &z) == 1)
	{
		for (int i = 0; ((i < x)&&(i<z)); i++)
		{
			func(x, z, n, &cnt[0], &cnt[1], &t_1, &t_2);
				if (((timeA = convert_time(cnt[0], n, 'a')) - (timeD = convert_time(cnt[1], n, 'd')) > 720) && cnt[0] != cnt[1])
					continue;
				if (cnt[0] != cnt[1])
				{
					if ((timeA = convert_time(cnt[0], n, 'a')) > (timeD = convert_time(cnt[1], n, 'd')))
					{
						timeD += 24 * 60;
						if (delay > (temp_delay = timeD - timeA))
						{
							delay = temp_delay;
							cnt[6] = cnt[0];
							cnt[7] = cnt[1];
						}
					}
					else if (delay > (temp_delay = timeD - timeA))
					{
						delay = temp_delay;
						cnt[6] = cnt[0];
						cnt[7] = cnt[1];
					}
				}
				else
				{
					if ((timeA = convert_time(cnt[0], n, 'a')) > (timeD = convert_time(cnt[0], n, 'd')));
						timeD += 24 * 60;
					if (minTime > (timeD - timeA))
					{
						minTime = timeD - timeA;
						cnt[3] = cnt[0];
						cnt[4] = cnt[1];
					}
				}
		}
		system("CLS");
		if ((cnt[3] == cnt[4])>0)
		{
			printf("Маршрут без пересадок:\n");
			printf("%d | %s - %s | %s - %s | %d\n", reys[index(cnt[3])].number, reys[index(cnt[3])].departures,
				reys[index(cnt[3])].arrivals, reys[index(cnt[3])].time_d, reys[index(cnt[3])].time_a, reys[index(cnt[3])].price);
		}
		if (cnt[6] > 0 && cnt[7] > 0)
		{
			printf("Маршрут с наименьшеим временем ожидания при пересадке:\n");
			printf("%d | %s - %s | %s - %s | %d\n", reys[index(cnt[6])].number, reys[index(cnt[6])].departures,
				reys[index(cnt[6])].arrivals, reys[index(cnt[6])].time_d, reys[index(cnt[6])].time_a, reys[index(cnt[6])].price);
			printf("%d | %s - %s | %s - %s | %d\n", reys[index(cnt[7])].number, reys[index(cnt[7])].departures,
				reys[index(cnt[7])].arrivals, reys[index(cnt[7])].time_d, reys[index(cnt[7])].time_a, reys[index(cnt[7])].price);
			printf("Время ожидания: %d:%d", delay/60, delay%60);
		}
		else
			printf("Маршрутов с пересадками не найдено");
	}
	free(to);
	free(from);
	getchar(); getchar();
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int number, n;
	n=counter_struct();
	reys = (struct flight*)calloc(1000, sizeof(struct flight));
	reys = (struct flight*)realloc(reys, (n + 1) * sizeof(struct flight));
	read();
	do {
		system("CLS");
		printf("Выберете действие: \n1 - Пополнение базы. \n2 - Редактирование базы. \n3 - Удаление записей. \n4 - Подбор маршрута с наименьшим временем ожидания при пересадке. \n5 - Подбор маршрута с наименьшей стоимостью. \n6 - Просмотр записей. \n0 - Выход. \n\n");
		scanf("%d", &number);
		if ((number < 0) || (number > 6))
		{
			printf("Ошибка. Выбрано несуществующее действие. ВВедите еще раз.");
			getchar(); getchar();
		}
		switch (number)
		{
		case 1:
			n=replenishment(n);
			reys = (struct flight*)realloc(reys, (n + 1) * sizeof(struct flight));
			load(n);
			printf("Запись добавлена. \nНажмите любую клавишу для продолжения. ");
			getchar(); getchar();
			break;
		case 2:
			editing();
			load(n);
			printf("Запись изменена.\nНажмите любую клавишу для продолжения. ");
			getchar(); getchar();
			break;
		case 3:
			n=deleting(n);
			reys = (struct flight*)realloc(reys, (n + 1) * sizeof(struct flight));
			load(n);
			printf("Запись удалена. \nНажмите любую клавишу для продолжения. ");
			getchar(); getchar();
			break;
		case 4:
			minTime(n);
			break;
		case 5:
			minPrice(n);
			break;
		case 6:
			load(n);
			print();
			getchar();getchar();
			break;
		}
	} while (number != 0);
	free(reys);
	return 0;
}