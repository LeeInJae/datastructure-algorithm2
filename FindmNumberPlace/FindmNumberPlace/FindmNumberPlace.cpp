#include <iostream>
#include<stdio.h>

using namespace std;

int FindmNumberPlace(int * arr, int m, int cur){
	if (cur < 0) return -1;
	if (arr[cur] == m){
		return cur;
	}
	return FindmNumberPlace(arr, m, cur - 1);
}

int main(void){

	int arr[] = { 1, 3, 4, 7, 9, 10 };
	int size = sizeof(arr) / sizeof(int);
	int m = 7;
	int mNumberPos = FindmNumberPlace(arr, m, size);
	printf("%d \n", mNumberPos + 1);
	getchar(); 
	return 0;
}
