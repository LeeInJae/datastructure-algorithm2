#include <iostream>

using namespace std;

void Swap(int * a, int * b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int Partition(int * arr, int left, int right){
	int pivot = arr[right];
	int wall = left - 1;

	for (int i = left; i < right; ++i){
		if (arr[i] <= pivot){
			++wall;
			Swap(&(arr[wall]), &(arr[i]));
		}
	}
	++wall;
	Swap(&(arr[wall]), &(arr[right]));
	return wall;
}

void QuickSort(int * arr, int left, int right){
	if (left > right)
		return;

	int pivot = Partition(arr, left, right);
	QuickSort(arr, left, pivot - 1);
	QuickSort(arr, pivot + 1, right);
}

int main(void){
	int arr[] = { 2, 8, 7, 1, 3, 5, 6, 4, 2 };
	int size = sizeof(arr) / sizeof(int);
	QuickSort(arr, 0, size - 1);
	getchar();
	return 0;
}