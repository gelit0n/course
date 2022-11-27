#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define SIZE 21

struct processor {
	char* name;
	char* model;
	char* socket;
	int cores;
	double hz;
	char* graph;
};
typedef struct processor Processor;

//*Добавление записи*//
Processor add_processor(Processor z);
//*Вывод записи*//
int put_processor(Processor z);
//*Поиск по записи совпадения сокета(допустима 1 ошибка) и встроенной графики*//
void find_proc(Processor z);


void main()
{
	system("chcp 1251");
	setlocale(LC_ALL, "rus");

	char socket_find, graph_find;

	int k = 1, menu;
	//*пробная запись*//
	Processor processors = { "intel", "i3-10100f", "LGA9540", 8, 4.7, "Да" };

	printf("*********База данных процессоров*********\n");
	while (k > 0)
	{
		printf("Для продолжения выберите необходимое действие:\n1 - Добавить запись\n2 - Вывести все имеющиеся записи\n3 - Поиск процессора по сокету\n4 - Выход из программы\n");
		scanf("%d", &menu);
		switch (menu)
		{
		case 1:
			processors = add_processor(processors);
			break;
		case 2:
			put_processor(processors);
			break;
		case 3:
			find_proc(processors);
			break;
		case 4:
			k = 0;
			break;
		default:
			printf("Введено неверное значение");
			break;
		}
	}
}

//*Добавление записи*//
Processor add_processor(Processor z)
{
	char name_proc[SIZE], model_proc[SIZE], socket_proc[SIZE], graph_proc[SIZE];
	int cores_proc;
	double hz_proc;
	printf("Введите производителя процессора: ");
	scanf("%s", name_proc);
	printf("Введите модель процессора: ");
	scanf("%s", model_proc);
	printf("Введите сокет процессора: ");
	scanf("%s", socket_proc);
	printf("Введите количество ядер процессора: ");
	while (getchar() != '\n');
	scanf("%d", &cores_proc);
	printf("Введите тактовую частоту процессора(в GHz): ");
	scanf("%lf", &hz_proc);
	printf("Введите наличие интегрированной графики(Да/Нет): ");
	while (getchar() != '\n');
	scanf("%s", graph_proc);
	z = (Processor){ name_proc, model_proc, socket_proc, cores_proc, hz_proc, graph_proc };
	return z;
}

//*Вывод записи*//
int put_processor(Processor z)
{
	printf("Производитель: %s \nМодель: %s\nСокет: %s\nКоличество ядер: %d\nЧастота: %gGHz\nИнтегрированная графика: %s\n\n", z.name, z.model, z.socket, z.cores, z.hz, z.graph);
	return 1;
}

//*Поиск по записи совпадения сокета(допустима 1 ошибка) и встроенной графики*//
void find_proc(Processor z)
{
	int count_coinc = 0;
	char socket_find[SIZE], graph_find[SIZE];
	printf("Введите сокет процессора для поиска: ");
	scanf("%s", socket_find);
	printf("Введите наличие встроенной графики(Да/Нет): ");
	scanf("%s", graph_find);
	for (int i = 0; i < strlen(socket_find); i++)
	{
		if ((socket_find[i] == z.socket[i]) && (strlen(graph_find) == strlen(z.graph))) count_coinc += 1;
	}
	if (count_coinc >= strlen(socket_find) - 1) put_processor(z);
	else printf("Совпадений не найдено.\n");
}