#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <limits.h>
#include "Profiler.h"
using namespace std;

Profiler profiler("BFS");

#define white 1
#define grey 2
#define black 3
#define MAX 300
#define inf 10000000

int op = 0;
int queue_array[MAX];
int rear = -1;
int front = -1;
int V = 100;
int e = 1000;

void enqueue(int x) {
	if (rear == MAX - 1)
		printf("Overflow \n");
	else
	{
		if (front == -1)
			front = 0;
		rear = rear + 1;
		queue_array[rear] = x;
	}
}

int dequeue() {
	if (front == -1 || front > rear)
	{
		printf("Underflow \n");
		return NULL;
	}
	else
	{
		int x = queue_array[front];
		front = front + 1;
		return x;
	}
}

bool isEmpty() {
	if (front == -1 || front > rear) return true;
	else return false;
}

typedef struct AdjListNode {
	int destination;
	struct AdjListNode*next;
}AdjListNode;

typedef struct AdjList {
	int parent;
	int color;
	int distance;
	struct AdjListNode *head;  // pointer to head node of list
}AdjList;


typedef struct Graph {
	int V; // number of vertices
	struct AdjList *arrayOfAdjacencyLists; 
}Graph;


Graph* createGraph(int V) {
	Graph *graph = (Graph*)malloc(sizeof(Graph));
	graph->V = V;
	// each vertex of the graph will have an adjacencylist
	graph->arrayOfAdjacencyLists = (AdjList*)malloc((V+1) * sizeof(AdjList));

	// Initialize each adjacency list as empty by making head as NULL
	for (int i = 1; i <= V; i++) {
		graph->arrayOfAdjacencyLists[i].head = NULL;
	}

	return graph;
}

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

	// Since graph is undirected, add an edge from dest to src also
	newNode = newAdjListNode(src);
	newNode->next = graph->arrayOfAdjacencyLists[dest].head;
	graph->arrayOfAdjacencyLists[dest].head = newNode;
}

void BFS(Graph* G, int s) {
	front = -1;
	rear = -1;

	for (int i = 1; i <= G->V; i++)
	{
		op += 3;
		G->arrayOfAdjacencyLists[i].color = white;
		G->arrayOfAdjacencyLists[i].distance = inf;
		G->arrayOfAdjacencyLists[i].parent = NULL;
	}
	
	op += 3;
	enqueue(s);
	G->arrayOfAdjacencyLists[s].color = grey;
	G->arrayOfAdjacencyLists[s].distance = 0;

	while (!isEmpty())
	{
		op++;
		int srcNode = dequeue();

		AdjListNode *current = G->arrayOfAdjacencyLists[srcNode].head; //current e nodul cu care ma plimb prin lista
		while (current != NULL)
		{
			op += 2;
			int dest = current->destination;
			if (G->arrayOfAdjacencyLists[dest].color == white)
			{
				op += 4;
				G->arrayOfAdjacencyLists[dest].color = grey;
				G->arrayOfAdjacencyLists[dest].distance = G->arrayOfAdjacencyLists[srcNode].distance+1;
				G->arrayOfAdjacencyLists[dest].parent = srcNode;
				enqueue(dest);
			}
			op++;
			current = current->next;
		}

		op++;
		G->arrayOfAdjacencyLists[srcNode].color = black;
	}
}
void prettyPrint(int s, Graph *G, int space)
{
	
	for (int i = 1; i <= space; i++) cout << " ";
	cout << s << "\n";
	for (int i = 1; i <= G->V; i++)
	{
		if (G->arrayOfAdjacencyLists[i].parent == s)
			prettyPrint(i, G, space + 2);

	}
}
void demo()
{
	int V = 8;
	Graph *G = createGraph(V);
	addEdge(G, 1, 2);
	addEdge(G, 2, 3);
	addEdge(G, 3, 4);
	addEdge(G, 4, 5);
	addEdge(G, 5, 6);
	addEdge(G, 6, 7);
	addEdge(G, 7, 8);
	addEdge(G, 4, 8);
	addEdge(G, 7, 5);
	addEdge(G, 1, 3);
	addEdge(G, 5, 2);

	for (int i = 1; i <= V; i++)
	{
		cout << i << " ";
		AdjListNode *current = G->arrayOfAdjacencyLists[i].head;
		while (current != NULL)
		{
			cout << current->destination << " ";
			current = current->next;
		}
		cout << "\n";
	}

	BFS(G, 1);

	prettyPrint(1, G, 0);
}
void graph1()
{
	profiler.createGroup("EFix", "gr");
	int E = 4500;

	for (int V = 100; V <= 200; V += 10)
	{
		op = 0;
		Graph *G=createGraph(V);
		for (int i = 0; i < E; i++)
		{
			addEdge(G, rand() % V + 1, rand() % V + 1);
		}
		BFS(G, 1);
		profiler.countOperation("gr", V, op);
	}

}

void graph2()
{
	profiler.createGroup("VFix", "gr1");
	int V = 100;

	for (int E = 100; E <= 4500; E += 100)
	{
		op = 0;
		Graph *G = createGraph(V);
		for (int i = 0; i < E; i++)
		{
			addEdge(G, rand() % V + 1, rand() % V + 1);
		}
		BFS(G, 1);
		profiler.countOperation("gr1", E, op);
	}

}
void main()
{
	demo();
	//graph1();
	//graph2();
	profiler.showReport();
	getchar();
}
