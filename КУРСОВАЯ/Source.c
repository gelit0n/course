#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define SIZE 21

struct processor {
	int number;
	char* name[SIZE];
	char* model[SIZE];
	char* socket[SIZE];
	int cores;
	float hz;
	char* graph[SIZE];
};
typedef struct processor Processor;

//*Определение последней записи*//
int last_processor(void);
//*Добавление записи*//
Processor add_processor(Processor *z, int number);
//*Вывод записей*//
int put_processor(Processor *z, int number);
//*Поиск по записи совпадения сокета(допустима 1 ошибка) и кол-ву ядер*//
int find_proc(Processor *z, int number);
//*Сортировка по тактовой частоте и наличию встроенной графики*//
int sort_proc(Processor *z, int number);


void main()
{
	system("chcp 1251");
	system("cls");
	setlocale(LC_ALL, "rus");

	//*k - переменная зациклювающая меню выбора, menu - переменная для выбора в меню, start_write - переменная, хранящая последнюю запись*//
	//* start_size - переменная для выделения изначальной памяти*//
	int k = 1, menu, start_write = last_processor(), start_size = 20;
	
	//*Объявление динамического массива и выделение памяти*//
	Processor* processors;
	processors = (Processor*)malloc(start_size * sizeof(Processor));

	//*Запись элементов из файла в динамический массив*//
	FILE* read = fopen("processors.txt", "r");
	for (int i = 0; i < start_write; i++)
	{
		fscanf(read, "%d\n", &processors[i].number);
		fgets(&processors[i].name, SIZE, read);
		fgets(&processors[i].model, SIZE, read);
		fgets(&processors[i].socket, SIZE, read);
		fscanf(read, "%d\n", &processors[i].cores);
		fscanf(read, "%f\n", &processors[i].hz);
		fgets(&processors[i].graph, SIZE, read);
	}

	fclose(read);

	printf("*********База данных процессоров*********\n");
	while (k > 0)
	{
		system("cls");
		printf("Для продолжения выберите необходимое действие:\n1 - Добавить запись\n2 - Вывести все имеющиеся записи\n3 - Поиск процессора по сокету\n4 - Сортировать процессоры по количеству ядер\n5 - Выход из программы\n");
		scanf("%d", &menu);
		switch (menu)
		{
		case 1:
			if (start_size <= last_processor())
			{
				start_size += 10;
				processors = (Processor*)malloc(start_size * sizeof(Processor));
			}
			add_processor(processors, start_write);
			start_write += 1;
			printf("Запись добавлена\n");
			break;
		case 2:
			printf("%d", last_processor());
			put_processor(processors, start_write);
			system("pause");
			break;
		case 3:
			find_proc(processors, start_write);
			printf("Поиск окончен");
			system("pause");
			break;
		case 4:
			sort_proc(processors, start_write);
			system("pause");
			break;
		case 5:
			k = 0;
			break;
		default:
			printf("Введено неверное значение");
			break;
		}
	}
	free(processors);
}

//*Определение последней записи*//
int last_processor(void)
{
	int number_proc = 0;

	FILE* read = fopen("processors.txt", "r");

	//*Счётчик кол-ва всех строк*//
	while (!feof(read))
	{
		if (fgetc(read) == '\n')
		number_proc += 1;
	}

	fclose(read);

	//*Определение кол-ва всех записей в файле (т.к. в структуре 7 строк)*//
	number_proc /= 7;

	return number_proc;
}

//*Вывод записей*//
int put_processor(Processor* z, int number)
{
	system("cls");

	for (int i = 0; i < number; i++)
	{
		printf("Номер записи: %d\n", z[i].number);
		printf("Производитель: %s", &z[i].name);
		printf("Модель: %s", &z[i].model);
		printf("Сокет: %s", &z[i].socket);
		printf("Количество ядер: %d\n", z[i].cores);
		printf("Тактовая частота: %gGHz\n", z[i].hz);
		printf("Наличие встроенной графики: %s\n", &z[i].graph);
	}

	return 1;
}

