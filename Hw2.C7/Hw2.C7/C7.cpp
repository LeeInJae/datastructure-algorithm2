#include <iostream>
#include <stdlib.h>

#define ERROR -1

void Swap(int * a, int * b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int Partition(int * arr, int left, int right){
	int randPos = rand() % (right + 1) + left;
	Swap(&arr[randPos], &arr[right]);
	
	int wall = -1;
	int pivot = arr[right];
	for (int i = 0; i <= right - 1; ++i){
		if (arr[i] <= pivot){
			++wall;
			Swap(&arr[i], &arr[wall]);
		}
	}
	++wall;
	Swap(&arr[wall], &arr[right]);
	return wall;
}

int FindKthNumber(int * arr, int left, int right, int k){
	if (left > right) return ERROR;

	int pivotPos = Partition(arr, left, right);
	if (pivotPos == k)
		return arr[k];
	else if (pivotPos > k){
		return FindKthNumber(arr, left, pivotPos - 1, k);
	}
	return FindKthNumber(arr, pivotPos + 1, right, k);
}

int main(void){
	int arr[] = { 1, 3, 2, 4, 5, 6, 9, 8, 7, 13, 12, 11, 10, 15, 14 };
	int size = sizeof(arr) / sizeof(int);
	int k = 11;
	int res = FindKthNumber(arr,0, size-1, k-1);
	printf("%d\n", res);
	getchar();
	return 0;
}