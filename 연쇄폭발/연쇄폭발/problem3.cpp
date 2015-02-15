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

void InputData(hash_map<int, Circle*> & bombHashMap, hash_map<int, list<Circle *>> & gridBombHashMap){
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
		list<Circle *> & gridList = gridBombHashMap[tempGrid];
		gridList.push_back(bombHashMap[i]);
	}
	fclose(fin);
}

void FindBombNumber(hash_map<int, Circle*> & bombHashMap, hash_map<int, list<Circle *>> & gridBombHashMap){
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

		if (explosionCircle.empty()){ //stack�� ���������, ���� ���� ��ź���� �Ѱ��� Ǫ������
			++res;//��ź �� �� �� �Ͷ߷�����

			auto iter = bombHashMap.begin();
			auto obj = iter->second;
			
			bombHashMap.erase(iter);//���� �ִ� ��ź�� ��ź ����Ʈ���� �������־����
			//explosionCircle.push(obj);
			curCicle = obj;

			int curGrid = obj->GetGridNumber(); //���� ���ÿ� �ִ� ��ź�� �׸��忡�� �������־����
			list<Circle *> & curGridList = gridBombHashMap[curGrid];
			
			for (auto i = curGridList.begin(); i != curGridList.end();){
				auto iter = i;
				auto loopObj = *iter;
				if (loopObj == curCicle){
					curGridList.erase(iter);
					break;
				}
			}
		} 
		else{//���� ���� �ʿ�(stack���� �ٷ� ������ ���)
			auto obj = explosionCircle.top();
			explosionCircle.pop();
			curCicle = obj;
		}
		
		int curGrid = curCicle->GetGridNumber();
		//list<Circle *> & curGridList = gridBombHashMap[curGrid];

		for (int j = 0; j < 9; ++j){
			int adjGrid = curGrid + gridInterval*adjGridAssist[j].x + adjGridAssist[j].y;
			if (adjGrid < 0 || adjGrid > gridInterval * gridInterval - 1) // ���� ����� �׸��� �˻� ����
				continue;

			list<Circle *> & adjGridList = gridBombHashMap[adjGrid];
			
			for (auto k = adjGridList.begin(); k != adjGridList.end();){
				auto iter = k;
				auto obj = *iter;

				if (IsCollision(curCicle, obj)){ //�浹 ���ٸ� �ش� �浹�� ��ź�� data bombHashmap���� ����
					explosionCircle.push(obj);
					auto deleteIter = bombHashMap.find(obj->GetId());
					bombHashMap.erase(deleteIter);
					k = adjGridList.erase(iter);
				}
				else
					++k;
			}
		}
		delete curCicle; //���� ����� ��ź�� �Ͷ߷����Ƿ� ���� �������� ����.
	}
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
	
	hash_map<int, Circle*> bombHashMap; //id�� bomb
	hash_map<int, list<Circle *>> gridBombHashMap;
	vector<list<Circle *>*> saveListPointer; //�����ִ³� �޸� ����

	for (int i = 0; i < 1000000; ++i){
		list<Circle *> * listArr = new list < Circle * >;
		saveListPointer.push_back(listArr);
		gridBombHashMap.insert(hash_map < int, list<Circle *> >::value_type(i, *listArr));
	}

	InputData(bombHashMap, gridBombHashMap);
	FindBombNumber(bombHashMap, gridBombHashMap);
	//ReleaseMemory(bombHashMap, gridBombHashMap, saveListPointer);

	end_time = clock();
	printf("Time : %f\n", ((double)(end_time - start_time)) / CLOCKS_PER_SEC);
	getchar();
	return 0;
}