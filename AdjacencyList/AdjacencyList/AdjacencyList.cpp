#include <iostream>

#define VertexNum 5
#define EdgeNum 9
#define INF 10000000

using namespace std;

typedef struct _Vertex{
	int nodeId;
	_Vertex * prev;
	_Vertex * next;
	int weight;
}Vertex;

typedef struct _SingleLinkedList{
	Vertex * head;
}SingleList;

typedef struct _Edge{
	int s, e, weight;
}Edge;

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
		newNode->next = headNextNode;
		newNode->prev = arrAdj[u].head;
		headNextNode->prev = newNode;
		arrAdj[u].head->next = newNode;
		arrAdj[u].head->prev = newNode->next;
		headNextNode->next = arrAdj[u].head;
	}
	return true;
}

bool DistInit(int * dist){
	if (dist == nullptr)
		return false;
	for (int i = 0; i < VertexNum; ++i)
		dist[i] = INF;

	dist[0] = 0;
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

	edgeList[0].e = 0, edgeList[0].e = 1, edgeList[0].e = 6;
	edgeList[1].e = 0, edgeList[1].e = 3, edgeList[1].e = 7;
	edgeList[2].e = 1, edgeList[2].e = 2, edgeList[2].e = 5;
	edgeList[3].e = 1, edgeList[3].e = 4, edgeList[3].e = -4;
	edgeList[4].e = 1, edgeList[4].e = 3, edgeList[4].e = 8;
	edgeList[5].e = 2, edgeList[5].e = 1, edgeList[5].e = -2;
	edgeList[6].e = 3, edgeList[6].e = 4, edgeList[6].e = 9;
	edgeList[7].e = 4, edgeList[7].e = 0, edgeList[7].e = 2;
	edgeList[8].e = 4, edgeList[8].e = 2, edgeList[8].e = 7;
	return true;
}

bool BellmanFord(SingleList * arrAdj, Edge * edgeList, int * dist){
	if (arrAdj == nullptr || edgeList == nullptr)
		return false;

	for (int i = 0; i < EdgeNum; ++i){
		if (edgeList[i].weight >= INF) continue;
		if (dist[edgeList[i].s] >= INF) continue;

		if (dist[edgeList[i].e] > dist[edgeList[i].s] + edgeList[i].weight){
			dist[edgeList[i].e] = dist[edgeList[i].s] + edgeList[i].weight;
		}
	}
	return true;
}

int main(void){
	SingleList * arrAdj = new SingleList[VertexNum];
	int * dist = new int[VertexNum];
	Edge * edgeList = new Edge[EdgeNum];

	DistInit(dist);
	
	ArrAdjInit(arrAdj);
	
	InitEdgeList(edgeList);
	
	EdgeSetting(arrAdj, edgeList);
	
	BellmanFord(arrAdj, edgeList, dist);
	getchar();
	delete[] arrAdj;
	delete dist;
	return 0;
}