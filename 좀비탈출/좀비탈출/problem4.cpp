#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INPUT_FILE_NAME "input.txt"

void InputRope(vector<int> & ropeVector, int & makeCount, int & dataCount){
	FILE * fin;
	errno_t err;
	err = fopen_s(&fin, INPUT_FILE_NAME, "r");

	fscanf_s(fin, "%d %d", &dataCount, &makeCount);

	for (int i = 0; i < dataCount; ++i){
		double temp;
		fscanf_s(fin, "%lf", &temp);
		temp *= 100;
		int number = static_cast<int>(temp);
		ropeVector.push_back(number);
	}
	sort(ropeVector.begin(), ropeVector.end());
	fclose(fin);
}

void FindMaxRopeLength(vector<int> & ropeVector, int & makeCount, int & dataCount){
	int left = 1;
	int right = ropeVector[dataCount - 1];
	int max = -1000000000;

	while (left <= right){
		int findLength = left + (right - left) / 2;
		int count = 0;

		for (int i = 0; i < dataCount; ++i){
			count += ropeVector[i] / findLength;
		}
		int temp = 0;
		if (count >= makeCount){
			left = findLength + 1;
			max = findLength;
		}
		else
			right = findLength - 1;
	}

	double res = (double)((double)max / (double)100);
	printf("%.02lf\n",res);
}

int main(){
	int dataCount;
	int makeCount;
	vector<int> ropeVector;
	InputRope(ropeVector, makeCount, dataCount);
	FindMaxRopeLength(ropeVector, makeCount, dataCount);
	getchar();
	return 0;
}