#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <time.h>

using namespace std;

#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"
#define MAX_BOMB 100

int Min(int a, int b){
	if (a < b)
		return a;
	return b;
}

struct Point{
	int x, y;
};
class Circle{
public:
	Circle(){}
	Circle(int inputX, int inputY, int inputR) {
		center.x = inputX;
		center.y = inputY;
		r = inputR;
	}

public:
	static bool Cmp(const Circle * t1, const Circle * t2) {
		if (t1->center.x < t2->center.x){
			return true;
		}
		else if (t1->center.x == t2->center.x){
			if (t1->center.y < t2->center.y)
				return true;
			else if (t1->center.y == t2->center.y){
				if (t1->r < t2->r)
					return true;
				return false;
			}
		}
		return false;
	}
	
	static bool Cmp2(const Circle * t1, const Circle * t2) {
		if (t1->center.y < t2->center.y){
			return true;
		}
		else if (t1->center.y == t2->center.y){
			if (t1->center.x < t2->center.x)
				return true;
			else if (t1->center.x == t2->center.x){
				if (t1->r < t2->r)
					return true;
				return false;
			}
		}
		return false;
	}

	Point GetCenter(){ return center;}
	int GetCenterX(){ return center.x; }
	int GetCenterY(){ return center.y; }
	int GetR(){ return r; }

	void SetSetNumber(int number){ setNumber = number; }
	int GetSetNumber(){ return setNumber; }
private:
	Point center;
	int r;
	int setNumber;
};

void InputData(vector<Circle *> & bombVector){
	FILE * fin;
	errno_t err;
	err = fopen_s(&fin, INPUT_FILE_NAME, "r");
	
	int tempN, tempX, tempY, tempR;
	
	fscanf_s(fin, "%d", &tempN);

	for (int i = 0; i < tempN; ++i){
		fscanf_s(fin, "%d %d %d", &tempX, &tempY, &tempR);

		bombVector.push_back(new Circle(tempX, tempY, tempR));
	}
	fclose(fin);
}

bool IsCollision(Circle * obj1, Circle * obj2){
	Point center1 = obj1->GetCenter();
	Point center2 = obj2->GetCenter();

	long long int dx = center1.x - center2.x;
	long long int dy = center1.y - center2.y;
	long long int d = dx*dx + dy*dy;
	long long int obj1R = obj1->GetR();
	long long int obj2R = obj2->GetR();

	long long int r = (obj1R + obj2R) * (obj1R + obj2R);
	if (r < 0 || d < 0)
		r = 0;
	if (r >= d){
		return true;
	}
	return false;
}


void FindMinBombCount(vector<Circle *> & bombVector){
	FILE * fout;
	errno_t err;
	err = fopen_s(&fout, OUTPUT_FILE_NAME, "w");

	int tempCount = 0;
	//x축 정렬
	sort(bombVector.begin(), bombVector.end(), Circle::Cmp);
	
	int preBorderStart, preBorderEnd, borderStart,borderEnd;
	int i, j;

	for (i = 0; i < bombVector.size(); ++i){
		bombVector[i]->SetSetNumber(i + 1);
	}

	preBorderStart = 0;
	preBorderEnd = 0;
	
	for (i = 0; i < bombVector.size(); ++i){
		Circle * objI = bombVector[i];
		borderStart = i;
		bool flag = false;
		for (j = borderStart; j < bombVector.size(); ++j){
			Circle * objJ = bombVector[j];
			
			if (objI->GetCenterX() != objJ->GetCenterX()){
				borderEnd = j;
				flag = true;
				break;
			}
		}

		if (flag == false){ //끝까지 다 같다면
			borderEnd = j;
		}

		for (int k = preBorderStart; k < preBorderEnd; ++k){
			Circle * objPivot = bombVector[k];
			for (int l = borderStart; l < borderEnd; ++l){
				Circle * objOper = bombVector[l];
				if (IsCollision(objPivot, objOper)){
					int min = Min(objPivot->GetSetNumber(), objOper->GetSetNumber());
					objPivot->SetSetNumber(min);
					objOper->SetSetNumber(min);
					tempCount++;
				}
			}
		}

		//////////////같은 좌표 새키들
		for (int k = i; k < borderEnd - 1; ++k){
			Circle * objPivot = bombVector[k];
			for (int l = k + 1; l < borderEnd; ++l){
				Circle * objOper = bombVector[l];

				if (IsCollision(objPivot, objOper)){
					int min = Min(objPivot->GetSetNumber(), objOper->GetSetNumber());
					objPivot->SetSetNumber(min);
					objOper->SetSetNumber(min);
					tempCount++;
				}
			}
		}

		if (borderEnd == bombVector.size())
			break;

		i = borderEnd - 1;
		preBorderStart = borderStart;
		preBorderEnd = borderEnd;
	}


	//y축 정렬
	sort(bombVector.begin(), bombVector.end(), Circle::Cmp2);
	
	preBorderStart = 0;
	preBorderEnd = 0;

	for (i = 0; i < bombVector.size(); ++i){
		Circle * objI = bombVector[i];
		borderStart = i;
		bool flag = false;
		for (j = borderStart; j < bombVector.size(); ++j){
			Circle * objJ = bombVector[j];

			if (objI->GetCenterY() != objJ->GetCenterY()){
				borderEnd = j;
				flag = true;
				break;
			}
		}
		if (flag == false){ //끝까지 다 같다면
			borderEnd = j;
		}

		for (int k = preBorderStart; k < preBorderEnd; ++k){
			Circle * objPivot = bombVector[k];
			for (int l = borderStart; l < borderEnd; ++l){
				Circle * objOper = bombVector[l];

				if (IsCollision(objPivot, objOper)){
					int min = Min(objPivot->GetSetNumber(), objOper->GetSetNumber());
					objPivot->SetSetNumber(min);
					objOper->SetSetNumber(min);
				}
			}
		}

		//////////////같은 좌표 새키들
		for (int k = i; k < borderEnd - 1; ++k){
			Circle * objPivot = bombVector[k];
			for (int l = k + 1; l < borderEnd; ++l){
				Circle * objOper = bombVector[l];

				if (IsCollision(objPivot, objOper)){
					int min = Min(objPivot->GetSetNumber(), objOper->GetSetNumber());
					objPivot->SetSetNumber(min);
					objOper->SetSetNumber(min);
				}
			}
		}
		if (borderEnd == bombVector.size())
			break;

		i = borderEnd - 1;
		preBorderStart = borderStart;
		preBorderEnd = borderEnd;
	}
	
	set<int> setGroup;
	for (int i = 0; i < bombVector.size(); ++i){
		setGroup.insert(bombVector[i]->GetSetNumber());
	}
	int res = setGroup.size();
	fprintf(fout, "%d\n", res);
	printf("%d\n", res);
	fclose(fout);
}

void ReleaseMemory(vector<Circle*> & bombVector){
	for (auto &i = bombVector.begin(); i != bombVector.end();){
		auto iter = i;
		auto obj = *iter;
		if (obj){
			i = bombVector.erase(iter);
			delete obj;
		}
	}
}

int main(void){
	clock_t start_time, end_time;
	start_time = clock();
	vector<Circle *> bombVector;

	InputData(bombVector);
	FindMinBombCount(bombVector);
	ReleaseMemory(bombVector);
	end_time = clock();
	printf("Time : %f\n", ((double)(end_time - start_time)) / CLOCKS_PER_SEC);
	getchar();
	return 0;
}