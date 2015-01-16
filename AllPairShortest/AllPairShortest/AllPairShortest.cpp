#include <iostream>

using namespace std;

#define VertexNum 5
#define EdgeNum 10
#define INF 1000000

int ** Make2dArray(int size){
	int ** arr = new int * [size];
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

bool ExtendedEdge(int **preArr, int ** arr){
	if (preArr == nullptr || arr == nullptr)
		return false;

	for (int i = 0; i < VertexNum; ++i){
		for (int j = 0; j < VertexNum; ++j){
			for (int k = 0; k < VertexNum; ++k){
				if (arr[i][j]>preArr[i][k] + preArr[k][j])
					arr[i][j] = preArr[i][k] + preArr[k][j];
			}
		}
	}
	return true;
}

bool CopyArrToPreArr(int ** preArr, int ** arr){
	if (preArr == nullptr || arr == nullptr)
		return false;

	for (int i = 0; i < VertexNum; ++i)
		for (int j = 0; j < VertexNum; ++j)
			preArr[i][j] = arr[i][j];
	
	return true;
}
int main(void){
	int ** preArr = Make2dArray(VertexNum);
	int ** arr = Make2dArray(VertexNum);
	MakeAdjMatrix(preArr);
	int edgeCount = 1;
		
	while (edgeCount < VertexNum - 1){
		ExtendedEdge(preArr, arr);
		CopyArrToPreArr(preArr, arr);
		edgeCount = edgeCount * 2;
	}
	getchar();
	delete[] preArr;
	delete[] arr;
	return 0;
}