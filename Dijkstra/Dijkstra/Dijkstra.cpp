#include <iostream>

#define VertexNum 5
#define EdgeNum 10
#define INF 10000000
#define HeapSize 100

using namespace std;

typedef struct _Vertex{
	int nodeId;
	_Vertex * prev;
	_Vertex * next;
	int weight;
}Vertex;

typedef struct _SingleLinkedList{
	Vertex * head;
	int elementNumber;
}SingleList;

typedef struct _Edge{
	int s, e, weight;
}Edge;

typedef struct _Element{
	int vertexId;
	int dist;
}Element;

typedef struct _Heap{
	int size;
	int capacity;
	Element * e;
}Heap;

void Swap(Element * a, Element * b){
	Element temp = *a;
	*a = *b;
	*b = temp;
}

void ReleaseHeap(Heap * maxHeap){
	delete[] maxHeap->e;
}

int IsMaxHeap(Heap * minHeap, int curIndex){
	if (minHeap == nullptr)
		return 0;

	if (curIndex < 1 || curIndex > minHeap->size) return 1;

	if (minHeap->e[curIndex].dist == INF) return 1;

	if (curIndex * 2 <= minHeap->size && minHeap->e[curIndex * 2].dist < minHeap->e[curIndex].dist)
		return 0;
	if (curIndex * 2 + 1 <= minHeap->size && minHeap->e[curIndex * 2 + 1].dist < minHeap->e[curIndex].dist)
		return 0;
	if (IsMaxHeap(minHeap, curIndex * 2) != 1 || IsMaxHeap(minHeap, curIndex * 2 + 1) != 1)
		return 0;

	return 1;
}

void MinHeapify(Heap * minHeap, int pos){
	if (pos > minHeap->size)
		return;

	int largestIndex, leftIndex, rightIndex;
	
	largestIndex = pos;
	leftIndex = pos * 2;
	rightIndex = pos * 2 + 1;

	if (leftIndex <= minHeap->size && minHeap->e[leftIndex].dist < minHeap->e[largestIndex].dist)
		largestIndex = leftIndex;
	
	if (rightIndex <= minHeap->size && minHeap->e[rightIndex].dist < minHeap->e[largestIndex].dist)
		largestIndex = rightIndex;

	if (largestIndex != pos)
	{
		Swap(&(minHeap->e[pos]), &(minHeap->e[largestIndex]));
	}
	return;
}

void BuildMinHeap(Heap * minHeap){
	int firstParentNode = minHeap->size / 2;
	for (int i = firstParentNode; i >= 1; --i){
		MinHeapify(minHeap, i);
	}
}

Element HeapExtractMinimum(Heap * minHeap){
	Element min;
	min.dist = 0;
	min.vertexId = -1;
	
	if (minHeap->size < 1) return min;
	
	min = minHeap->e[1];
	minHeap->e[1] = minHeap->e[minHeap->size];
	--minHeap->size;
	MinHeapify(minHeap, 1);
	return min;
}

bool DecreaseKey(Heap * minHeap, int index, Element key){
	if (key.dist > minHeap->e[index].dist)
		return false;

	minHeap->e[index].dist = key.dist;
	minHeap->e[index].vertexId = key.vertexId;

	int parent = index / 2;
	while (index > 1 && minHeap->e[parent].dist > key.dist){
		Swap(&minHeap->e[parent], &minHeap->e[index]);
		index = parent;
	}
	return true;
}

void MinHeapInsert(Heap * minHeap, Element key){
	minHeap->size = minHeap->size + 1;
	minHeap->e[minHeap->size].dist = INF;
	minHeap->e[minHeap->size].vertexId = -1;
	DecreaseKey(minHeap,minHeap->size, key);
}

void MakeMinHeap(Heap * minHeap, int source){
	minHeap->size = 0;
	minHeap->capacity = HeapSize * 2;
	minHeap->e = new Element[minHeap->capacity + 1];

	for (int i = 1; i <= minHeap->capacity; ++i){
		minHeap->e[i].dist = INF;
		minHeap->e[i].vertexId = -1;
	}

	minHeap->e[source].dist = 0;
	minHeap->e[source].vertexId = source;
	MinHeapInsert(minHeap, minHeap->e[source]);
}

bool ArrAdjInit(SingleList * arrAdj){
	if (arrAdj == nullptr)
		return false;

	
	for (int i = 0; i < VertexNum; ++i){
		Vertex * dummyNode = new Vertex;
		dummyNode->prev = dummyNode;
		dummyNode->next = dummyNode;
		dummyNode->nodeId = -1;
		dummyNode->weight = 0;
		arrAdj[i].head = dummyNode;
		arrAdj[i].elementNumber = 0;
	}
	return true;
}

