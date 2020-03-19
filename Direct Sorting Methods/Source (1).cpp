
/*
1.Selection sort ---------------------------------------------------
-searches the minimum, starting with the position 1, swaping the elements from (1 to n-1) with the minimum found

******BEST CASE: (ordered array)
ASSIGNMENTS = 0 --as the array is sorted, there will be no swaps
COMPARISONS = n * n-1 / 2 (the first element is compared with n-1 elements, the second one with n-2 etc.)
-> the number of the assignments in best case este 0 ( from best case)
-> the number of the compasrisons has a quadratic form (n^2)
-> the total number of operations has a quadratic form( just compariSONS)

******WORST CASE: an array like ( 2 3 4 5 6 7 1 - after each iteration, "the next minimum" is found at the end of the array)
ASSIGNMENTS = 3 * (n - 1) -- because the swap function has 3 assignments operations
COMPARISONS = n * n-1 / 2
-> the number of assignments is liniar
-> the number of comparisons has a quadratic form
-> the total number of operations has a quadratc form

*****-AVERAGE CASE:
-> the number of comparisons has a quadratic form ( n * n-1 / 2 )
-> the number of assignments is liniar
-> the total number of operations has a quadratic form

=> efficiency: O(n^2)
=> number of comparisons is constant
=> stability:unknown

2.Insertion sort ------------------------------------------------------------
-an array that has the first element already sorted and the rest of n-1 are unsorted
-takes the first unsorted element and introduces it in the already sorted array(+ elements shifts)

*****BEST CASE: ---sorted array
ASSIGNMENTS = 2*n-1
> number of comparisons is n * log (n) (graph)
-> the number of assignments is linear
-> the total number of operations is n * log (n)

***** WORST CASE: - sorted in descending order
-> the number of comparisons is linear (graph)
-> the number of attributions is linear
-> the total number of operations is linear

***** CASE:
-> the number of comparisons is linear (graph)
-> the number of attributions is linear
-> the total number of operations is linear

=> efficiency O (n ^ 2)
=> The algorithm is stable

3.Bubble sort ---------------------------------------------- ---------------------------------------
-vector is not sorted => cross the vector by comparing the consecutive elements two by two
and reversing if necessary; after each scroll, the maximum reaches to the right

***** BEST CASE: --- sorted sort
NR ATTRIBUTION = 0
NR COMPARATIES = n-1
-> the number of comparisons is linear (graphical)
-> the number of assignments is 0
-> the total number of operations is linear

***** WORST CASE: - sorted in descending order
NR ATRIBUTIONS = 3 * n-1 * n / 2
NR COMPARATIES = n-1 * n / 2
-> the number of comparisons is quadratic (graph)
-> the number of attributions is quadratic
-> the total number of operations is quadratic

***** AVERAGE CASE:
NR ATRIBUTIONS = ..
NR COMPARATIES = ..
-> the number of comparisons is quadratic (graph)
-> the number of attributions is quadratic
-> the total number of operations is quadratic

=> efficiency is O (n ^ 2)
=> the algorithm is stable
*/


#include "Profiler.h"
#include <cassert>
#include <iostream>
using namespace std;
Profiler profiler("sorting");



void insert_sort(int *arr, int n)
{
	for (int j = 2; j <= n; j++) //the first element in the arrray is considered to be already sorted
	{
		int buff = arr[j];  // the first unsorted element has to be selected 
		profiler.countOperation("insert_assign", n);

	    //Insert arr[j] into the sorted sequence arr[1...j-1]
		int i = j - 1;
		while (i >= 0 && buff < arr[i])
		{
			profiler.countOperation("insert_comp", n);
			
			arr[i + 1] = arr[i];
			i--;
			profiler.countOperation("insert_assign", n);
			
		}
		//if buff is not smaller than arr[i], still check if i>=0;
		if(i>=0) profiler.countOperation("insert_comp", n);
		
		arr[i + 1] = buff;

		profiler.countOperation("insert_assign",n);
	}
}
//for the selection sort, the array is considered to have 2 parts:1 sorted and 1 unsorted, but in fact, the whole array is unsorted
void selection_sort(int *v, int size) {
	int poz, aux;
	for (int i = 1; i < size; i++) {
		poz = i;
		for (int j = i + 1; j < size; j++) {
			profiler.countOperation("selection_comp", size);
			
			if (v[j] < v[poz])
				poz = j;
		}
		if (i != poz) {
			profiler.countOperation("selection_assign", size, 3);
		
			aux = v[i];
			v[i] = v[poz];
			v[poz] = aux;
		}

	}
	
}
void bubble_sort(int *v, int size) {
	
	bool ok;
	int k = 0;
	do {
		ok = false;
		for (int i = 1; i <= size - 1 - k; i++) {
			profiler.countOperation("bubble_comp", size);
		
			if (v[i] > v[i + 1]) {
				profiler.countOperation("bubble_assign", size, 3);
				int aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				ok = true;
			}
		}
		k++;
	} while (ok);
}
void CopyValues(int old_arr[], int new_arr[], int length) {
	
	for (int i = 0; i < length; i++) {
		new_arr[i]=old_arr[i];
	}
}

