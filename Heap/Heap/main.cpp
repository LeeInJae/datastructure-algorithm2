#include <iostream>
#include "Heap.h"

using namespace std;

int main(void){
	Heap * heap = new Heap;
	heap->Create();
	heap->Insert(1);
	heap->Insert(4);
	heap->Insert(3);
	heap->PrintNode();
	heap->Insert(5);
	heap->Insert(7);
	heap->Insert(9);
	heap->PrintNode();
	
	if (heap->CheckTree(1)){
		cout << "해당 트리는 힙의 조건을 만족함" << endl;
	}
	heap->Sort();
	heap->PrintNode();
	getchar();
	return 0;
}