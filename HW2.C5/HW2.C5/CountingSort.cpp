#include <iostream>
#define MAX_NUM 1000

void CountingSort(int * arr, int * res, int size){
	int * count = (int *)malloc(sizeof(int) * (MAX_NUM + 1));

	for (int i = 0; i <= MAX_NUM; ++i)
		count[i] = 0;

	for (int i = 0; i < size; ++i)
		++count[arr[i]];

	for (int i = 1; i <= MAX_NUM; ++i)
		count[i] = count[i] + count[i - 1];

	for (int i = size - 1; i >= 0; --i){
		res[count[arr[i]]] = arr[i];
		--count[arr[i]];
	}
	delete count;
}

void PrintArr(int * arr, int * res, int size){
	for (int i = 0; i < size; ++i)
		printf("%d ", arr[i]);
	printf("\n");
	for (int i = 1; i <= size; ++i)
		printf("%d ", res[i]);
}

int main(void){
	int arr[] = { 10, 4, 1, 2, 5, 1, 2, 3, 0, 0, 1, 3, 2 };
	int size = sizeof(arr) / sizeof(int);
	int * res = (int *)malloc(sizeof(int) * (size + 1));
	CountingSort(arr, res, size);
	PrintArr(arr, res, size);
	delete res;
	getchar();
	return 0;
}