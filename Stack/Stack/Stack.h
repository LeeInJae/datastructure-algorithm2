#pragma once

class Stack
{
public:
	Stack();
	void CreateStack(int size);
	void ReleaseStack();
	bool IsEmpty();
	bool IsFull();
	void Push(int data);
	int Pop();
private:
	int * mElement;
	int mTop;
	int mSize;
	~Stack();
};