//*Добавление записи*//
Processor add_processor(Processor *z, int number)
{
	system("cls");
	FILE* edit = fopen("processors.txt", "a");
	z[number].number = number + 1;
	printf("Введите производителя процессора: ");
	while (getchar() != '\n');
	fgets(z[number].name, SIZE, stdin);
	printf("Введите модель процессора: ");
	fgets(z[number].model, SIZE, stdin);
	printf("Введите сокет процессора: ");
	fgets(z[number].socket, SIZE, stdin);
	printf("Введите количество ядер процессора: ");
	scanf("%d", &z[number].cores);
	printf("Введите тактовую частоту процессора(в GHz): ");
	scanf("%f", &z[number].hz);
	printf("Введите наличие интегрированной графики(Да/Нет): ");
	while (getchar() != '\n');
	fgets(z[number].graph, SIZE, stdin);
	fprintf(edit, "%d\n%s%s%s%d\n%g\n%s", z[number].number, &z[number].name, &z[number].model, &z[number].socket, z[number].cores, z[number].hz, &z[number].graph);
	fclose(edit);
	return *z;
}

//*Поиск по записи совпадения сокета(допустима 1 ошибка) и кол-ву ядер*//
int find_proc(Processor *z, int number)
{
	system("cls");
	FILE* read = fopen("processors.txt", "r");

	int find = 0, cores_find;
	char socket_find[SIZE], socket_proc[SIZE], cores_proc[SIZE];

	printf("Введите сокет процессора для поиска: ");
	getchar();
	scanf("%s", socket_find);
	socket_find[strlen(socket_find)] = '\0';
	printf("Введите кол-во ядер: ");
	scanf("%d", &cores_find);
	for (int j = 0; j < number - 1; j++)
	{
		memcpy(socket_proc, z[j].socket, SIZE); //*Копирование в другой массив для корректного отображения*//
		for (int i = 0; i < strlen(socket_find); i++)
		{
			if ((socket_find[i] == socket_proc[i]) && (cores_find == (z[j].cores))) find += 1;
		}
		if (find >= strlen(socket_find) - 1) printf("Найдено совпадение: номер записи - %d\n", j + 1); //*- 1 сделано для поиска с одной ошибкой*//
		find = 0;
	}
	return 1;
}

//*Сортировка по тактовой частоте и наличию встроенной графики*//
int sort_proc(Processor *z, int number)
{
	system("cls");
	Processor processors;

	//Создание нового динамического массива, чтобы можно было вывести изначальный неотсортированный массив**//
	Processor* new_processors;
	new_processors = (Processor*)malloc(number * sizeof(Processor));
	memcpy(new_processors, z, number);
	for (int i = 0; i < number; i++)
	{
		new_processors[i] = z[i];
	}
	char graph_proc[SIZE];
	int sort = 1;

	//*Сортировка по тактвой частоте (hz)*//
	while (sort)
	{
		sort = 0;
		for (int i = 1; i < number; i++)
		{
			if (new_processors[i - 1].hz < new_processors[i].hz)
			{
				processors = new_processors[i - 1];
				new_processors[i - 1] = new_processors[i];
				new_processors[i] = processors;
				sort++;
			}
		}
	}

	//*Сортировка по наличию встроенной графики*//
	sort = 1;
	while (sort)
	{
		sort = 0;
		for (int i = 1; i < number; i++)
		{
			memcpy(graph_proc, new_processors[i].graph, SIZE);
			if (strlen(&new_processors[i].graph) < strlen(&new_processors[i - 1].graph))
			{
				processors = new_processors[i - 1];
				new_processors[i - 1] = new_processors[i];
				new_processors[i] = processors;
				sort++;
			}
		}
	}

	//*Вывод сортированного массива*//
	for (int i = 0; i < number; i++)
	{
		printf("Номер записи: %d\n", new_processors[i].number);
		printf("Производитель: %s", &new_processors[i].name);
		printf("Модель: %s", &new_processors[i].model);
		printf("Сокет: %s", &new_processors[i].socket);
		printf("Количество ядер: %d\n", new_processors[i].cores);
		printf("Тактовая частота: %gGHz\n", new_processors[i].hz);
		printf("Наличие встроенной графики: %s\n", &new_processors[i].graph);
	}
	return 1;
}
