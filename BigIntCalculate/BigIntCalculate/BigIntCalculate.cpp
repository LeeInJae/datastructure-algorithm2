#include <iostream>
#include <string.h>

#define MAX 1000

using namespace std;

struct Operator{
	int count;
	int position[MAX];
};

//접근제어자 리팩토링 필요
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

//접근제어자 리팩토링 필요
class NumberParsing{
	
public:
	NumberParsing(){
		count = 0;
	}

	int count;
	int position[MAX][MAX];
	int length[MAX];
};

//calculate가 Operation과 Number를 가지도록 만듦.
//접근제어자 리팩토링 필요
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

	//첫번째 미리 숫자계산
	for (int j = 0; j < number->length[0]; ++j){
		leftSumNumber += (number->position[0][j] * tenPow);
		tenPow /= 10;
	}
	number->count = 1;

	int addOperCount = 0;
	int subOpercount = 0;
	int addPos = -1;
	int subPos = -1;

	//숫자 갯수 = 연산자 + 1
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

		//리팩토링 과정 중 버그(수정 필요)
		//다음 오퍼레이터가 무엇인지 각각 addPos와 subPos로 확인
		//다음 연산자에  +가 있고, - 연산자는 더이상 없다면 + 연산을
		//다음 연산자에 -가 있고,  + 연산자는 더이상 없다면 - 연산을
		//남은 연산자 중 + 와 -가 동시에 존재한다면 둘 중 먼저나온 연산자를 처리해주어야함
		//현재 +와 -연산자의 카운팅을 해주는 변수 subOpercount 와 addOperCount의 수정이 필요.
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

	//현재 +연산자만 있거나 - 연산자만 있을경우 계산( 섞여있을시 연산자 부분 수정필요)
	strcpy_s(calculate->inputNumber, _countof(calculate->inputNumber), "100-100-250-3000");
	calculate->inputLength = strlen(calculate->inputNumber);
	Parsing(calculate);
	cout << calculate->AddSubCalculate() << endl;
	
	getchar();

	delete calculate;
	return 0;
}