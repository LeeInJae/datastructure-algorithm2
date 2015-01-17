#pragma once
#define MAX 100

class Heap
{
public:
	Heap();
	~Heap();
	void Create();
	void Insert(int data);
	void Delete(int data);
	bool CheckTree(int nodeIndex);
	int ExtractMin();
	void MaxHeapfify(int nodeIndex);
	void BuildMaxHeap();
	void IncreaseKey(int nodeIndex, int data);
	bool IsFull();
	bool IsEmpty();
	void PrintNode();
	void Sort();
private:
	int * mNode;
	int mSize;
	int mCapacity;
};

