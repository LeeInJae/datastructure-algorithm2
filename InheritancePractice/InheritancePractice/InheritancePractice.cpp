#include <iostream>

using namespace std;

class Parent{
public:
	Parent(){};
	~Parent(){};

	void Print(){ cout << "���� �θ��� Print" << endl; }
};

class Child : public Parent{
public:
	Child(){};
	~Child(){};

	void Print(){ cout << "���� �ڽ��� Print" << endl; }
};

int main(void){
// 	Parent p1;
// 	Child c1;
// 	p1.Print(); //�θ����
// 	c1.Print(); //�ڽ����
// 
// 	Parent * pP1 = new Parent;//�θ�
// 	Child * cC1 = new Child;//�ڽ�
// 
// 	//(����Ű���ִ� �������� Ÿ�Կ� ���� ����)
// 	pP1->Print();//�θ����
// 	cC1->Print();//�ڽ����

	Parent * pP2;	
	Child * cC2 = new Child;

	pP2 = cC2;
	pP2->Print(); //virtual�� ������ pP2�� �θ��� Ÿ���̹Ƿ� �θ��� �Լ��� ȣ��(virtual�� ������ ��μ� ���� ����Ű�� ���� �Լ� ȣ��)

	getchar();
	return 0;
}