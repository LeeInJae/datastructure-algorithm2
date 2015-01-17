#include <iostream>

#include <iostream>

using namespace std;

void CopyBlock(int * arr, int * buffer, int left, int right){
	for (int i = left; i <= right; ++i){
		buffer[i] = arr[i];
	}
}

void Merge(int * arr, int * buffer, int left, int mid, int right){
	int leftIndex = left;
	int leftLast = mid;
	int rightIndex = mid + 1;
	int rightLast = right;

	for (int i = left; i <= right; ++i){
		if (leftIndex > leftLast){
			arr[i] = buffer[rightIndex];
			++rightIndex;
			continue;
		}

		if (rightIndex > rightLast){
			arr[i] = buffer[leftIndex];
			++leftIndex;
			continue;
		}

		if (buffer[leftIndex] < buffer[rightIndex]){
			arr[i] = buffer[leftIndex];
			++leftIndex;
		}
		else{
			arr[i] = buffer[rightIndex];
			++rightIndex;
		}
	}
}

void MergeSort(int * arr, int * buffer, int left, int right){
	if (left >= right){
		return;
	}
	int mid = left + (right - left) / 2;
	MergeSort(arr, buffer, left, mid);
	MergeSort(arr, buffer, mid + 1, right);
	CopyBlock(arr, buffer, left, right);
	Merge(arr, buffer, left, mid, right);
}

int main(void){
	int arr[] = { 3, 1, 45, 2, 5, 1, 6 };
	int size = sizeof(arr) / sizeof(int);
	int * buffer = new int[size];

	MergeSort(arr, buffer, 0, size - 1);

	getchar();
	delete[] buffer;
	return 0;
}