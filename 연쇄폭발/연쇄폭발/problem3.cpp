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
	
	gridInterval = MAX_NUMBER / GRID_LENGTH;
	
	fscanf_s(fin, "%d", &tempN);

	for (int i = 0; i < tempN; ++i){
		fscanf_s(fin, "%d %d %d", &tempX, &tempY, &tempR);
		int row = tempX / GRID_LENGTH;
		int col = tempY / GRID_LENGTH;
		int adjGridR = tempR / GRID_LENGTH;
		Point left, right, up, down;
		
		left.x = tempX - tempR, left.y = tempY;
		right.x = tempX + tempR, right.y = tempY;
		up.x = tempX, up.y = tempY + tempR;
		down.x = tempX, down.y = tempY - tempR;
		
		int minX = left.x;
		int maxX = right.x;
		int minY = down.y;
		int maxY = up.y;

		minX = Revision(minX);
		minY = Revision(minY);
		maxX = Revision(maxX);
		maxY = Revision(maxY);

		minX = minX / GRID_LENGTH;
		maxX = maxX / GRID_LENGTH;
		minY = minY / GRID_LENGTH;
		maxY = maxY / GRID_LENGTH;
		
		int leftDownGrid = GridFunc(minX, minY);
		int leftUpGrid = GridFunc(minX, maxY);

		for (int j = leftDownGrid; j <= leftUpGrid; j += GRID_INTERVAL){
			for (int k = 0; k <= (maxX - minX); ++k){
				list<int> & collisionGridList = gridBombHashMap[j + k];
				collisionGridList.push_back(i);
			}
		}

		tempGrid = GridFunc(row, col);
		bombHashMap[i] = (new Circle(tempX, tempY, tempR, i, tempGrid));
	}
	fclose(fin);
}

void FindBombNumber(hash_map<int, Circle*> & bombHashMap, hash_map<int, list<int>> & gridBombHashMap){
	stack<Circle *> explosionCircle;
	set<int> alreadyExplodedBomb;
	bool * checkBomb = new bool[5000001];

	for (int i = 0; i < 5000001; ++i)
		checkBomb[i] = false;

	int res = 0;

	for (int i = 0; i < 1000000; ++i){
		list<int> & gridCurBombList = gridBombHashMap[i];
		for (auto bombList = gridCurBombList.begin(); bombList != gridCurBombList.end(); ++bombList){

		}
	}

// 	while (!bombHashMap.empty()){
// 		Circle * curCicle;
// 
// 		if (explosionCircle.empty()){ //stack이 비어있으면, 현재 남은 폭탄에서 한개를 푸쉬해줌
// 			++res;//폭탄 새로 터뜨려야함
// 
// 			auto iter = bombHashMap.begin();
// 			auto obj = iter->second;
// 			
// 			bombHashMap.erase(iter);//현재 넣는 폭탄을 폭탄 리스트에서 제거해주어야함
// 			curCicle = obj;
// 
// 			//alreadyExplodedBomb.insert(curCicle->GetId());//터진새키는 set에 넣어줌
// 			checkBomb[obj->GetId()] = true; //얘는 지금 터뜨림.
// 		} 
// 		else{//추후 보정 필요(stack에서 바로 빼오는 경우)
// 			auto obj = explosionCircle.top();
// 			explosionCircle.pop();
// 			curCicle = obj;
// 		}
// 		
// 		int curGrid = curCicle->GetGridNumber();
// 		list<int> & curGridList = gridBombHashMap[curGrid];
// 
// 		for (auto curGridCircle1 = curGridList.begin(); curGridCircle1 != curGridList.end(); ++curGridCircle1){
// 			for (auto curGridCircle2 = curGridList.begin(); curGridCircle2 != curGridList.end(); ++curGridCircle2){
// 				auto obj1 = *curGridCircle1;
// 				auto obj2 = *curGridCircle2;
// 
// 				if (obj1 == obj2) continue; //ID 같으면 같은 새키니까 continue
// 				if (checkBomb[obj1] || checkBomb[obj2]) continue; //이미 터진새키들인지 확인
// 
// 				auto circle1 = bombHashMap[obj1];
// 				auto circle2 = bombHashMap[obj2];
// 
// 				if (IsCollision(circle1, circle2)){ //새로운 두새키 충돌하면
// 					checkBomb[circle1->GetId()] = true;
// 					checkBomb[circle2->GetId()] = true;
// 
// 					explosionCircle.push(circle1);
// 					explosionCircle.push(circle2);
// 				}
// 			}
// 		}
// 		//delete curCicle; //현재 써먹은 폭탄은 터뜨렸으므로 이제 존재하지 않음.
// 	}

	printf("%d\n", res);
}

// void ReleaseMemory(hash_map<int, Circle*> & bombHashMap, hash_map<int, list<Circle *>> & gridBombHashMap, vector<list<Circle *>*> & saveListPointer){
// 	for (auto &i = bombHashMap.begin(); i != bombHashMap.end();){
// 		auto iter = i;
// 		if (i){
// 			i = bombHashMap.erase(iter);
// 			delete obj;
// 		}
// 	}
// }

int main(void){
	clock_t start_time, end_time;
	start_time = clock();

	hash_map<int, Circle*> bombHashMap; //id와 bomb
	hash_map<int, list<int>> gridBombHashMap;
	vector<list<int>*> saveListPointer; //여기있는놈 메모리 해제

	for (int i = 0; i < 1000000; ++i){
		list<int> * listArr = new list < int >;
		saveListPointer.push_back(listArr);
		gridBombHashMap.insert(hash_map < int, list<int> >::value_type(i, *listArr));
	}

	InputData(bombHashMap, gridBombHashMap);
	FindBombNumber(bombHashMap, gridBombHashMap);
	//ReleaseMemory(bombHashMap, gridBombHashMap, saveListPointer);

	end_time = clock();
	printf("Time : %f\n", ((double)(end_time - start_time)) / CLOCKS_PER_SEC);
	getchar();
	return 0;
}