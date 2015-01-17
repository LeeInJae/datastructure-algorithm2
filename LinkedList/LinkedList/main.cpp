#include<iostream>
#include "LinkedList.h"

using namespace std;

int main(void){
	LinkedList * list = new LinkedList;
	list->Create();
	list->Delete(10);
	list->Insert(10);
	list->Insert(20);
	list->Insert(30);
	list->Insert(40);
	list->Insert(50);
	list->Insert(100);
	list->PrintList();
	list->Search(10);
	list->Delete(100);
	list->PrintList();
	list->Delete(30);
	list->PrintList();
	list->Inverse();
	list->PrintList();
	getchar();
	return 0;
}