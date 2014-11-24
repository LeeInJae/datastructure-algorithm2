#include <iostream>
#include<stdio.h>

using namespace std;

int FindmNumberLeftPlace(int * arr, int m, int cur, int size){
	if (cur >= size) return -1;
	if (arr[cur] == m){
		return cur;
	}
	return FindmNumberLeftPlace(arr, m, cur + 1, size);
}


int FindmNumberRightPlace(int * arr, int m, int cur){
	if (cur < 0) return -1;
	if (arr[cur] == m){
		return cur;
	}
	return FindmNumberRightPlace(arr, m, cur - 1);
}
int main(void){

	int arr[] = { 1, 3, 7, 7, 7, 7, 9, 10 };
	int size = sizeof(arr) / sizeof(int);
	int m = 7;
	int mNumberLeftPos = FindmNumberLeftPlace(arr, m, 0, size);
	int mNumberRightPos = FindmNumberRightPlace(arr, m, size);
	printf("%d 부터 %d 까지 있음\n", mNumberLeftPos + 1, mNumberRightPos + 1);
	getchar();
	return 0;
}
