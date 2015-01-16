#include "Stack.h"
#include <iostream>

using namespace std;

Stack::Stack(){
	mTop = -1;
}


Stack::~Stack()
{
}

void Stack::CreateStack(int size)
{
	mSize = size;
	mElement = new int[size];
}

void Stack::ReleaseStack()
{
	delete[] mElement;
}

bool Stack::IsEmpty()
{
	if (mTop == -1)
	{
		cout << "stack is Empty" << endl;
		return true;
	}
	return false;
}

bool Stack::IsFull()
{
	if (mTop == mSize - 1)
	{
		cout << "stakc is Full" << endl;
		return true;
	}
	return false;

}

void Stack::Push(int data)
{
	if (IsFull())
		return;

	++mTop;
	mElement[mTop] = data;
}

int Stack::Pop()
{
	if (IsEmpty())
		return -1;
	--mTop;

	return mElement[mTop + 1];
}


