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
	int pivot = arr[right-1];
	int wall = -1;

	for (int i = 0; i < right - 1; ++i){
		if (arr[i] <= pivot){
			++wall;
			Swap(&arr[wall], &arr[i]);
		}
	}
	++wall;
	Swap(&arr[wall], &arr[right-1]);
	return wall;
}

int TestPartition(int * arr, int size, int pivotPos){
	for (int i = 0; i < pivotPos; ++i){
		if (arr[i] > arr[pivotPos])
			return 0;
	}

	for (int i = pivotPos + 1; i < size; ++i){
		if (arr[pivotPos] > arr[i])
			return 0;
	}
	return 1;
}

int main(void){
	int * arr;
	int pos;
	
	for (int i = 1; i <= 32; ++i){
		arr = Init(i);
		pos = Partition(arr, 0, i);
		PrintArr(arr, i);
		if (TestPartition(arr, i, pos)){
			printf("pivot의 위치는 %d 이고, 파티션이 아주 잘 되었음\n", pos);
		}
		else
		{
			printf("파티션이 아주 잘 못되었음\n");
		}
		delete arr;
		
		printf("\n\n");
		
		arr = InitIncrease(i);
		pos = Partition(arr, 0, i);
		PrintArr(arr, i);
		if (TestPartition(arr, i, pos)){
			printf("pivot의 위치는 %d 이고, 파티션이 아주 잘 되었음\n", pos);
		}
		else
		{
			printf("파티션이 아주 잘 못되었음\n");
		}
		delete arr;

		printf("\n\n");

		arr = InitDecrease(i);
		pos = Partition(arr, 0, i);
		PrintArr(arr, i);
		if (TestPartition(arr, i, pos)){
			printf("pivot의 위치는 %d 이고, 파티션이 아주 잘 되었음\n", pos);
		}
		else
		{
			printf("파티션이 아주 잘 못되었음\n");
		}
		delete arr;
		
		printf("\n\n");
	}

	getchar();
	return 0;
}

