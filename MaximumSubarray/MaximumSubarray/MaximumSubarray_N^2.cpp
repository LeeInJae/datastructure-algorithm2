#include <iostream>


int MaximumSubarray(int * arr, int * sum, int n){
	int max = -1000000;
	int left, right;
	if (n == 0){
		return 0;
	}
	else if (n == 1){
		left = 0;
		right = 0;
		max = sum[0];
	}
	else{
		for (int i = 0; i < n; ++i){
			for (int j = i; j < n; ++j){
				if (sum[j] - sum[i] + arr[i] > max){
					max = sum[j] - sum[i] + arr[i];
					left = i;
					right = j;
				}
			}
		}
	}
	printf("%d ~ %d\n", left, right);
	return max;
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
	else
	{
		int n = sizeof(arr) / sizeof(int);
		int * sum = (int *)malloc(sizeof(int) * n);

		sum[0] = arr[0];
		for (int i = 1; i < n; ++i){
			sum[i] = sum[i - 1] + arr[i];
		}
		int res = MaximumSubarray(arr, sum, n);

		printf("%d\n", res);
		getchar();
		delete[] sum;
	}
	return 0;
}