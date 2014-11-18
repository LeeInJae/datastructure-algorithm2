#include<stdio.h>
#include<iostream>

void Swap(int * a, int * b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int * Init(int size){
	int * arr = (int *)malloc(sizeof(int) * size);
	for (int i = 0; i < size; ++i){
		arr[i] = rand() % size + 1;
	}
	return arr;
}

int * InitIncrease(int size){
	int * arr = (int *)malloc(sizeof(int) * size);
	for (int i = 0; i < size; ++i){
		arr[i] = i + 1;
	}
	return arr;
}

int * InitDecrease(int size){
	int * arr = (int *)malloc(sizeof(int) * size);
	for (int i = 0; i < size; ++i){
		arr[i] = size - i;
	}
	return arr;
}

void PrintArr(int * arr, int size){
	for (int i = 0; i < size; ++i){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int Partition(int * arr, int left, int right){
	int pivot = arr[right];
	int wall = -1;

	for (int i = 0; i <= right - 1; ++i){
		if (arr[i] <= pivot){
			++wall;
			Swap(&arr[wall], &arr[i]);
		}
	}
	++wall;
	Swap(&arr[wall], &arr[right]);
	return wall;
}

int TestPartition(int * arr, int left, int right, int pivotPos){
	for (int i = left; i < pivotPos; ++i){
		if (arr[i] > arr[pivotPos])
			return 0;
	}

	for (int i = pivotPos + 1; i <= right; ++i){
		if (arr[pivotPos] > arr[i])
			return 0;
	}
	return 1;
}

void QuickSort(int * arr, int left, int right){
	if (left >= right) return;
	
	if (left < right){
		int pos = Partition(arr, left, right);
		if (TestPartition(arr, left, right, pos)){
			QuickSort(arr, left, pos - 1);
			QuickSort(arr, pos + 1, right);
		}
		else
			return;
	}
}

int main(void){
	int * arr;
	int pos;

	for (int i = 1; i <= 16; ++i){
		arr = Init(i);
		PrintArr(arr, i);
		QuickSort(arr, 0, i - 1);
		PrintArr(arr, i);
		delete arr;

		printf("\n\n");

		arr = InitIncrease(i);
		PrintArr(arr, i);
		QuickSort(arr, 0, i - 1);
		PrintArr(arr, i);
		delete arr;

		printf("\n\n");

		arr = InitDecrease(i);
		PrintArr(arr, i);
		QuickSort(arr, 0, i - 1);
		PrintArr(arr, i);
		delete arr;

		printf("\n\n");
	}

	getchar();
	return 0;
}