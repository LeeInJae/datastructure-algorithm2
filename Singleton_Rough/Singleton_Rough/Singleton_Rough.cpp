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

GameUnit * CreateNewUnit(int unitType){ //���� ���ֿ� ���� ���� ��û�� ���� ���������� pUnitArray �迭 ������ �� ������ ���������� ���� ������ ��������.
	for (int i = 0; i < N_UNIT; ++i){//pUnitArray�� N_UNIT��ŭ�� ũ�⸦ ����.
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
	
	GameUnit * pUnit3 = new ProtectUnit();  //CreateNewUnit�� �ƴ� Ŭ������ ���� �����ڸ� ȣ���ؼ� �����ϰԵǸ�, �̴� �̱����� �ǹ̰� �������Եȴ�.
	if (pUnit3 == 0)
		cout << "No more create Unit" << endl;

	DestroyUnit(pUnit1);
	DestroyUnit(pUnit2);
	DestroyUnit(pUnit3);

	//���������� �̿��� �̱��濪���� �ϰ� �ϴµ����־�� ��������. ���� Ŭ������ �����ڸ� ���ؼ� ��ü�� ���������ϴٴ� �Ͱ�, 
	//Ŭ���� ��ü������ �ִ� N���� ��ü�� ������ �� �ְ� �� �� ���� �����̴�.
	return 0;
}