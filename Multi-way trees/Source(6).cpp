
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
int root;

typedef struct nodR2 {
	int key;
	int nr_children;
	struct nodR2** children; //array de pointeri
}nodR2;

void pretty_print1(int *a, int size, int parent, int level)
{
	for (int i = 1; i <= size; i++)
	{
		if (a[i] == parent) // am gasit un copil de-al  lui -1		
		{
			for (int j = 0; j < level; j++) cout << "  ";
			cout << i << "\n";
			pretty_print1(a, size, i, level+1);
		}
	}
}
nodR2* T1(int *a, int size)
{
	nodR2* root_R2; //array de noduri

	root_R2 = (nodR2 *)malloc((size+1) * sizeof(nodR2));

	//initializez nodurile din noul array
	for (int i = 1; i <= size; i++)
	{
		root_R2[i].key = i;
		root_R2[i].nr_children = 0;
		//nr copii
		if (a[i] != -1)
			root_R2[a[i]].nr_children++;
		else
			root = i ; //pe ce pozitie e radacina in array de noduri
	}

	//initializez copiii nodurilor
	for (int i = 1; i <= size; i++)
	{
		root_R2[i].children = (nodR2**)malloc(root_R2[i].nr_children * sizeof(nodR2*));
		root_R2[i].nr_children = 0;
	}

	//leg nodul curent de copil sau copilul la nodul curent 
	for (int i = 1; i <= size; i++)
	{
		int j = a[i];
		if (j != -1)
		{
            int indice = root_R2[j].nr_children;
			root_R2[j].children[indice] = &root_R2[i];
			root_R2[j].nr_children++;
		}
	}
	return root_R2;
}
void pretty_print2(nodR2 *t, int level)
{
	if (t == NULL) return;
	for (int i = 0; i < level; i++) { //am ajuns la nodul pe care vreau sa-l afisez
		//cout<<" ";
		printf("  ");
	}

	//cout<<" "<<t->key;
	//cout<<'\n';
	printf("%d   ", t->key);
	printf("\n");
	for (int i = 0; i < t->nr_children; i++) //ma duc si-i afisez copiii la nodul pe care am vrut sa-l afisez
	{
		pretty_print2(t->children[i], level + 1);
	}
}

typedef struct nodR3 {
	int key;
	struct nodR3* son;
	struct nodR3* brother;
}nodR3;

//-1 e primul parinte, 7 e copilul lui, dar dupa 7 e parinte si 2 e right

nodR3* T2(nodR2 *parent, nodR2 *right, int k) //k=> al catelea copil este
	{
		nodR3* p = (nodR3*)malloc(sizeof(nodR3)); //nod din binary transformation

		p->key = right->key; //p e nodul corespunzator lui right, care e de tip R2, iar p de tip R3
		p->brother = NULL; //setez pe NULL pt ca inca nu mi-am facut transformarea
		p->son = NULL;

		//verific daca am legatura stanga(copil)
		if (right->nr_children >0) {
			p->son = T2(right, right->children[0], 0);
		}
		else
			p->son = NULL;

		//creez legatura de brother(dreapta)
		if (parent->nr_children > k+1) {
			p->brother = T2(parent, parent->children[k+1], k + 1); //k+1=>pun urmatorul copil al radacinii 
		}
		else
			p->brother = NULL;
		return p;
	}

	void pretty_print3(nodR3* t, int level)
	{

		for (int i = 0; i < level; i++) {
			cout<<"  ";
			//printf("  ");
		}

        printf("%d   ", t->key);
		printf("\n");

		if (t->son != NULL) {
			pretty_print3(t->son, level + 1);
		}

		if (t->brother != NULL) {
			pretty_print3(t->brother, level);
		}
	}

	int main()
	{
		//int a[2] = { 0,-1 };
	    int a[10] = {0,2,7,5,2,7,7,-1,5,2};
	    int size = 9;

		cout << "Pretty Print 1"<<'\n';
		pretty_print1(a, size, -1, 0);

		cout << '\n'<<"Pretty Print 2"<<'\n';
		nodR2* root_R2;
	    root_R2 = T1(a, size);
		pretty_print2(&root_R2[root], 0); //0 e levelul si spatiile


		nodR3* root_R3 = (nodR3*)malloc(sizeof(nodR3)); //declar rootul
		root_R3->key = root_R2[root].key; //rootul din multicai e acelasi si in binar
		root_R3->son = NULL; //by default
		root_R3->brother = NULL;
		if(root_R2[root].nr_children!=0) //daca radacina nu are niciun copil, ma opresc pt ca nu are rost sa mai fac transformarea
        root_R3->son = T2(&root_R2[root], root_R2[root].children[0], 0); //sestez fiul radacinii, intrucat ea nu are frati
		                  //trimit nodul parinte, nodul copil si al catelea copil este pt parinte
	
		cout << '\n';
		cout<<"Pretty Print 3";
		cout<<'\n';
		pretty_print3(root_R3, 0);
		

		getchar();

		return 0;
	}