bool IsValid(int nodeId){
	if (nodeId < 0 || nodeId >= VertexNum)
		return false;
	return true;
}

bool InsertAdjVer(SingleList * arrAdj, int u, int  v, int weight){
	if (!IsValid(u) || !IsValid(v))
		return false;

	Vertex * newNode = new Vertex;
	Vertex * headNextNode = arrAdj[u].head->next;

	newNode->nodeId = v;
	newNode->weight = weight;

	if (headNextNode == arrAdj[u].head){//처음원소
		arrAdj[u].head->next = newNode;
		arrAdj[u].head->prev = newNode;
		newNode->prev = arrAdj[u].head;
		newNode->next = arrAdj[u].head;
	}
	else{
		arrAdj[u].head->prev->next = newNode;
		newNode->prev = arrAdj[u].head->prev;
		arrAdj[u].head->prev = newNode;
		newNode->next = arrAdj[u].head;
	}
	++arrAdj[u].elementNumber;
	return true;
}

bool DistInit(int * dist, int source){
	if (dist == nullptr)
		return false;
	for (int i = 0; i < VertexNum; ++i){
		dist[i] = INF;
	}
	dist[source] = 0;
	return true;
}

bool EdgeSetting(SingleList * arrAdj, Edge * edgeList){
	if (arrAdj == nullptr || edgeList == nullptr)
		return false;

	for (int i = 0; i < EdgeNum; ++i){
		InsertAdjVer(arrAdj, edgeList[i].s, edgeList[i].e, edgeList[i].weight);
	}
	return true;
}
bool InitEdgeList(Edge * edgeList){
	if (edgeList == nullptr)
		return false;

	edgeList[0].s = 0, edgeList[0].e = 1, edgeList[0].weight = 6;
	edgeList[1].s = 0, edgeList[1].e = 3, edgeList[1].weight = 7;
	edgeList[2].s = 1, edgeList[2].e = 2, edgeList[2].weight = 5;
	edgeList[3].s = 1, edgeList[3].e = 4, edgeList[3].weight = 4;
	edgeList[4].s = 1, edgeList[4].e = 3, edgeList[4].weight = 8;
	edgeList[5].s = 2, edgeList[5].e = 1, edgeList[5].weight = 2;
	edgeList[6].s = 3, edgeList[6].e = 4, edgeList[6].weight = 9;
	edgeList[7].s = 4, edgeList[7].e = 0, edgeList[7].weight = 2;
	edgeList[8].s = 4, edgeList[8].e = 2, edgeList[8].weight = 7;
	edgeList[9].s = 3, edgeList[9].e = 2, edgeList[9].weight = 3;
	return true;
}

void PrintEdgeList(SingleList * arrAdj){
	for (int i = 0; i < VertexNum; ++i){
		cout << i << "->  ";
		Vertex * curNode = arrAdj[i].head->next;
		for (int j = 0; j < arrAdj[i].elementNumber; ++j){
			cout << curNode->nodeId << "   , ";
			curNode = curNode->next;
		}
		cout << endl;
	}
}

bool Dijkstra(SingleList * arrAdj, int * dist, Heap * minHeap){
	if (arrAdj == nullptr)
		return false;

	Element curNode;

	while (minHeap->size != 0){
		curNode = HeapExtractMinimum(minHeap);
		if (curNode.vertexId < 0)
			continue;
		
		if (dist[curNode.vertexId] < curNode.dist) continue;
		Vertex * adjVer = arrAdj[curNode.vertexId].head->next;
		for (int i = 0; i < arrAdj[curNode.vertexId].elementNumber; ++i){
			if (dist[adjVer->nodeId] > curNode.dist + adjVer->weight){
				dist[adjVer->nodeId] = curNode.dist + adjVer->weight;
				
				Element key;
				key.dist = curNode.dist + adjVer->weight;
				key.vertexId = adjVer->nodeId;
				MinHeapInsert(minHeap, key);
			}
			adjVer = adjVer->next;
		}
	}
	return true;
}

int main(void){
	Vertex * v = new Vertex;
	SingleList * arrAdj = new SingleList[VertexNum];
	int * dist = new int[VertexNum];
	Edge * edgeList = new Edge[EdgeNum];
	Heap * minHeap = new Heap;
	int source = 0;
	
	DistInit(dist, source);
	MakeMinHeap(minHeap, source);
	ArrAdjInit(arrAdj);
	InitEdgeList(edgeList);
	EdgeSetting(arrAdj, edgeList);
	PrintEdgeList(arrAdj);

	Dijkstra(arrAdj, dist, minHeap);
	getchar();

	delete[] arrAdj;
	delete dist;
	delete minHeap;
	return 0;
}