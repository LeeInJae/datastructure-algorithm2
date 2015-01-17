#include <iostream>
#define INF 100000000

using namespace std;

int CrossMaximumSubarray(int * arr, int left, int mid, int right){
	int sum = 0;
	int leftMaxSum = -INF;
	for (int i = mid; i >= left; --i){
		sum += arr[i];
		if (sum > leftMaxSum)
			leftMaxSum = sum;
	}

	sum = 0;
	int rightMaxSum = -INF;

	for (int i = mid+1; i <= right; ++i){
		sum += arr[i];
		if (sum > rightMaxSum)
			rightMaxSum = sum;
	}

	return (leftMaxSum + rightMaxSum);
}

int Max(int a, int b, int c){
	if (b < a && c < a) return a;
	if (a < b && c < b) return b;
	return c;
}

int MaximumSubarray(int * arr, int left, int right){
	if (left == right)
		return arr[left];

	int mid = left + (right - left) / 2;

	int leftMaximumSubarray = MaximumSubarray(arr, left, mid);
	int rightMaximumSubarray = MaximumSubarray(arr, mid + 1, right);
	int crossMaximumSubarray = CrossMaximumSubarray(arr, left, mid, right);
	
	return Max(leftMaximumSubarray, rightMaximumSubarray, crossMaximumSubarray);
}

int IterationMaximumSubarray(int * arr, int left, int right){
	int max = -INF;
	int sum = 0;
	for (int i = left; i <= right; ++i){
		if (sum + arr[i] >= 0){
			sum += arr[i];
			if (max < sum)
				max = sum;
		}
		else
			sum = 0;
	}
	return max;
}

int main(void){
	int arr[] = { 3, -1, 45, 2, -500, 1, 6 };
	int size = sizeof(arr) / sizeof(int);
	cout << MaximumSubarray(arr, 0, size) << endl;
	cout << IterationMaximumSubarray(arr, 0, size) << endl;
	getchar();
	return 0;
}