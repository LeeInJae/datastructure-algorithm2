#include <stdio.h>
#include <iostream>

#define INF 10000000

typedef struct heap{
	int size;
	int capacity;
	int *element;
}heap_t;

void Swap(int * a, int * b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void MakeSampleHeap(heap_t * maxHeap, int n){
	//FILE * fin;
	//errno_t err = fopen_s(&fin, "input.txt", "r");
	//fscanf_s(fin, "%d", &maxHeap->size);
	maxHeap->size = n;
	maxHeap->capacity = 20;
	maxHeap->element = (int *)malloc(sizeof(int) * (maxHeap->capacity + 1));

	for (int i = 0; i <= maxHeap->capacity; ++i){
		maxHeap->element[i] = -INF;
	}
	maxHeap->element[1] = 7;
	maxHeap->element[2] = 8;
	maxHeap->element[3] = 4;
	maxHeap->element[4] = 9;
	maxHeap->element[5] = 10;
	maxHeap->element[6] = 5;
	maxHeap->element[7] = 12;
	maxHeap->element[8] = 13;
	maxHeap->element[9] = 17;
	// 	for (int i = 1; i <= maxHeap->size; ++i){
	// 		fscanf_s(fin, "%d", &maxHeap->element[i]);
	// 	}
	// 	fclose(fin);
}

// void MaxHeapify(heap_t * maxHeap, int pos){ //iteration으로 구현
// 	int curIndex, curKey, leftNode, rightNode;
// 	
// 	curIndex = pos;
// 	curKey = maxHeap->element[curIndex];
// 	while (1){//양쪽 자식 다 있는 경우, 왼쪽만 있는경우, 없는경우
// 		if (curIndex * 2 > maxHeap->size && curIndex * 2 + 1 > maxHeap->size) break;
// 		
// 		if (curIndex * 2 <= maxHeap->size && curIndex * 2 + 1 <= maxHeap->size){
// 			leftNode = maxHeap->element[curIndex * 2];
// 			rightNode = maxHeap->element[curIndex * 2 + 1];
// 
// 			if (leftNode > rightNode && curKey < leftNode){
// 				Swap(&maxHeap->element[curIndex * 2], &maxHeap->element[curIndex]);
// 				curIndex = curIndex * 2;
// 			}
// 			else if (leftNode < rightNode && curKey < rightNode){
// 				Swap(&maxHeap->element[curIndex * 2 + 1], &maxHeap->element[curIndex]);
// 				curIndex = curIndex * 2 + 1;
// 			}
// 		}
// 		else if (curIndex * 2 <= maxHeap->size && curIndex * 2 + 1 > maxHeap->size){
// 			leftNode = maxHeap->element[curIndex * 2];
// 
// 			if (leftNode > rightNode && curKey < leftNode){
// 				Swap(&maxHeap->element[curIndex * 2], &maxHeap->element[curIndex]);
// 				curIndex = curIndex * 2;
// 			}
// 		}
// 	}
// }

void MaxHeapify(heap_t * maxHeap, int pos){ //recursive으로 구현
	if (pos > maxHeap->size) return;

	int largestIndex, leftIndex, rightIndex;

	largestIndex = pos;
	leftIndex = pos * 2;
	rightIndex = pos * 2 + 1;

	if (leftIndex <= maxHeap->size && maxHeap->element[leftIndex] > maxHeap->element[largestIndex]){
		largestIndex = leftIndex;
	}

	if (rightIndex <= maxHeap->size && maxHeap->element[rightIndex] > maxHeap->element[largestIndex]){
		largestIndex = rightIndex;
	}

	if (largestIndex != pos){
		Swap(&maxHeap->element[pos], &maxHeap->element[largestIndex]);
		MaxHeapify(maxHeap, largestIndex);
	}
	return;
}

void PrintHeap(heap_t * maxHeap){
	for (int i = 1; i <= maxHeap->size; ++i){
		printf("%d  ", maxHeap->element[i]);
	}
	printf("\n");
}

void ReleaseHeap(heap_t * maxHeap){
	delete[] maxHeap->element;
}

int IsMaxHeap(heap_t * maxHeap, int size, int curIndex){
	if (curIndex < 1 || curIndex > maxHeap->size) return 1;
	if (maxHeap->element[curIndex] == NULL) return 1;

	if (curIndex * 2 <= maxHeap->size && maxHeap->element[curIndex * 2] > maxHeap->element[curIndex])
		return 0;
	if (curIndex * 2 + 1 <= maxHeap->size && maxHeap->element[curIndex * 2 + 1] > maxHeap->element[curIndex])
		return 0;
	if (IsMaxHeap(maxHeap, size, curIndex * 2) != 1 || IsMaxHeap(maxHeap, size, curIndex * 2 + 1) != 1)
		return 0;

	return 1;
}

void BuildMaxHeap(heap_t * maxHeap){
	int firstParentNode = maxHeap->size / 2;
	for (int i = firstParentNode; i >= 1; --i){
		MaxHeapify(maxHeap, i);
	}
}

int main(void){
	heap_t * maxHeap = (heap_t *)malloc(sizeof(heap_t));

	MakeSampleHeap(maxHeap, 9);
	BuildMaxHeap(maxHeap);

	//MaxHeapify(maxHeap, 3);
	PrintHeap(maxHeap);

	if (IsMaxHeap(maxHeap, maxHeap->size, 1))
		printf("maxHeap이 맞습니다.\n");
	else
		printf("maxHeap이 아닙니다.\n");

	ReleaseHeap(maxHeap);//element도 따로 삭제
	delete maxHeap;
	getchar();
	return 0;
}