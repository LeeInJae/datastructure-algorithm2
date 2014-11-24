#include <iostream>

void Combination(char * arr, int curNumber, int size, int curPos, int * bit, int r){
	if (curNumber == r){
		for (int i = 0; i < size; ++i){
			if (bit[i]){
				printf("%c", arr[i]);
			}
		}
		printf("\n");
		return;
	}

	for (int i = curPos; i < size; ++i){
		bit[i] = 1;
		Combination(arr, curNumber + 1, size, i + 1, bit, r);
		bit[i] = 0;
	}
}
int main(void){
	char arr[] = "abc";
	int size = sizeof(arr) / sizeof(char) - 1;
	int * bit = (int *)malloc(sizeof(int) * (size + 1));

	for (int r = 0; r <= size; ++r){
		for (int i = 0; i <= size; ++i){
			bit[i] = 0;
		}
		Combination(arr, 0, size, 0, bit, r);
	}
	getchar();
	return 0;
}