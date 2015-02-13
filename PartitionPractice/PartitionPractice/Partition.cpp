#include <iostream>

using namespace std;

void Swap(int * a, int * b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void Partition(int * arr, int size){
	int pivot = arr[size - 1];
	int wall = -1;

	for (int i = 0; i < size - 1; ++i){
		if (arr[i] <= pivot){
			++wall;
			Swap(&(arr[wall]), &(arr[i]));
		}
	}
	++wall;
	Swap(&(arr[wall]), &(arr[size-1]));
}

int main(void){
	int arr[] = { 2, 8, 7, 1, 3, 5, 6, 4 };
	int size = sizeof(arr) / sizeof(int);

	Partition(arr, size);
	getchar();
	return 0;
}