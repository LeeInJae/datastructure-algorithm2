#include <iostream>
#include <algorithm>
#include <list>
#include <hash_map>
#include <time.h>
#include <map>
#include <stack>
#include <set>

using namespace std;

#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"
#define MAX_NUMBER 1000000
#define GRID_LENGTH 1000
#define GRID_INTERVAL MAX_NUMBER / GRID_LENGTH

struct Point{
	int x, y;
};
class Circle{
public:
	Circle(){}
	Circle(int inputX, int inputY, int inputR, int inputId, int inputGridNumber) {
		center.x = inputX;
		center.y = inputY;
		r = inputR;
		id = inputId;
		gridNumber = inputGridNumber;
		groupNumber = inputId;
	}

public:
	void SetGroupNumber(int number){ groupNumber = number; }
	Point GetCenter(){ return center; }
	int GetCenterX(){ return center.x; }
	int GetCenterY(){ return center.y; }
	int GetR(){ return r; }
	int GetGridNumber(){ return gridNumber; }
	int GetId(){ return id; }
	int GetGroupNumber(){ return groupNumber; }
private:
	Point center;
	int r;
	int id;
	int gridNumber;
	int groupNumber;
};

bool IsCollision(Circle * obj1, Circle * obj2){
	Point center1 = obj1->GetCenter();
	Point center2 = obj2->GetCenter();

	long long int dx = center1.x - center2.x;
	long long int dy = center1.y - center2.y;
	long long int d = dx*dx + dy*dy;
	long long int obj1R = obj1->GetR();
	long long int obj2R = obj2->GetR();

	long long int r = (obj1R + obj2R) * (obj1R + obj2R);

	if (r >= d){
		return true;
	}
	return false;
}

int Min(int a, int b){
	if (a < b)
		return a;
	return b;
}

int Revision(int number){
	if (number < 0)
		return 0;
	if (number>MAX_NUMBER - 1)
		return MAX_NUMBER - 1;

	return number;
}

int GridFunc(int row, int col){
	return row + col * GRID_INTERVAL;
}

void InputData(hash_map<int, Circle*> & bombHashMap, hash_map<int, list<int>> & gridBombHashMap){
	FILE * fin;
	errno_t err;
	err = fopen_s(&fin, INPUT_FILE_NAME, "r");

	int tempN, tempX, tempY, tempR, tempGrid, gridInterval;
	list<int> bombList;

	gridInterval = MAX_NUMBER / GRID_LENGTH;

	fscanf_s(fin, "%d", &tempN);

	for (int i = 0; i < tempN; ++i){
		fscanf_s(fin, "%d %d %d", &tempX, &tempY, &tempR);
		int row = tempX / GRID_LENGTH;
		int col = tempY / GRID_LENGTH;

		tempGrid = GridFunc(row, col);
		bombHashMap[i] = (new Circle(tempX, tempY, tempR, i, tempGrid));

		auto curCircle = bombHashMap[i]; //현재 들어온 새키

		for (auto iter = bombList.begin(); iter != bombList.end(); ++iter){
			auto preCircle = bombHashMap[*iter];

			if (IsCollision(curCircle, preCircle)){//충돌 했으면 그룹 합쳐주기
				int min = Min(preCircle->GetGroupNumber(), curCircle->GetGroupNumber());
				preCircle->SetGroupNumber(min);
				curCircle->SetGroupNumber(min);
			}
		}
		bombList.push_back(i);
	}

	set<int> resSet;
	for (auto iter = bombHashMap.begin(); iter != bombHashMap.end(); ++iter){
		auto obj = iter->second;
		resSet.insert(obj->GetGroupNumber());
	}
	int res = resSet.size();
	printf("%d", res);
	fclose(fin);
}

int main(void){
	clock_t start_time, end_time;
	start_time = clock();

	hash_map<int, Circle*> bombHashMap; //id와 bomb
	hash_map<int, list<int>> gridBombHashMap;
	vector<list<int>*> saveListPointer; //여기있는놈 메모리 해제

	InputData(bombHashMap, gridBombHashMap);

	end_time = clock();
	printf("Time : %f\n", ((double)(end_time - start_time)) / CLOCKS_PER_SEC);
	getchar();
	return 0;
}