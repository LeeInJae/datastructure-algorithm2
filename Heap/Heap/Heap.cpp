#include "Heap.h"
#include <iostream>

#define INF 10000000
#define MaxCapacity 5
using namespace std;

void Swap(int * a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

Heap::Heap()
{
	mCapacity = MaxCapacity;
}


Heap::~Heap()
{
}

void Heap::Create()
{
	mSize = 0;
	mNode = new int[MaxCapacity];
}

bool Heap::CheckTree(int nodeIndex)
{
	if (nodeIndex >= mSize)
		return true;

	if (nodeIndex * 2 >= mSize && mNode[nodeIndex] < mNode[nodeIndex * 2])
		return false;
	if (nodeIndex * 2 + 1 >= mSize && mNode[nodeIndex] < mNode[nodeIndex * 2 + 1])
		return false;

	if (!CheckTree(nodeIndex * 2) || !CheckTree(nodeIndex * 2 + 1))
		return false;
	return true;
}

void Heap::MaxHeapfify(int nodeIndex)
{
	if (nodeIndex >= mSize)
		return;

	int left = nodeIndex * 2;
	int right = nodeIndex * 2 + 1;
	int maxPosition= nodeIndex;
	int max = mNode[nodeIndex];

	if (left < mSize && mNode[left]>max){
		maxPosition = left;
		max = mNode[left];
	}

	if (right<mSize && mSize && mNode[right]>max){
		maxPosition = right;
		max = mNode[right];
	}
	if (maxPosition != nodeIndex){
		Swap(&(mNode[nodeIndex]), &(mNode[maxPosition]));
		MaxHeapfify(maxPosition);
	}
}

void Heap::BuildMaxHeap()
{
	for (int i = mSize / 2; i >= 0; --i){
		MaxHeapfify(i);
	}
}

void Heap::Insert(int data)
{
	if (IsFull()){
		cout << "꽉찼습니다" << endl;
		return;
	}
	mSize = mSize + 1;
	mNode[mSize] = -INF;
	IncreaseKey(mSize, data);
}

void Heap::IncreaseKey(int nodeIndex, int data)
{
	if (data < mNode[mSize])
		cout << "잘못된 데이터의 증가" << endl;

	mNode[mSize] = data;
	while (nodeIndex > 1 && mNode[nodeIndex / 2] < data){
		Swap(&(mNode[nodeIndex]), &(mNode[nodeIndex / 2]));
		nodeIndex = nodeIndex / 2;
	}
}

int Heap::ExtractMin()
{
	if (IsEmpty()){
		cout << "heap에 아무것도 없다" << endl;
		return INF;
	}

	int max = mNode[1];
	mNode[1] = mNode[mSize];
	mSize = mSize - 1;
	MaxHeapfify(1);
	return max;
}

bool Heap::IsFull()
{
	if (mSize == mCapacity)
		return true;
	return false;
}

bool Heap::IsEmpty()
{
	if (mSize == 0)
		return true;
	return false;
}

void Heap::PrintNode()
{
	for (int i = 1; i <= mSize; ++i){
		cout << mNode[i] << " ";
	}
	cout << endl;
}

void Heap::Sort()
{
	int tempSize = mSize;
	while (mSize > 0){
		Swap(&(mNode[1]), &(mNode[mSize]));
		mSize = mSize - 1;
		MaxHeapfify(1);
	}
	mSize = tempSize;
}
