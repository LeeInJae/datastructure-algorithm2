#include <iostream>

using namespace std;

void InsertionSort(int * arr, int size){
	for (int i = 1; i < size; ++i){
		int pos = i-1;
		int curKey = arr[i];
		while (pos >=0 && curKey < arr[pos]){
			arr[pos+1] = arr[pos];
			--pos;
		}
		arr[pos + 1] = curKey;
	}
}

int main(void){
	int arr[] = { 3, 1, 45, 2, 5, 1, 6 };
	int size = sizeof(arr) / sizeof(int);
	InsertionSort(arr, size);
	getchar();
	return 0;
}