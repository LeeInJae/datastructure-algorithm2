#include <iostream>

void Swap(char * a, char * b){
	char temp = *a;
	*a = *b;
	*b = temp;
}

void Permutation(char * arr, int startPos, int endPos){
	if (startPos >= endPos){
		printf("%s\n", arr);
		return;
	}

	for (int i = startPos; i <= endPos; ++i){
		Swap(&arr[startPos], &arr[i]);
		Permutation(arr, startPos + 1, endPos);
		Swap(&arr[startPos], &arr[i]);
	}
}
int main(void){
	char arr[] = "abc";
	int size = sizeof(arr) / sizeof(char);
	size = size - 1;
	Permutation(arr, 0, size - 1);
	getchar();
	return 0;
}