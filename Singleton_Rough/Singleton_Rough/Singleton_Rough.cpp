#include <iostream>
using namespace std;

#define N_UNIT 100
#define ATTACK_UNIT 1
#define PROTECT_UNIT 2

class GameUnit{
public:
	virtual void Display(int x, int y) = 0;
	virtual void DoAction() = 0;
};

class AttackUnit : public GameUnit{
public:
	void Display(int x, int y){}
	void DoAction(){}
};

class ProtectUnit : public GameUnit{
public:
	void Display(int x, int y){}
	void DoAction(){}
};

GameUnit * pUnitArray[N_UNIT];

void InitUnitArray(){
	for (int i = 0; i < N_UNIT; ++i){
		pUnitArray[i] = 0;
	}
}

GameUnit * CreateNewUnit(int unitType){ //게임 유닛에 대한 생성 요청에 대해 전역변수인 pUnitArray 배열 변수에 빈 공간이 있을때에만 게임 유닛을 생성해줌.
	for (int i = 0; i < N_UNIT; ++i){//pUnitArray는 N_UNIT만큼의 크기를 가짐.
		if (pUnitArray[i] == 0){
			if (unitType == ATTACK_UNIT)
				pUnitArray[i] = new AttackUnit;
			else
				pUnitArray[i] = new ProtectUnit;
			return pUnitArray[i];
		}
	}
	return 0;
}

void DestroyUnit(GameUnit * pUnit){
	for (int i = 0; i < N_UNIT; ++i){
		if (pUnitArray[i] == pUnit){
			delete pUnitArray[i];
			pUnitArray[i] = 0;
			return;
		}
	}
}

int main(){
	InitUnitArray();

	GameUnit * pUnit1 = CreateNewUnit(ATTACK_UNIT);
	if (pUnit1 == 0)
		cout << "No more create unit" << endl;

	GameUnit * pUnit2 = CreateNewUnit(PROTECT_UNIT);
	if (pUnit2 == 0)
		cout << "No more create Unit" << endl;
	
	GameUnit * pUnit3 = new ProtectUnit();  //CreateNewUnit이 아닌 클래스의 직접 생성자를 호출해서 생성하게되면, 이는 싱글톤의 의미가 없어지게된다.
	if (pUnit3 == 0)
		cout << "No more create Unit" << endl;

	DestroyUnit(pUnit1);
	DestroyUnit(pUnit2);
	DestroyUnit(pUnit3);

	//전역변수를 이용한 싱글톤역할을 하게 하는데에있어서의 문제점은. 직접 클래스의 생성자를 통해서 객체를 생성가능하다는 것과, 
	//클래스 자체적으로 최대 N개의 객체만 생성할 수 있게 할 수 없게 때문이다.
	return 0;
}