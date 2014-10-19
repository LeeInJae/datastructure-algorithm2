#include <stdio.h>
#include <stdlib.h>

#define DATA_MAX 100

void insertion_sort(int * arr, int n){
	if (arr == NULL) return;
	
	int key, idx;

	for (int i = 1; i < n; ++i){
		key = arr[i];
		idx = i - 1;
		while (idx >= 0 && arr[idx] > key){
			arr[idx+1] = arr[idx];
			--idx;
		}
		arr[idx + 1] = key;
	}
}

void print_arr(int * arr, int n){
	for (int i = 0; i < n; ++i){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main(void){
	int * arr = (int * )malloc(sizeof(int) * DATA_MAX);
	int n;
	memset(arr, 0, sizeof(int) * DATA_MAX);
	FILE * fin;
	errno_t err = fopen_s(&fin, "input.txt", "r");
	
	if ( err )
	{
		perror("fopen_s");
	}
	
	fscanf_s(fin, "%d", &n);
	for (int i = 0; i < n; ++i){
		fscanf_s(fin, "%d", &arr[i]);
	}

	insertion_sort(arr, n);
	print_arr(arr, n);
	free(arr);
	getchar();
	return 0;
}