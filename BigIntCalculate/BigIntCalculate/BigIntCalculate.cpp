#include <iostream>
#include <string.h>

#define MAX 1000

using namespace std;

struct Operator{
	int count;
	int position[MAX];
};

//���������� �����丵 �ʿ�
class OperationParsing{
public:
	OperationParsing(){
		Plus.count = 0;
		Sub.count = 0;
		Multi.count = 0;
		Pow.count = 0;
	}

	Operator Plus;
	Operator Sub;
	Operator Multi;
	Operator Pow;
};

//���������� �����丵 �ʿ�
class NumberParsing{
	
public:
	NumberParsing(){
		count = 0;
	}

	int count;
	int position[MAX][MAX];
	int length[MAX];
};

//calculate�� Operation�� Number�� �������� ����.
//���������� �����丵 �ʿ�
class Calculate{
public:
	Calculate(){
		operation = new OperationParsing;
		number = new NumberParsing;
		inputLength = 0;
	}
	int AddSubCalculate();

	OperationParsing * operation;
	NumberParsing * number;
	char inputNumber[MAX];
	int inputLength;
};

int PowCal(int number, int count){
	for (int i = 0; i < count; ++i){
		number *= 10;
	}
	return number;
}

bool IsOperation(char str){
	if (str == '+' || str == '-' || str == '*')
		return true;

	return false;
}

bool IsPow(char str1, char str2){
	if (str1 == '*' && str2 == '*')
		return true;

	return false;
}

int Calculate::AddSubCalculate()
{
	int leftSumNumber = 0;
	int rightSumNumber = 0;
	int tenPow = PowCal(1, number->length[0] - 1);

	//ù��° �̸� ���ڰ��
	for (int j = 0; j < number->length[0]; ++j){
		leftSumNumber += (number->position[0][j] * tenPow);
		tenPow /= 10;
	}
	number->count = 1;

	int addOperCount = 0;
	int subOpercount = 0;
	int addPos = -1;
	int subPos = -1;

	//���� ���� = ������ + 1
	for (int i = 0; i < (operation->Sub.count + operation->Plus.count); ++i){
		addPos = -1;
		subPos = -1;

		if (addOperCount < operation->Plus.count){
			addPos = operation->Plus.position[i];
			++addOperCount;
		}
		if (subOpercount < operation->Sub.count){
			subPos = operation->Sub.position[i];
			++subOpercount;
		}

		rightSumNumber = 0;
		tenPow = PowCal(1, number->length[i + 1] - 1);

		for (int j = 0; j < number->length[i + 1]; ++j){
			rightSumNumber += (number->position[i + 1][j] * tenPow);
			tenPow /= 10;
		}

		//�����丵 ���� �� ����(���� �ʿ�)
		//���� ���۷����Ͱ� �������� ���� addPos�� subPos�� Ȯ��
		//���� �����ڿ�  +�� �ְ�, - �����ڴ� ���̻� ���ٸ� + ������
		//���� �����ڿ� -�� �ְ�,  + �����ڴ� ���̻� ���ٸ� - ������
		//���� ������ �� + �� -�� ���ÿ� �����Ѵٸ� �� �� �������� �����ڸ� ó�����־����
		//���� +�� -�������� ī������ ���ִ� ���� subOpercount �� addOperCount�� ������ �ʿ�.
		///////////////////////////////////////////////////////////////////////////////
		if (subPos == -1){
			leftSumNumber += rightSumNumber;
			if (subOpercount != 0)
				--subOpercount;
		}
		else if (addPos == -1){
			leftSumNumber -= rightSumNumber;
			if (addOperCount != 0)
				--addOperCount;
		}
		else if (subPos < addPos){
			leftSumNumber -= rightSumNumber;
			--addOperCount;
		}
		else if (subPos > addPos){
			leftSumNumber += rightSumNumber;
			--subOpercount;
		}
		///////////////////////////////////////////////
	}
	return leftSumNumber;
}

void Parsing(Calculate * calculate){
	for (int i = 0; i < calculate->inputLength; ++i){
		if (IsOperation(calculate->inputNumber[i])){
			if (IsPow(calculate->inputNumber[i], calculate->inputNumber[i + 1])){
				calculate->operation->Pow.position[calculate->operation->Pow.count] = i;
				++calculate->operation->Pow.count;
				continue;
			}
			else{
				switch (calculate->inputNumber[i])
				{
				case '+':
					calculate->operation->Plus.position[calculate->operation->Plus.count] = i;
					++calculate->operation->Plus.count;
					break;
				case '-':
					calculate->operation->Sub.position[calculate->operation->Sub.count] = i;
					++calculate->operation->Sub.count;
					break;
				case '*':
					calculate->operation->Multi.position[calculate->operation->Multi.count] = i;
					++calculate->operation->Multi.count;
					break;
				default:
					break;
				}
			}
		}
		else
		{
			calculate->number->length[calculate->number->count] = 0;
			while (calculate->inputNumber[i] - '0' >= 0 && calculate->inputNumber[i] - '0' <= 9){
				calculate->number->position[calculate->number->count][calculate->number->length[calculate->number->count]] = calculate->inputNumber[i] - '0';
				++(calculate->number->length[calculate->number->count]);
				++i;
			}
			--i;
			++calculate->number->count;
		}
	}
}

int main(void){
	Calculate * calculate = new Calculate;

	//���� +�����ڸ� �ְų� - �����ڸ� ������� ���( ���������� ������ �κ� �����ʿ�)
	strcpy_s(calculate->inputNumber, _countof(calculate->inputNumber), "100-100-250-3000");
	calculate->inputLength = strlen(calculate->inputNumber);
	Parsing(calculate);
	cout << calculate->AddSubCalculate() << endl;
	
	getchar();

	delete calculate;
	return 0;
}