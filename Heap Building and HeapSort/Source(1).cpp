
// max_heapify = complexity O (lg n), it determines the maximum of
// A [i], A[left], A[right] and the index is kept in the largest.
// Agorithm ends when the largest is A[i];

// build_max_heap_bu = has a linear execution time( O(n) )
// and generates a heap from an unordered vector given at the input using the buttom-up principle

// top_down = linear complexity, but from the graph it can be
//  observed that is more inefficient (higher constant)
// implements the priority queue
// build max_heap_td = linear execution time

//heapsort= implements the heapsort algorithm, which transformes an input array into a heap,then the heap is sorted
//takes O(nlgn) time, since the call to build_max_heap_bu takes O(n) time and each of the calls to max_heapify takes O(lgn) time


#include "Profiler.h"
#include <cassert>
#include <iostream>
using namespace std;


Profiler p("HeapBuild");

int bu_comp = 0, bu_assign = 0, td_comp, td_assign;

int getLeft( int i)
{
	return 2 * i;
}

int getRight(int i)
{
	return 2 * i + 1;
}

int getParent(int i)
{
	return i / 2;
}
 
void max_heapify(int A[], int n, int i)
{
	int largest = i;
	int left = getLeft(i);
	int right = getRight(i);

	if( left <= n){
		bu_comp++;
		if(A[left]>A[i])
			largest=left;
	}
	if (right <= n) {
		bu_comp++;
		if ( A[right] > A [largest] )
			largest = right;
	}
	if (largest != i) { int aux=A[i];
	                    A[i]=A[largest];
						A[largest]=aux;
						bu_assign+=3;

						max_heapify(A, n, largest);
	}
}

void build_max_heap_BU(int A[], int n) {
	int init = n / 2 ;
	for (int i = init; i > 0; i--)
		max_heapify(A, n, i);
}

void top_down(int B[], int i, int n) {
	int parent = getParent(i);
	if (parent > 0) {
		td_comp++;
		if (B[parent] < B[i]) {
			int aux = B[parent];
			B[parent] = B[i];
			B[i] = aux;
			td_assign += 3;
			top_down(B, parent, n);
		}
	}
}
void build_max_heap_td(int A[], int n) {

	for (int i = 1; i <= n; i++) {
		
		top_down(A, i, n);
	
	}
}

void CopyValues(int old_arr[], int new_arr[], int length) {

	for (int i = 0; i < length; i++) {
		new_arr[i] = old_arr[i];
	}
}

void Print(int arr[], int length) {
	for (int i = 1; i <= length; i++) cout << arr[i] << ' ';
	cout << "\n";
}


void heapsort(int *heap, int size)
{	
	build_max_heap_BU(heap, size);

	while (size > 1)
	{
		int aux = heap[1];
		heap[1] = heap[size];
		heap[size] = aux;
		size--;
		max_heapify(heap, size, 1);
	}
	
}
void demo() {
	int n = 10;

	int arr[11] = { 0, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
	
	int *backup = (int*)malloc(n * sizeof(int));

	CopyValues(arr, backup, n+1);
	cout << "BOTTOM-UP:\n";
	build_max_heap_BU(backup, n);
	Print(backup, n);

	CopyValues(backup, arr, n+1);
	build_max_heap_td(backup, n);
	cout << "TOP-DOWN:\n";
	Print(backup, n);

	CopyValues(backup, arr, n+1);
	heapsort(backup, n);
	cout << "HEAPSORT:\n";
	Print(backup, n);

		cin.get();
	}


void averageCase()
{
	int arr[10001], backup[10001], heap[10001];
	p.createGroup("BUILD_HEAP", "BU_OPERATIONS", "TD_OPERATIONS");
	int repNr = 5;
	for (int i = 100; i <= 10000; i += 100)
	{
		cout << i << "\n";
		
		for (int j = 1; j <= repNr; j++)
		{ 

			FillRandomArray(arr, i + 1);
			CopyArray(backup, arr, i + 1);
			build_max_heap_BU(backup, i);
		
			CopyArray(backup, arr, i + 1);
			build_max_heap_td(backup,i+1);
		
		
		}

		bu_assign /= 5;
		bu_comp /= 5;
		td_assign /= 5;
		td_comp /= 5;

		p.countOperation("BU_OPERATIONS", i, bu_comp + bu_assign);
		p.countOperation("TD_OPERATIONS", i, td_comp + td_assign);
	
		
		bu_comp = 0; bu_assign = 0; td_comp = 0; td_assign=0;


	}
	

	p.showReport();

}
int main()
{
	demo();
	//averageCase();
	
	getchar();
	return 0;
}