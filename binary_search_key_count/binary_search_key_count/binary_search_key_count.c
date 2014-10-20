#include <stdio.h>
#include <stdlib.h>

#define DATA_MAX 100

int left_binary_search(int * arr, int left, int right, int key){
	int mid, pos;
	pos = -1;
	while (left <= right){
		mid = left + (right - left) / 2;

		if (arr[mid] > key){
			right = mid - 1;
		}
		else if (arr[mid] < key){
			left = mid + 1;
		}
		else if (arr[mid] == key){
			pos = mid;
			right = mid - 1;
		}
	}
	return pos;
}

int right_binary_search(int * arr, int left, int right, int key){
	int mid, pos = -1;

	while (left <= right){
		mid = left + (right - left) / 2;

		if (arr[mid] > key){
			right = mid - 1;
		}
		else if (arr[mid] < key){
			left = mid + 1;
		}
		else if (arr[mid] == key){
			pos = mid;
			left = mid + 1;
		}
	}
	return pos;
}

int main(int argc, char ** argv){
	int * arr = (int *)malloc(sizeof(int) * DATA_MAX);
	FILE * fin;
	int n;
	int leftPos, rightPos, key;

	memset(arr, 0, sizeof(int) * DATA_MAX);
	errno_t err = fopen_s(&fin, "input.txt", "r");
	if (err)
		perror("fopen_s");

	fscanf_s(fin, "%d", &n);
	for (int i = 0; i < n; ++i){
		fscanf_s(fin, "%d", &arr[i]);
	}

	key = 3;

	leftPos = left_binary_search(arr, 0, n-1, key);
	rightPos = right_binary_search(arr, 0, n-1, key);

	if (leftPos == -1 || rightPos == -1)
		printf("해당 key 값은 없습니다.\n");
	else
		printf("%d 의 개수 = %d\n", key, rightPos - leftPos + 1);
	getchar();
	return 0;
}