#include <iostream>
#include "CircularQueue.h"

using namespace std;

int main(void){
	CircularQueue * queue = new CircularQueue;
	queue->CreateQueue(3);
	queue->Dequeue();
	queue->Enqueue(1);
	queue->Enqueue(2);
	queue->Enqueue(3);
	queue->Enqueue(4);
	
	cout << queue->Dequeue() << endl;
	cout << queue->Dequeue() << endl;
	cout << queue->Dequeue() << endl;
	cout << queue->Dequeue() << endl;

	getchar();
	return 0;
}