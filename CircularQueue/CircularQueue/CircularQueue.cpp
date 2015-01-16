#include "CircularQueue.h"
#include <iostream>

using namespace std;

CircularQueue::CircularQueue()
{ 
	mRear = -1;
	mFront = -1;
}


CircularQueue::~CircularQueue()
{
}

void CircularQueue::CreateQueue(int size)
{
	mSize = size;
	mElement = new int[size];
}

void CircularQueue::ReleaseQueue()
{
	delete[] mElement;
}

bool CircularQueue::IsEmpty()
{
	if (mRear == mFront)
	{
		cout << "queue is Empty" << endl;
		return true;
	}
	return false;
}

bool CircularQueue::IsFull()
{
	if ( (mRear + 1) % mSize == mFront || (mRear == mSize -1 && mFront == -1) )
	{
		cout << "queue is Full" << endl;
		return true;
	}
	return false;
}

void CircularQueue::Enqueue(int data)
{
	if (IsFull())
		return;

	mRear = (mRear + 1) % mSize;
	mElement[mRear] = data;

}

int CircularQueue::Dequeue()
{
	if (IsEmpty())
		return -1;

	mFront = (mFront + 1) % mSize;
	return mElement[mFront];
}