void Print(int arr[], int length) {
	for (int i = 1; i <= length; i++) cout << arr[i] << ' ';
	cout << "\n";
}

void demo() {
	int n = 10;
	int arr[] = { 0,8,9,1,4,3,2,5,7,6,0};
	int *backup = (int*)malloc(n * sizeof(int));
	
	CopyValues(arr, backup, n);	
	cout << "Insertion sort:\n";
	insert_sort(backup, n);
	Print(backup,n);
	
	CopyValues(backup,arr, n);
	selection_sort(backup,n);
	cout << "Selection sort\n";
    Print(backup, n);
	
	CopyValues(backup,arr, n);
	bubble_sort(backup, n); 
	cout << "Bubble sort:\n";
	Print(backup, n);

	cin.get();
    
}
void average_case() {
	profiler.createGroup("AVG_OPERATIONS", "insert_operations", "selection_operations", "bubble_operations");
	profiler.createGroup("COMP_AVG_OPERATIONS", "insert_comp", "selection_comp", "bubble_comp");
	profiler.createGroup("ASSIGN_AVG_OPERATIONS", "insert_assign", "selection_assign", "bubble_assign");
	int rep;
	int arr[10001], backup[10001];
	for (rep = 1; rep <= 5; rep++)
	{
		FillRandomArray(arr, 1000);
		CopyValues(arr, backup, 1000);
		for (int n = 100; n <= 1000; n += 100) 
		{
			cout << n << "\n";

			
			insert_sort(arr, n);

			CopyValues(backup, arr, n);
			selection_sort(arr, n);

			CopyValues(backup, arr, n);
			bubble_sort(arr, n);

		}
	}
	profiler.addSeries("insert_operations", "insert_comp", "insert_assign");
	profiler.addSeries("selection_operations", "selection_comp", "selection_assign"); 
	profiler.addSeries("bubble_operations", "bubble_comp", "bubble_assign");
	
	profiler.divideValues("insert_operations", 5);
	profiler.divideValues("insert_comp", 5);
	profiler.divideValues("insert_assign", 5);
	profiler.divideValues("selection_operations", 5);
	profiler.divideValues("selection_comp", 5);
	profiler.divideValues("selection_assign", 5); 
	profiler.divideValues("bubble_operations", 5);
	profiler.divideValues("bubble_comp", 5);
	profiler.divideValues("bubble_assign", 5);
	profiler.showReport();
}

void worst_case()
{
	profiler.createGroup("WORST_OPERATIONS", "insert_operations", "selection_operations", "bubble_operations");
	profiler.createGroup("COMP_WORST_OPERATIONS", "insert_comp", "selection_comp", "bubble_comp");
	profiler.createGroup("ASSIGN_WORST_OPERATIONS", "insert_assign", "selection_assign", "bubble_assign");
	int arr[10001], backup[10001];
	
		FillRandomArray(arr, 1000, 10, 50000, false,  DESCENDING);  
		CopyValues(arr, backup, 1000);
		for (int n = 100; n <= 1000; n += 100)  
		{
			cout << n << "\n";

            insert_sort(arr, n);

			CopyValues(backup, arr, n);
			selection_sort(arr, n);

			CopyValues(backup, arr, n);
			bubble_sort(arr, n);

		}
	
	profiler.addSeries("insert_operations", "insert_comp", "insert_assign");
	profiler.addSeries("selection_operations", "selection_comp", "selection_assign"); 
	profiler.addSeries("bubble_operations", "bubble_comp", "bubble_assign");
	profiler.showReport();
}

void best_case()
{
	profiler.createGroup("BEST_OPERATIONS", "insert_operations", "selection_operations", "bubble_operations");
	profiler.createGroup("COMP_BEST_OPERATIONS", "insert_comp", "selection_comp", "bubble_comp");
	profiler.createGroup("ASSIGN_BEST_OPERATIONS", "insert_assign", "selection_assign", "bubble_assign");
	int arr[10001], backup[10001];

	FillRandomArray(arr, 1001, 10, 50000, false, ASCENDING);  
	CopyValues(arr, backup, 1001);
	for (int n = 100; n <= 1000; n += 100)
	{
		cout << n << "\n";

		CopyValues(backup, arr, 1001);
		insert_sort(arr, n);
		
		profiler.countOperation("bubble_assign", n, 0);
		profiler.countOperation("bubble_comp", n, 0);
		profiler.countOperation("selection_assign", n, 0);
		profiler.countOperation("selection_comp", n, 0);

		CopyValues(backup, arr, 1001);
		selection_sort(arr, n);

		CopyValues(backup, arr, 1001);
		bubble_sort(arr, n);

	}

	profiler.addSeries("insert_operations", "insert_comp", "insert_assign");
	profiler.addSeries("selection_operations", "selection_comp", "selection_assign");
	profiler.addSeries("bubble_operations", "bubble_comp", "bubble_assign");
	profiler.showReport();
} 

int main() {
	demo();
	//average_case();
	//worst_case();
	//best_case();

	getchar();
	return 0;
}