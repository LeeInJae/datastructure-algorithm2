#include <iostream>

using namespace std;

#define VertexNum 5
#define EdgeNum 10
#define INF 1000000

int ** Make2dArray(int size){
	int ** arr = new int *[size];
	int cnt = 0;
	for (int i = 0; i < size; ++i){
		arr[i] = new int[size];
		for (int j = 0; j < size; ++j){
			arr[i][j] = INF;
		}
		arr[i][i] = 0;
	}
	return arr;
}

bool MakeAdjMatrix(int ** preArr){
	if (preArr == nullptr)
		return false;

	preArr[0][1] = 6;
	preArr[0][3] = 7;
	preArr[1][2] = 5;
	preArr[1][4] = 4;
	preArr[1][3] = 8;
	preArr[2][1] = 2;
	preArr[3][4] = 9;
	preArr[4][0] = 2;
	preArr[4][2] = 7;
	preArr[3][2] = 3;

	return true;
}

void FloydWarshall(int ** arr){
	for (int k = 0; k < VertexNum; ++k){
		for (int i = 0; i < VertexNum; ++i){
			for (int j = 0; j < VertexNum; ++j){
				if (arr[i][j] > arr[i][k] + arr[k][j])
					arr[i][j] = arr[i][k] + arr[k][j];
			}
		}
	}
}

int main(void){
	int ** arr = Make2dArray(VertexNum);
	MakeAdjMatrix(arr);
	FloydWarshall(arr);
	getchar();
	delete[] arr;
	return 0;
}