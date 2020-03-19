#include <iostream>
#include "Profiler.h"

using namespace std;
Profiler profiler("kruskal");

int op = 0;
typedef struct Node {
	int key;
	int rank;
	struct Node* parent;
} Node;

Node* makeSet(int key) {

	Node* node = (Node*)malloc(sizeof(Node));
	op += 3;
	node->key = key;
	node->parent = node;
	node->rank = 0;
	return node;
}

void Link(Node*x, Node*y) {
	op++;
	if (x->rank > y->rank)
	{
		op++;
		y->parent = x;
	}
	else x->parent = y;
	if (x->rank == y->rank)
	{
		op++;
		y->rank = y->rank++;
	}
		
}

Node* findSet(Node *x) //path comprassion
{
	op++;
	if (x != x->parent)
		x->parent = findSet(x->parent);
	return x->parent;

}

void unionSet(Node *x, Node *y)// union by rank
{
	Link(findSet(x), findSet(y));
}

typedef struct Edge {
	int weight;
	struct Node*  beg;
	struct Node*  end;
}Edge;

typedef struct Graph {
	// V =  number of vertices
	// E = number of edges
	int V, E;
	// an array of edges
	struct Edge* edges;
}Graph;

Graph* createGraph(int V, int E) {
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->V = V;
	graph->E = E;
	graph->edges = (Edge*)malloc(E * sizeof(Edge));
	return graph;
}


// partition function
int partition(Edge array[], int p, int r) {
	int x = array[r].weight;
	int i = p - 1;
	for (int j = p; j <= r - 1; j++) {
		if (array[j].weight <= x) {
			i++;
			swap(array[i], array[j]);
		}
	}
	swap(array[i + 1], array[r]);
	return i + 1;
}


// quicksort - for sorting the array of edges
void quicksort(Edge array[], int p, int r) {
	int q;
	if (p < r) {
		q = partition(array, p, r);
		quicksort(array, p, q - 1);
		quicksort(array, q + 1, r);
	}
}

Edge* minimumSpanningTree;
int j = 0;

void Kruskal(Graph* graph) {


	//int E = graph->E;
	//int V = graph->V;

	// for each vertex of the graph we make a set with only an element
	for (int v = 1; v <= graph->V; v++)
		makeSet(v);

	minimumSpanningTree = (Edge*)malloc((graph->E)* sizeof(Edge));
	// we sort in ascendign order our vertices
	quicksort(graph->edges, 0, graph->E - 1);

	// we go through the list of edges
	for (int i = 0; i < graph->E; i++) {

		// and we choose the smallest one 
		Edge tempEdge = graph->edges[i];

		Node* x = findSet(tempEdge.beg);
		Node* y = findSet(tempEdge.end);

		// we check if including this edge will make a cycle or not
		// if it won't we add it to the minimumSpanningTree
		if (x != y) {
			if(j<graph->V)
			minimumSpanningTree[j++] = tempEdge;
			unionSet(x, y);
		}
	}

}
void generateG()
{
	profiler.createGroup("Kruskal", "grafic");
	Edge *vect = (Edge*)malloc(40001 * sizeof(Edge));// in asta o sa am edgeuri 	
	for (int n = 100; n <= 10000; n += 100)
	{
		cout << n <<'\n';
		op = 0;
		for (int i = 0; i < n * 4; i++)
		{
			vect[i].beg = makeSet(rand() % n + 1);
			vect[i].end = makeSet(rand() % n + 1);
			vect[i].weight = rand() % 100000; 
		}
		Graph G;
		G.edges = vect;
		G.E = 4 * n;
		G.V = n;
		Kruskal(&G);
		profiler.countOperation("grafic", n, op);

		for (int i = 0; i < 4 * n; i++)
		{
			free(vect[i].beg);// free la vectorul de edgeuri ca imi da overflow
			free(vect[i].end);
		}

	}
	profiler.showReport();
}
int main()
{
	int array[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	//generateG();
	//return 0;
	Node ** nodesArray = (Node**)malloc(10 * sizeof(Node));

	cout << "OPERATIONS ON SETS DEMO\n\n";

	cout << "BEFORE\n";

	for (int i = 0; i < 10; i++) {
		nodesArray[i] = makeSet(array[i]);
		cout << nodesArray[i]->key << " ->  " << findSet(nodesArray[i])->key << "\n";
	}

	cout << "\nAFTER\n";
	// make 5 unions
	unionSet(nodesArray[0], nodesArray[5]);
	unionSet(nodesArray[3], nodesArray[7]);
	unionSet(nodesArray[2], nodesArray[6]);
	unionSet(nodesArray[4], nodesArray[8]);
	unionSet(nodesArray[1], nodesArray[9]);
	unionSet(nodesArray[9], nodesArray[0]);

	for (int i = 0; i < 10; i++) {
		cout << nodesArray[i]->key << " ->  " << findSet(nodesArray[i])->key << "\n";
	}

	cout << "\nKRUSKAL DEMO \n\n";

	int V = 9;
	int E = 14;

	Graph* graph = createGraph(V, E);  // we build a graph with the given numbers

	Node** vertices = (Node**)malloc((V + 1) * sizeof(Node*)); //we build an array of vertices; for each vertex we make a new set
	for (int i = 1; i <= V; i++) {
	vertices[i] = makeSet(i);
	}
	int beg, end, weight;
	//now we add the edges to the graph
	for (int i = 0; i < 14; i++)
	{
	cin >> beg >> end >> weight;
	graph->edges[i].beg = vertices[beg];
	graph->edges[i].end = vertices[end];
	graph->edges[i].weight = weight;
	}

	Kruskal(graph);

	// we print the edges form the minimumSpanningTree
	for (int i = 0; i < j; i++)
	cout << minimumSpanningTree[i].beg->key << " - " << minimumSpanningTree[i].end->key << ", weight: " << minimumSpanningTree[i].weight << "\n";

    getchar();
	getchar();
	return 0;

}