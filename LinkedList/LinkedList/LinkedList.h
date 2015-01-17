#pragma once

typedef struct _Node
{
	int data;
	struct _Node *next;
}Node;

class LinkedList
{
public:
	LinkedList();
	~LinkedList();
	
	void Create();
	void Insert(int data);
	void Delete(int data);
	void Search(int data);
	void PrintList();
	void Inverse();
	Node * GetHead(){ return mHead; }
	
private:
	Node * mHead;
};

