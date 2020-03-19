#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include "Profiler.h"
using namespace std;
Profiler profiler;

#define const1 2
#define const2 3

#define SIZE 10007


//collision=2 identical ids with the same hash key

typedef struct {
	int id;
	char name[30];
}Entry;

Entry* Table[SIZE];
Entry* newEntry(int id, char const *name)
{
	Entry * result = (Entry*)malloc(sizeof(Entry));
	result->id = id;
	strcpy_s(result->name, name);
	return result;
}

int hash_func(int key, int id)
{
	return ((key % SIZE) + const1 * id + const2 * id * id) % SIZE;
}

void clear_hash(Entry *Table[]) {
	for (int i = 0; i < SIZE; i++)
	{
		free(Table[i]);
		Table[i] = NULL;
	}
}

Entry* insert(Entry*  newEntry)
{
	int i, j;


	for (i = 0; i < SIZE; i++)
	{

		j = hash_func(newEntry->id, i);

		if (Table[j] == NULL)
		{
			Table[j] = newEntry;

			return Table[j];
		}
	}
	return NULL;
}

Entry* hashSearch(int id, int &numberTimes)
{
	numberTimes = 0; //cate celule acceseaza ca sa ajunga la celula cautata
	int i = 0;
	int j;
	do
	{

		j = hash_func(id, i);
		numberTimes++;
		if (Table[j] == NULL) {
			return NULL;
		}

		if (Table[j]->id == id) 
		{
			return Table[j];

		}

		
		i++;
	} while (Table[j] != NULL && i != SIZE);
	return NULL;
}



void demo() {

	char nume1[30] = "Name1";
	char nume2[30] = "Name2";
	char nume3[30] = "Name3";
	char nume4[30] = "Name4";
	int value = 0;
	Entry * e1 = newEntry(1, nume1);
	Entry * e2 = newEntry(10009, nume2);
	Entry * e3 = newEntry(10008, nume3);
	Entry * e4 = newEntry(1, nume4);

	insert(e1);
	insert(e2);
	insert(e3);
	insert(e4);

	Entry * found1 = hashSearch(1, value);
	Entry * found2 = hashSearch(2, value);
	Entry * found3 = hashSearch(4, value);
	Entry * found4 = hashSearch(10009, value);

	if (found1 == NULL)
	{
		printf("elementul nu se gaseste in tabel\n");
	}
	else
		printf("%s\n", found1->name);
	if (found2 == NULL)
	{
		printf("elementul nu se gaseste in tabel\n");
	}
	else
		printf("%s\n", found2->name);
	if (found3 == NULL)
	{
		printf("elementul nu se gaseste in tabel\n");
	}
	else
		printf("%s\n", found3->name);
	if (found4 == NULL)
	{
		printf("elementul nu se gaseste in tabel\n");
	}
	else
		printf("%s\n", found4->name);

	

}

void average()
{
	cout<<"FFactor | Avg. Effort found | Max. Effort found | Avg. Effort not-found | Max Effort not-found\n";
	double fillingFactor;
	double fillingFactorArray[] = { 0.8f, 0.85f, 0.9f, 0.95f, 0.99f };
	int op = 0; //indice pt filling factorarray
	int insertedArray[SIZE + 1500];
	int indices[1500];
	int n;
	

	for (int op = 0; op < 5; op++)
	{
		int maxEffortFound = 0; //exista recordul cu key 
		int maxEffortNotFound = 0; //cand cauta si nu exista recordul cu key

		double totalEffortFound = 0; //pt toate cele 1500*5 elemente gasibile
		double totalEffortNotFound = 0; //pt toate cele 1500*5 elemente negasibile
		fillingFactor = fillingFactorArray[op];
		for (int i = 0; i < 5; i++) //5 repetitii pt average
		{
			int effortFound = 0;
			int effortNotFound = 0;



			n = fillingFactor * SIZE; //nr de elemente inserate pt un fillingfactor
			FillRandomArray(insertedArray, n + 1500, 0, 50000, true, UNSORTED); //nu exista dubluri, prin true, n elemente de inserat si restul de 1500 pe care nu o sa le gasesc
			FillRandomArray(indices, 1500, 0, n - 1, true, UNSORTED); // vectori de indici la 1500 de pozitii cu elemente inserate in insertedArray
			for (int j = 0; j < n; j++)
			{
				insert(newEntry(insertedArray[j], "nume")); //toate elementele din insertedArray de la 0 la n-1 le inserez in hashtable
			}
			for (int j = 0; j < 1500; j++) //1500 cazuri si de found si unfound 
			{
				int effortFound = 0;
				int effortNotFound = 0;

				hashSearch(insertedArray[indices[j]], effortFound);
				totalEffortFound += effortFound;
				if (maxEffortFound < effortFound) maxEffortFound = effortFound;


				hashSearch(insertedArray[j + n], effortNotFound);
				totalEffortNotFound += effortNotFound;
				if (maxEffortNotFound < effortNotFound) maxEffortNotFound = effortNotFound;
			}
			clear_hash(Table);

		}

		cout << fillingFactor << "\t\t" << (double)(totalEffortFound / 7500) << "\t\t\t" << maxEffortFound << "\t\t\t" << (double)(totalEffortNotFound / 7500) << "\t\t\t" << maxEffortNotFound << "\n";
		
	}

}

int main() {
	
	
	//demo();
	average();
	getchar();
	return 0; 
}
