#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include "Profiler.h"

Profiler profiler;

#define MAX 10000

using namespace std;

int OP = 0;

int getParent(int i)
{
	return (i-1) / 2;
}

int getLeft(int i)
{
	return 2 * i + 1;
}

int getRight(int i)
{
	return 2 * i + 2;
}


typedef struct node
{
	int key;
	struct node* next;
} Node;

typedef struct
{
	int nr; //numarul listei
	node *first, *last;

}lista;

typedef struct
{
	int val;
	int i;
}heap;

//  nrliste goale, initializare liste
void creareLista(lista list[], int nrListe)
{
	for (int i = 0; i < nrListe; i++)
	{
		list[i].first = list[i].last = NULL;
		list[i].nr = 0;
	}

}

Node *creareNod(int k)
{
	Node *node;
	node = (Node*)calloc(1, sizeof(Node));
	if (node != NULL)
	{
		node->key = k;
		node->next = NULL;
	}
	return node;
}

void adaugaInLista(lista l[], int i, Node *nod)
{
	if (l[i].first == NULL)
		l[i].first = l[i].last = nod;
	else
	{
		l[i].last->next = nod;
		l[i].last = nod;
		l[i].last->next = 0;
	}
	l[i].nr++;
}

void min_heapify(heap a[], int n, int i)
{
	heap aux;
	int left = getLeft(i);
	int right = getRight(i);
	int min = i;

    //stanga<rad
	if (left < n && a[left].val < a[i].val)
		min = left;
	else min = i;

	//min< min anterior
	if (right < n && a[right].val < a[min].val)
		min = right;
        OP += 2;

    //min nu e egal cu radacina
	if (min != i)
	{
		//OP += 3;

		aux = a[i];
		a[i] = a[min];
		a[min] = aux;
		min_heapify(a, n, min);
	}
}
void buildHeap(heap a[], int n)
{

	for (int i = (n / 2) - 1; i >= 0; i--)
		min_heapify(a, n, i);

}

lista* constructInput(int n, int k) {

	int* a = (int*)malloc(n / k * sizeof(int));

	lista* list = (lista *)malloc(k * sizeof(lista));
	//heap* heap1 = (heap *)malloc(k * sizeof(heap));
	Node *z;
	creareLista(list, k);
	for (int i = 0; i < k; i++)
	{
		FillRandomArray(a, n / k +1, 10, 50000, false, 1);
		for (int m = 0; m < n / k + (n%k > i); m++) //cate elemente am de disribuit la final
		{
			z = creareNod(a[m]);
			adaugaInLista(list, i, z);
		}
	}

	return list;
}

/*heap* constructheap(lista list[], int k) {

	heap heap1[50001];

	for (int i = 0; i < k; i++)
	{
		heap1[i].val = list[i].first->key;
		heap1[i].i = i;

		//op += 2;
	}

	return heap1;
}*/

void merge2Lists(lista list1, lista list2, int arr[])
{

	int i = 0;
	Node* n = list1.first;
	Node* m = list2.first;

	while (n != NULL && m != NULL)
	{
		if (n->key < m->key)
		{
			arr[i] = n->key;
			i++;
			n = n->next;
		}
		else {
			arr[i] = m->key;
			i++;
			m = m->next;
		}
	}

	while (n != NULL) {
		arr[i++] = n->key;
		n = n->next;
	}

	while (m != NULL) {
		arr[i++] = m->key;
		m = m->next;
	}
}

void interclasare(lista list[], int n, int size, int B[]) //n liste, size elemente, n size heap
{
	int t = 0;


	heap heap1[50001];

	for (int i = 0; i < n; i++)
	{
		heap1[i].val = list[i].first->key; //punem valorile din nodurile listelor
		heap1[i].i = i; //punem numarul listei din care am luat nodul

		//OP += 2;
	}

	buildHeap(heap1, n);


	OP += 2;


	B[t++] = heap1[0].val; //punem in vectorul mare radacina heapului

	while (n)
	{
		list[heap1[0].i].first = list[heap1[0].i].first->next; //sterg valoarea din lista dupa ce am bagat in heap

		//OP += 2;

		//daca val este egala cu NULL facem "pushHeap"
		if (list[heap1[0].i].first == NULL)
		{
           //OP += 2;

            heap1[0] = heap1[n - 1]; //facem swap cu frunza
			n--;
		}

		else
		{
           //OP += 2;
           heap1[0].val = list[heap1[0].i].first->key; //pun next value din lista aferenta

		}
		min_heapify(heap1, n, 0);

		//OP += 2;

		B[t++] = heap1[0].val;  //t folosit pentru la ce indice am pus in B 
	}
	t--;
	
}

