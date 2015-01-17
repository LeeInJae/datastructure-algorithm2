#include <iostream>

using namespace std;

class Parent{
public:
	Parent(){};
	~Parent(){};

	void Print(){ cout << "나는 부모의 Print" << endl; }
};

class Child : public Parent{
public:
	Child(){};
	~Child(){};

	void Print(){ cout << "나는 자식의 Print" << endl; }
};

int main(void){
// 	Parent p1;
// 	Child c1;
// 	p1.Print(); //부모출력
// 	c1.Print(); //자식출력
// 
// 	Parent * pP1 = new Parent;//부모
// 	Child * cC1 = new Child;//자식
// 
// 	//(가리키고있는 포인터의 타입에 따라 결정)
// 	pP1->Print();//부모출력
// 	cC1->Print();//자식출력

	Parent * pP2;	
	Child * cC2 = new Child;

	pP2 = cC2;
	pP2->Print(); //virtual이 없으면 pP2는 부모의 타입이므로 부모의 함수가 호출(virtual이 있으면 비로소 실제 가리키는 것의 함수 호출)

	getchar();
	return 0;
}