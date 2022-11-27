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

//*���������� ������*//
Processor add_processor(Processor z);
//*����� ������*//
int put_processor(Processor z);
//*����� �� ������ ���������� ������(��������� 1 ������) � ���������� �������*//
void find_proc(Processor z);


void main()
{
	system("chcp 1251");
	setlocale(LC_ALL, "rus");

	char socket_find, graph_find;

	int k = 1, menu;
	//*������� ������*//
	Processor processors = { "intel", "i3-10100f", "LGA9540", 8, 4.7, "��" };

	printf("*********���� ������ �����������*********\n");
	while (k > 0)
	{
		printf("��� ����������� �������� ����������� ��������:\n1 - �������� ������\n2 - ������� ��� ��������� ������\n3 - ����� ���������� �� ������\n4 - ����� �� ���������\n");
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
			printf("������� �������� ��������");
			break;
		}
	}
}

//*���������� ������*//
Processor add_processor(Processor z)
{
	char name_proc[SIZE], model_proc[SIZE], socket_proc[SIZE], graph_proc[SIZE];
	int cores_proc;
	double hz_proc;
	printf("������� ������������� ����������: ");
	scanf("%s", name_proc);
	printf("������� ������ ����������: ");
	scanf("%s", model_proc);
	printf("������� ����� ����������: ");
	scanf("%s", socket_proc);
	printf("������� ���������� ���� ����������: ");
	while (getchar() != '\n');
	scanf("%d", &cores_proc);
	printf("������� �������� ������� ����������(� GHz): ");
	scanf("%lf", &hz_proc);
	printf("������� ������� ��������������� �������(��/���): ");
	while (getchar() != '\n');
	scanf("%s", graph_proc);
	z = (Processor){ name_proc, model_proc, socket_proc, cores_proc, hz_proc, graph_proc };
	return z;
}

//*����� ������*//
int put_processor(Processor z)
{
	printf("�������������: %s \n������: %s\n�����: %s\n���������� ����: %d\n�������: %gGHz\n��������������� �������: %s\n\n", z.name, z.model, z.socket, z.cores, z.hz, z.graph);
	return 1;
}

//*����� �� ������ ���������� ������(��������� 1 ������) � ���������� �������*//
void find_proc(Processor z)
{
	int count_coinc = 0;
	char socket_find[SIZE], graph_find[SIZE];
	printf("������� ����� ���������� ��� ������: ");
	scanf("%s", socket_find);
	printf("������� ������� ���������� �������(��/���): ");
	scanf("%s", graph_find);
	for (int i = 0; i < strlen(socket_find); i++)
	{
		if ((socket_find[i] == z.socket[i]) && (strlen(graph_find) == strlen(z.graph))) count_coinc += 1;
	}
	if (count_coinc >= strlen(socket_find) - 1) put_processor(z);
	else printf("���������� �� �������.\n");
}