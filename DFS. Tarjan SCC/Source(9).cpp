#include <iostream>

#include "Profiler.h"
#define white 1
#define grey 2
#define black 3
#define tree 4
#define back 5
#define forward 6
#define cross 7

using namespace std;

Profiler profiler("BFS");
int op = 0;
bool topo = true;


int V = 100, component;
int sol[500], contor;
int e = 1000;
int myTime;

typedef struct
{
	int vec[500];
	int topOfStack = 0;
}Stack;

Stack s;

int pop(Stack &s)
{
	return s.vec[--s.topOfStack];
}

void push(int val, Stack &s)
{
	s.vec[s.topOfStack++] = val;
}

typedef struct AdjListNode {
	int destination;
	int edgeType;
	struct AdjListNode*next;
}AdjListNode;

typedef struct AdjList {
	int value;
	int discoveryTime;
	int finishTime;
	int parent;
	int color;
	int comp;
	int index;
	struct AdjListNode *head;  // pointer to head node of list
}AdjList;


typedef struct Graph {
	int V; // number of vertices
	struct AdjList *arrayOfAdjacencyLists;
}Graph;

struct AdjListNode* newAdjListNode(int dest)
{
	struct AdjListNode* newNode =
		(struct AdjListNode*) malloc(sizeof(struct AdjListNode));
	newNode->destination = dest;
	newNode->next = NULL;
	return newNode;
}

void addEdge(struct Graph* graph, int src, int dest)
{
	// A new node is added to the adjacency list of src.  The node is added at the begining
	struct AdjListNode* newNode = newAdjListNode(dest);
	newNode->next = graph->arrayOfAdjacencyLists[src].head;
	graph->arrayOfAdjacencyLists[src].head = newNode;

}

Graph* createGraph(int V, int E) {
	Graph *graph = (Graph*)malloc(sizeof(Graph));
	graph->V = V;
	// each vertex of the graph will have an adjacencylist
	graph->arrayOfAdjacencyLists = (AdjList*)malloc((V + 1) * sizeof(AdjList));
	for (int i = 1; i <= V; i++)
	{
		graph->arrayOfAdjacencyLists[i].value = i;
		graph->arrayOfAdjacencyLists[i].head = NULL; // Initialize each adjacency list as empty by making head as NULL
	}
	
	bool matrix[100][100];
	memset(matrix, 0, sizeof(matrix));
	for (int i = 0; i < E; i++)
	{
		int dest, src;
		do
		{
			dest = rand() % V + 1;
			src = rand() % V + 1;
		} while (dest == src || matrix[src][dest]==1);
		addEdge(graph, src, dest);
		matrix[src][dest] = 1;
	
	}
	return graph;
}


void dfs_visit(Graph *g ,int indice)
{
	//cout << g->arrayOfAdjacencyLists[indice].value << " " ; //afisez valoarea nodului in care sunt cu dfs
	AdjList *nod = &(g->arrayOfAdjacencyLists[indice]);
	op += 2;
	nod->color = grey;
	nod->discoveryTime = myTime++;
	//component++;
	//nod->comp = component;
	//nod->index = component;
	
	AdjListNode *current = nod->head;
	//push(nod->value, s);
	while (current != NULL)
	{
		AdjList *myNext = &(g->arrayOfAdjacencyLists[current->destination]);//in nodurile din lista unui nod am un int destinatie. mie imi trebe nodul ca sa-i pun culoare si parinte. asa ca fac graph->adjList[destinatie]
		op++;
		if (myNext->color == white)
		{
			op++;
			myNext->parent = nod->value;
			dfs_visit(g, myNext->value);
			
			//if (myNext.comp < nod->comp) nod->comp = myNext.comp;
		}
		else if (myNext->color == grey)
		{
			
			topo = false;
			
			//if (myNext.index < nod->comp) nod->comp = myNext.index;

		}
		op++;
		current = current->next;

	}
	op += 2;
	nod->color = black;
	nod->finishTime = myTime++;
	sol[++contor] = nod->value;
	/*if (nod->index == nod->comp)
	{
		
		int thisIndex;
		do {
			thisIndex = pop(s);
			cout << thisIndex << " ";
		} while (thisIndex != indice);
			cout << "\n";
	}*/
}

void dfs(Graph *g)
{

	for (int i = 1; i <= g->V; i++)
	{
		op += 3;
		g->arrayOfAdjacencyLists[i].color = white;
		g->arrayOfAdjacencyLists[i].parent = NULL;
		g->arrayOfAdjacencyLists[i].comp = 100000;
	}
	myTime = 0;
	//component = 0;
	topo = true;
	contor = 0;
	for (int i = 1; i <= g->V; i++)
	{
		if (g->arrayOfAdjacencyLists[i].color == white)
			dfs_visit(g, i);
		//dfs_visit(g, i);
	} 
}

void printGraph(Graph *G )
{
	for (int i = 1; i <= G->V; i++)
	{
		cout << i << "->";
		AdjListNode *current = G->arrayOfAdjacencyLists[i].head;
		while (current != NULL)
		{
			cout << current->destination << " ";
			current = current->next;
		}
		cout << "\n";
	}
}

void prettyPrint(int indice, Graph *G, int space)
{

	for (int i = 1; i <= space; i++) cout << " ";
	cout << indice << "\n";
	for (int i = 1; i <= G->V; i++)
	{
		if (G->arrayOfAdjacencyLists[i].parent == indice)
			prettyPrint(i, G, space + 2);

	}
}

void demoTopo()
{
	int V = 6;
	int E = 10;
	Graph *G;
	do {
 		G = createGraph(V, E);
		dfs(G);
	} while (topo == false);
	printGraph(G);
	for (int i = contor; i >0; i--)
	{
		cout << sol[i] << " ";
	}
	
}


void demoTarjan()
{
	int V = 6;
	int E = 10;
	Graph *G = createGraph(V, E);
	printGraph(G);
	dfs(G);
	

}

void demoDFS()
{
	int V = 6;
	int E = 10;
	Graph *G = createGraph(V, E);
	printGraph(G);
	dfs(G);
	for (int i = 1; i <= V; i++)
	{
		if (G->arrayOfAdjacencyLists[i].parent == NULL)

			prettyPrint(i, G, 0);
	}
}
void averageE()
{
	int e = 9000;
	Graph *g;
	profiler.createGroup("Efix", "serie1");
	for (int n = 100; n <= 200; n+=10)
	{
		op = 0;
		g = createGraph(n, e);
		dfs(g);
		profiler.countOperation("serie1", n, op);
		
	}
	//profiler.showReport();
}
void averageV()
{
	int n = 100;
	Graph *g;
	profiler.createGroup("Vfix", "serie2");
	for (int e = 1000; e <= 5000; e+=100)
	{
		op = 0;
		g = createGraph(n, e);
		dfs(g);
		profiler.countOperation("serie2", e, op);

	}
	//profiler.showReport();
}

int main()
{
	srand(time(NULL));
	//demoTopo();
	//cout << '\n' << '\n';
	//demoTarjan();
	demoDFS();
	//averageE();
	//averageV();
	//profiler.showReport();
	getchar();
	return 0;
}

