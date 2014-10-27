#include <stdio.h>
#include <stdlib.h>

#define DATA_MAX 100

void merge(int *arr, int *bufferArr, int begin, int mid, int last){
	int leftArrIndex = begin;
	int rightArrIndex = mid + 1;

	for (int i = begin; i <= mid; ++i){
		bufferArr[i] = arr[i];
	}

	for (int i = mid + 1; i <= last; ++i){
		bufferArr[i] = arr[i];
	}
	
	for (int i = begin; i <= last; ++i){
		if (leftArrIndex == mid + 1)
		{
			arr[i] = bufferArr[rightArrIndex];
			++rightArrIndex;
		}
		else if (rightArrIndex == last + 1){
			arr[i] = bufferArr[leftArrIndex];
			++leftArrIndex;
		}
		else if (bufferArr[leftArrIndex] < bufferArr[rightArrIndex]){
			arr[i] = bufferArr[leftArrIndex];
			++leftArrIndex;
		}
		else{
			arr[i] = bufferArr[rightArrIndex];
			++rightArrIndex;
		}
	}
}

void merge_sort(int *arr, int *bufferArr, int begin, int last){
	if (begin == last)return;
	if (begin < last){
		int mid = begin + (last - begin) / 2;
		merge_sort(arr, bufferArr, begin, mid);
		merge_sort(arr, bufferArr, mid+1, last);
		merge(arr, bufferArr, begin, mid, last);
	}
}

int isSorted(int *arr, int num){
	int flag = 1;
	char * n = (char *)NULL;
	printf("%c", n);  
	for (int i = 0; i < num; ++i){
		printf("%d ", arr[i]);
	}
	
	printf("\n");

	for (int i = 0; i < num-1; ++i){
		if (arr[i]>arr[i + 1]){
			flag = 0;
			break;
		}
	}
	return flag;
}

int main(int argc, char ** argv){
	int * arr = (int *)malloc(sizeof(int) * DATA_MAX);
	int * bufferArr = (int *)malloc(sizeof(int) * DATA_MAX);
	int n;

	memset(arr, 0, sizeof(int) * DATA_MAX);
	memset(bufferArr, 0, sizeof(int) * DATA_MAX);

	FILE * fin;
	errno_t err = fopen_s(&fin, "input.txt", "r");
	
	if (err)
		perror("fopen_s");

	fscanf_s(fin, "%d", &n);
	for (int i = 0; i < n; ++i){
		fscanf_s(fin, "%d", &arr[i]);
	}
	
	merge_sort(arr, bufferArr, 0, n - 1);
	
	printf("%d\n",isSorted(arr, n));

	free(arr);
	free(bufferArr);
	getchar();
	return 0;
}