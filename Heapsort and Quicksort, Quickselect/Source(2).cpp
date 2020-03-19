#include "Profiler.h"
#include <cassert>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

Profiler p("Heapsort&Quicksort");

int heap_comp = 0, heap_assign = 0, q_comp = 0, q_assign = 0;

int getLeft(int i)
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

	if (left <= n) {
		heap_comp++;
		if (A[left] > A[i])
			largest = left;
	}
	if (right <= n) {
		heap_comp++;
		if (A[right] > A[largest])
			largest = right;
	}
	if (largest != i) {
		int aux = A[i];
		A[i] = A[largest];
		A[largest] = aux;
		heap_assign += 3;

		max_heapify(A, n, largest);
	}
}

void build_max_heap_BU(int A[], int n) {
	int init = n / 2;
	for (int i = init; i > 0; i--)
		max_heapify(A, n, i);
}


void heapsort(int *heap, int size)
{
	build_max_heap_BU(heap, size);

	while (size > 1)
	{
		int aux = heap[1];
		heap[1] = heap[size];
		heap[size] = aux;
		heap_assign += 3;
		size--;
		max_heapify(heap, size, 1);
	}

}

int partition(int A[], int p, int r) {
	int x = A[r];
	int i = p - 1;
	for (int j = p; j <= r - 1; j++) {
		q_comp++;
		if (A[j] <= x) {
			
			i++;
			int aux = A[i];
			A[i] = A[j];
			A[j] = aux;
			q_assign += 3;
		}
	}
	int aux1 = A[i + 1];
	A[i + 1] = A[r];
	A[r] = aux1;
	q_assign += 3;
	return i + 1;
}

int random(int min, int max) {
	srand(time(NULL));
	return(min + rand() % (max-min+1));
} 

int randomized_partition(int A[], int p, int r) {
	int i = random(p, r);
	int aux = A[r];
	A[r] = A[i];
	A[i] = aux;
	q_assign += 3;
	return partition (A, p, r);
}

void randomized_quicksort(int A[], int p, int r) {
	if (p < r){
		int q = randomized_partition(A, p, r);
		randomized_quicksort(A, p, q - 1);
		randomized_quicksort(A, q + 1, r);

	}
}

int randomized_select(int A[], int p, int r, int i) {
	if (p == r) return A[p]; //the subarray [p,r] consists of just one element and the algorithm returns it
	int q = randomized_partition(A, p, r);//partitioning into 2 arrays, where q is the pivot
	int k = q - p + 1; //the no of elements in the low side of the partition +1 for the pivot
	if (i == k) return A[q]; //checks wether the A[q] is the ith smallest element
	else if (i < k) return randomized_select(A, p, q - 1, i);
	else return randomized_select(A, q + 1, r, i - k); //the desired element is the (i-k) smallest element of A[q+1,r], since we know there are k elements smaller than i
}

void CopyValues(int old_arr[], int new_arr[], int length) {

	for (int i = 0; i <= length; i++) {
		new_arr[i] = old_arr[i];
	}
}

void Print(int arr[], int length) {
	for (int i = 0; i <= length; i++) cout << arr[i] << ' ';
	cout << "\n";
}

void demo() {
	int n = 10;

	int arr[11] = { 0, 9, 7, 6, 3, 1, 2, 5, 4, 8, 10 };

	int *backup = (int*)malloc(n * sizeof(int));

	CopyValues(arr, backup, n + 1);
	cout << "HEAPSORT:\n";
	heapsort(backup, n);
	Print(backup, n);

	CopyValues(backup, arr, n + 1);
	randomized_quicksort(backup,1, n);
	cout << "RANDOMIZED-QUICKSORT:\n";
	Print(backup, n);

	CopyValues(backup, arr, n + 1);
	cout << "RANDOMIZED_SELECT: "<< randomized_select(backup, 1, n, 2);

	cin.get();
}

void averageCase() {
	int arr[10001], backup[10001];
	p.createGroup("ANALYSIS", "HEAPSORT_OPERATIONS", "QUICKSORT_OPERATIONS");
	int repNr = 5;

	for (int i = 100; i <= 10000; i += 100)
	{
		cout << i << "\n";
		for (int j = 1; j <= repNr; j++)
		{
			FillRandomArray(arr, i + 1);
			CopyArray(backup, arr, i + 1);
			heapsort(backup, i);
			//cout << IsSorted(backup, i)<<"\n";


			CopyArray(backup, arr, i + 1);
			randomized_quicksort(backup, 1, i);
			//cout << IsSorted(backup, i) << "\n";
		}
		heap_assign /= repNr;
		heap_comp /= repNr;
		q_assign /= repNr;
		q_comp /= repNr;


		p.countOperation("HEAPSORT_OPERATIONS", i, heap_comp + heap_assign);
		p.countOperation("QUICKSORT_OPERATIONS", i, q_comp + q_assign);


		heap_comp = 0; heap_assign = 0; q_comp = 0; q_assign = 0;

	}
	p.showReport();
}

int partitionBest( int A[], int p, int r) {
	int q = A[(p + r) / 2];
	int aux = A[(p + r) / 2];
	A[(p + r) / 2] = A[r];
	A[r] = aux;
	q_assign += 3;
	return partition(A, p, r);

}
 
void best_quicksort(int A[], int p, int r) {
	if (p < r) {
		int q = partitionBest(A, p, r);
		best_quicksort(A, p, q - 1);
		best_quicksort(A, q + 1, r);

	}
}

void bestCase()
{
	p.createGroup("BEST_QUICKSORT", "BEST_QUICKSORT_OPERATIONS");
	int arr[10001];

	FillRandomArray(arr, 10001, 10, 50000, false, ASCENDING);

	for (int i = 100; i <= 10000; i += 100)
	{
		cout << i << "\n";
		best_quicksort(arr, 1, i);

		p.countOperation("BEST_QUICKSORT_OPERATIONS", i, q_comp + q_assign);
		q_comp = 0; q_assign = 0;
	}

	
	p.showReport();
}

void worst_quicksort(int A[], int p, int r) {
	if (p < r) {
		//q=partition(a,p,r)
		int q = partition(A, p, r);
		worst_quicksort(A, p, q - 1);
		worst_quicksort(A, q + 1, r);

	}
}
void worstCase()
{
	p.createGroup("WORST_QUICKSORT", "WORST_QUICKSORT_OPERATIONS");
	int arr[10001];

	FillRandomArray(arr, 10001, 10, 50000, false, ASCENDING);

	for (int i = 100; i <= 10000; i += 100)
	{
		cout << i << "\n";
		worst_quicksort(arr, 1, i);

		p.countOperation("WORST_QUICKSORT_OPERATIONS", i, q_comp + q_assign);
		q_comp = 0; q_assign = 0;
	}


	p.showReport();
}

int main()
{
	demo();
	//averageCase();
	//bestCase();
	//worstCase();

	getchar();
	return 0;
}
