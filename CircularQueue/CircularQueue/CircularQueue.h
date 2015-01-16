#pragma once
class CircularQueue
{
public:
	CircularQueue();
	~CircularQueue();

	void CreateQueue(int size);
	void ReleaseQueue();
	void Enqueue(int data);
	int Dequeue();
	bool IsEmpty();
	bool IsFull();

private:
	int mRear, mFront;
	int * mElement;
	int mSize;
};

