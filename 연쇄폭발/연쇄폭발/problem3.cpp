#include <iostream>
#include <algorithm>
#include <list>
#include <hash_map>
#include <time.h>
#include <map>
#include <stack>

using namespace std;

#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"
#define MAX_NUMBER 1000000
#define GRID_LENGTH 1000

struct Point{
	int x, y;
};
class Circle{
public:
	Circle(){}
	Circle(int inputX, int inputY, int inputR, int inputId,int inputGridNumber) {
		center.x = inputX;
		center.y = inputY;
		r = inputR;
		id = inputId;
		gridNumber = inputGridNumber;
	}

public:
	Point GetCenter(){ return center;}
	int GetCenterX(){ return center.x; }
	int GetCenterY(){ return center.y; }
	int GetR(){ return r; }
	int GetGridNumber(){ return gridNumber; }
	int GetId(){ return id; }
private:
	Point center;
	int r;
	int id;
	int gridNumber;
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

void InputData(hash_map<int, Circle*> & bombHashMap, multimap<int, Circle*> & gridBombMultiMap){
	FILE * fin;
	errno_t err;
	err = fopen_s(&fin, INPUT_FILE_NAME, "r");
	
	int tempN, tempX, tempY, tempR, tempGrid, gridInterval;
	
	gridInterval = MAX_NUMBER / GRID_LENGTH;

	fscanf_s(fin, "%d", &tempN);

	for (int i = 0; i < tempN; ++i){
		fscanf_s(fin, "%d %d %d", &tempX, &tempY, &tempR);
		int row = tempX / GRID_LENGTH;
		int col = tempY / GRID_LENGTH;
		tempGrid = row + col * gridInterval;
		bombHashMap[i] = (new Circle(tempX, tempY, tempR, i, tempGrid));
		gridBombMultiMap.insert(multimap<int, Circle*>::value_type(tempGrid, bombHashMap[i]));
	}
	fclose(fin);
}

void FindBombNumber(hash_map<int, Circle*> & bombHashMap, multimap<int, Circle*> & gridBombMultiMap){
	int gridInterval = MAX_NUMBER / GRID_LENGTH;
	Point adjGridAssist[9];
	int tempCount = 0;
	for (int i = -1; i <= 1; ++i){
		for (int j = -1; j <= 1; ++j){
			adjGridAssist[tempCount].x = i;
			adjGridAssist[tempCount].y = j;
			++tempCount;
		}
	}
	stack<Circle *> explosionCircle;

	int res = 0;
	while (!bombHashMap.empty()){
		Circle * curCicle;

		if (explosionCircle.empty()){ //stack이 비어있으면, 현재 남은 폭탄에서 한개를 푸쉬해줌
			++res;//폭탄 한 번 더 터뜨려야함

			auto iter = bombHashMap.begin();
			auto obj = iter->second;
			
			bombHashMap.erase(iter);//현재 넣는 폭탄을 폭탄 리스트에서 제거해주어야함
			explosionCircle.push(obj);
			curCicle = obj;

			int curGrid = obj->GetGridNumber(); //현재 스택에 넣는 폭탄을 그리드에서 제거해주어야함
			auto curGridCircle = gridBombMultiMap.equal_range(curGrid);

			for (auto bomb = curGridCircle.first; bomb != curGridCircle.second; ++bomb){
				auto bombIter = bomb;
				auto bombObj = bomb->second;
				if (obj == bombObj){
					
				}
			}

		} 
		else{
			auto obj = explosionCircle.top();
			explosionCircle.pop();
			curCicle = obj;
		}
		int curGrid = curCicle->GetGridNumber();

		for (int j = 0; j < 9; ++j){
			int adjGrid = curGrid + gridInterval*adjGridAssist[j].x + adjGridAssist[j].y;
			if (adjGrid < 0 || adjGrid > gridInterval * gridInterval - 1) // 범위 벗어나면 그리드 검사 안함
				continue;

			auto curGridCircle = gridBombMultiMap.equal_range(curGrid);
			auto adjGridCircle = gridBombMultiMap.equal_range(adjGrid);
		}
	}
}

int main(void){
	clock_t start_time, end_time;
	start_time = clock();
	hash_map<int, Circle*> bombHashMap; //id와 bomb
	multimap<int, Circle*> gridBombMultiMap;

	InputData(bombHashMap, gridBombMultiMap);
	FindBombNumber(bombHashMap, gridBombMultiMap);
	end_time = clock();
	printf("Time : %f\n", ((double)(end_time - start_time)) / CLOCKS_PER_SEC);
	getchar();
	return 0;
}