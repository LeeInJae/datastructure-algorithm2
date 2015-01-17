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
	heap->Sort();
	heap->PrintNode();
	getchar();
	return 0;
}