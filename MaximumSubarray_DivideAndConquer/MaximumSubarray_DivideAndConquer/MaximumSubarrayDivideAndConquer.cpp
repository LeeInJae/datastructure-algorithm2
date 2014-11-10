#include<iostream>

int FindMaximumSubarrayFromLeftToRight(int * arr, int left, int mid, int right){
	int leftMax = -100000, rightMax = -100000;
	int index, sum;

	sum = 0;
	index = mid;
	while (index >= left){
		sum += arr[index];
		if (leftMax < sum)
			leftMax = sum;
		--index;
	}

	sum = 0;
	index = mid +1;
	while (index <= right){
		sum += arr[index];
		if (rightMax < sum)
			rightMax = sum;
		++index;
	}

	return (leftMax + rightMax);
}

int Max(int a, int b, int c){
	if (a >= b && a >= c) return a;
	if (b >= a && b >= c) return b;
	return c;
}


int MaximumSubarray(int * arr, int left, int right){
	if (left > right) return 0;
	if (left == right)
		return arr[left];

	int mid = left + (right - left) / 2;//소수점이하 버리기때문에 left~mid-1까지 하면 안되는듯

	int leftSubArray = MaximumSubarray(arr, left, mid);
	int rightSubArray = MaximumSubarray(arr, mid + 1, right);
	int leftRightSubarray = FindMaximumSubarrayFromLeftToRight(arr,left, mid, right);

	return Max(leftRightSubarray, rightSubArray, leftRightSubarray);
}

int main(void){
	//int * arr = NULL;
	//int arr[] = { 1 };
	//int arr[] = { 100, -99, 100, 2 };
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, -200, 199, 20 };
	//int arr[] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, -12, -5, -22, 15, -4, 7 };
	if (arr == NULL){
		printf("자료가 없음");
		getchar();
		return 0;
	}
	
	int n = sizeof(arr) / sizeof(int);

 	printf("%d\n", MaximumSubarray(arr, 0, n - 1));
	getchar();
	return 0;
}