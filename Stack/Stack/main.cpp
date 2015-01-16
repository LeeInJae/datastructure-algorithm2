#include <iostream>
#include "Stack.h"

using namespace std;

int main(void){
	Stack * stack = new Stack();
	stack->CreateStack(3);

	stack->Push(1);
	stack->Push(2);
	stack->Push(3);
	stack->Push(4);
	
	cout << stack->Pop() << endl;
	cout << stack->Pop() << endl;
	cout << stack->Pop() << endl;
	cout << stack->Pop() << endl;
	getchar();
	return 0;
}