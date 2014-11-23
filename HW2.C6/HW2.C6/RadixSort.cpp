#include <iostream>
#include <stdlib.h>

#define DIGIT_MAX 3 //최대자리수 Digit
#define MAX_NUM 423 //최대수 K

void CountingSort(int * arr, int size, int digitNum, int * result){
	int * count = (int *)malloc(sizeof(int) * (MAX_NUM + 1));
	int * temp = (int *)malloc(sizeof(int) * (size + 1));
	int digit = 1;

	for (int i = 1; i < digitNum; ++i)
		digit = digit * 10;

	for (int i = 0; i <= MAX_NUM; ++i)
		count[i] = 0;

	for (int i = 0; i < size; ++i){
		temp[i] = (char)((arr[i] / digit) % 10);
		++count[temp[i]];
	}

	for (int i = 1; i <= MAX_NUM; ++i)
		count[i] = count[i] + count[i - 1];

	for (int i = size - 1; i >= 0; --i){
		result[count[temp[i]]] = arr[i];
		--count[temp[i]];
	}
	for (int i = 1; i <= size; ++i){
		arr[i - 1] = result[i];
	}
	delete count;
	delete temp;
}

void PrintArr(int * arr, int * res, int size){
	for (int i = 0; i < size; ++i)
		printf("%d ", arr[i]);
	printf("\n");
	for (int i = 1; i <= size; ++i)
		printf("%d ", res[i]);
}

void RadixSort(int * arr, int size, int digitNum, int * result){
	for (int i = 1; i <=digitNum; ++i){
		CountingSort(arr, size, i, result);
	}
}

void PrintResult(int * result, int size){
	for (int i = 1; i <= size; ++i){
		printf("%d ", result[i]);
	}
	printf("\n");
}
int main(void){
	int arr[] = { 10, 2, 30, 423, 21, 20, 35, 5, 7, 8 };
	int size = sizeof(arr) / sizeof(int);
	int * result = (int *)malloc(sizeof(int) * (size + 1));
	RadixSort(arr, size, DIGIT_MAX, result);

	PrintResult(result, size);
	getchar();
	return 0;
}