void k_fix()
{
	int vector1[MAX];
	lista lista1[MAX];
	Node *nod1;
	int B[10001];

	int nrListe = 5;
	OP = 0;

	for (int size = 100; size <= 10000; size += 100)
	{
		cout << size << "\n";
		creareLista(lista1, nrListe); //creez liste goale
		for (int a = 0; a < nrListe; a++)
		{
			FillRandomArray(vector1, size / nrListe, 100, 10000, false, 1);
			for (int i = 0; i < size / nrListe; i++)
			{
				nod1 = creareNod(vector1[i]);
				adaugaInLista(lista1, a, nod1);
			}
		}
		interclasare(lista1, nrListe, size, B); //size output

		profiler.countOperation("K=5", size, OP);
		OP = 0;

	}

	nrListe = 10;
	OP = 0;

	for (int size = 100; size <= 10000; size += 100)
	{
		cout << size << "\n";

		creareLista(lista1, nrListe);
		for (int a = 0; a < nrListe; a++)
		{
			FillRandomArray(vector1, size / nrListe, 100, 10000, false, 1);
			for (int i = 0; i < size / nrListe; i++)
			{
				nod1 = creareNod(vector1[i]);
				adaugaInLista(lista1, a, nod1);
			}
		}
		interclasare(lista1, nrListe, size, B);

		profiler.countOperation("K=10", size, OP);
		OP = 0;

	}

	nrListe = 100;
	for (int size = 100; size <= 10000; size += 100)
	{
		cout << size << "\n";
		creareLista(lista1, nrListe);
		for (int a = 0; a < nrListe; a++)
		{
			FillRandomArray(vector1, size / nrListe, 100, 10000, false, 1);
			for (int i = 0; i < size / nrListe; i++)
			{
				nod1 = creareNod(vector1[i]);
				adaugaInLista(lista1, a, nod1);
			}
		}
		interclasare(lista1, nrListe, size, B);

		profiler.countOperation("K=100", size, OP);
		OP = 0;
	}

	profiler.createGroup("Merge K lists", "K=5", "K=10", "K=100");

}

void n_fix()
{
	int vector2[MAX];
	lista lista2[MAX];
	Node *nod2;
	int B[10001];
	int n;


	int size2 = 10000;
	OP = 0;

	for (int nrListe = 10; nrListe <= 500; nrListe += 10)
	{
		creareLista(lista2, nrListe);
		for (int d = 0; d < nrListe; d++)
		{
			FillRandomArray(vector2, size2 / nrListe+1, 10, 10000, false, 1);
			for (int i = 0; i < size2 / nrListe + (size2 % nrListe> d); i++)
			{
				nod2 = creareNod(vector2[i]);
				adaugaInLista(lista2, d, nod2); 
			}
		}
		interclasare(lista2, nrListe, nrListe, B);
		cout << nrListe << "\n";

		profiler.countOperation("Output = 10000", nrListe, OP);
		OP = 0;
	}

}

void printList(lista list) {
	Node * n = list.first;
	while (n != NULL)
	{
		cout << n->key << " ";
		n = n->next;
	}
	cout << "\n";
}

void demo() {
	int size = 13;
	int nrListe = 3;
	lista* l = constructInput(13, 3);
	for (int i = 0; i < nrListe; i++)
		printList(l[i]);
	int B[5000], n;
	interclasare(l, nrListe, size, B);


	for (int i = 0; i < size; i++)
		cout << B[i] << " ";
}


int main()
{
	/*lista* l = constructInput(10, 2);
	for (int i = 0; i < 2; i++)
		printList(l[i]);
	int a[10];

	merge2Lists(l[0], l[1], a);

	for (int i = 0; i <= 9; i++)
		cout<< a[i] << " ";*/

	demo();
	//k_fix();
	//n_fix();
	//profiler.showReport();
	getchar();
	return 0;
}
