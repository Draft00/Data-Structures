#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct _lst
{
	int numb;
	struct _lst* next; // указатель на следующий элемент
	struct _lst* prev; // указатель на предыдущий элемент
} list;

list* head, * cur;
int n = 10;
short* mass, * draft;
double summ_for_mass = 0, summ_for_list = 0;

void init(int a)
{
	list* lst;
	lst = (list*)malloc(sizeof(list));
	lst->numb = a;
	lst->next = NULL;
	lst->prev = NULL;
	head = lst;
	cur = head;
}

void full()
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		list* temp, * p;
		temp = (list*)malloc(sizeof(list));
		p = cur->next;
		cur->next = temp;
		temp->numb = rand() % 9 + 1;
		temp->next = p;
		temp->prev = cur;
		if (p != NULL)
			p->prev = temp;
		cur = temp;
	}
}

void full_mass()
{
	list* temp = head->next;
	for (int i = 0; i < n; i++)
	{
		mass[i] = temp->numb;
		draft[i] = temp->numb;
		temp = temp->next;
	}
}

void sort_mass()
{
	for (int i = 1; i < n; i++)
	{
		int current = mass[i];
		int poz = i - 1;
		while (poz >= 0 && mass[poz] > current)
		{
			mass[poz + 1] = mass[poz];
			poz--;
		}
		mass[poz + 1] = current;
	}
}


void delete_connection(list * current)
{
	list* prev, * next;
	prev = current->prev;
	next = current->next;
	if (prev != NULL)
		prev->next = current->next;
	if (next != NULL)
		next->prev = current->prev;
}

void add_conection(list * temp, list * p)
{
	list* y = temp->next;
	p->prev = temp;
	p->next = y;
	temp->next = p;
	y->prev = p;
}
void sort_list()
{
	list* temp = head->next;
	list* p = temp->next;
	list* p2 = p->next;
	int flag = 0;
	for (int i = 1; i < n; i++)
	{
		while (temp != head && temp->numb > p->numb)
		{
			temp = temp->prev;
			flag = 1;
		}
		if (flag)
		{
			delete_connection(p);
			add_conection(temp, p);
			flag = 0;
		}
		p = p2;
		temp = p2->prev;
		if (p->next)
			p2 = p->next;
	}
}

void copy_list()
{
	list* temp = head->next;
	for (int i = 0; i < n; i++)
	{
		temp->numb = draft[i];
		temp = temp->next;
	}
}
int main()
{
	clock_t start, end;
	double end2;
	init(0);
	scanf("%d", &n);
	mass = (short*)malloc(n * sizeof(short));
	draft = (short*)malloc(n * sizeof(short));
	printf("Hello world!\n");
	full();
	full_mass();

	printf("\n");

	for (int i = 0; i < 10; i++)
	{
		start = clock();
		sort_mass();
		end = clock();
		end2 = (double)(end - start) / CLOCKS_PER_SEC;
		summ_for_mass += end2;
		printf("This if for mass: %f\n", end2);
		memcpy(mass, draft, n * sizeof(short));
	}
	printf("End value: %lf\n", summ_for_mass / 10);

	for (int i = 0; i < 10; i++)
	{
		start = clock();
		sort_list();
		end = clock();
		end2 = (double)(end - start) / CLOCKS_PER_SEC;
		summ_for_list += end2;
		printf("This is for list: %f\n", end2);
		copy_list();
	}
	printf("End value: %lf", summ_for_list / 10);

	/*
	list *j = head->next;
	for (int i = 0; i < n; i++)
	{
		printf("%d ", j->numb);
		j = j->next;
	}*/
	//printf("%d %d", head->numb, mass[1]);
	return 0;
}
