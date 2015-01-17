#include "LinkedList.h"
#include <iostream>

using namespace std;

LinkedList::LinkedList()
{
}


LinkedList::~LinkedList()
{
}

void LinkedList::Create()
{
	Node * sentinalNode = new Node;
	sentinalNode->next = nullptr;

	mHead = sentinalNode;
}

void LinkedList::Insert(int data)
{
	Node * curNode = mHead->next;
	Node * newNode = new Node;
	newNode->data = data;
	newNode->next = curNode;

	mHead->next = newNode;
}

void LinkedList::Delete(int data)
{
	Node * curNode = mHead->next;
	if (curNode == nullptr){
		cout << "����Ʈ�� ������ϴ�" << endl;
		return;
	}

	Node * prevNode = mHead;

	while (curNode){
		if (curNode->data == data){
			prevNode->next = curNode->next;
			delete curNode;
			curNode = nullptr;
			break;
		}
		prevNode = curNode;
		curNode = curNode->next;
	}
}

void LinkedList::Search(int data)
{
	Node * curNode = mHead->next;
	if (curNode == nullptr){
		cout << "����Ʈ�� ������ϴ�" << endl;
		return;
	}

	while (curNode){
		if (curNode->data == data){
			cout << curNode->data << "�ش� �����Ͱ� �����մϴ�" << endl;
		}
		curNode = curNode->next;
	}
	cout << endl;
}

void LinkedList::PrintList()
{
	Node * curNode = mHead->next;
	if (curNode == nullptr){
		cout << "����Ʈ�� ������ϴ�" << endl;
		return;
	}

	while (curNode){
		cout << curNode->data << " ";
		curNode = curNode->next;
	}
	cout << endl;
}

void LinkedList::Inverse()
{
	Node * newHead = nullptr;
	Node * tempHead = mHead->next;
	Node * tempNode = nullptr;

	while (tempHead){
		tempNode = tempHead;
		tempHead = tempHead->next;
		tempNode->next = newHead;
		newHead = tempNode;
	}

	Node * sentinalNode = new Node;
	sentinalNode->next = newHead;
	newHead = sentinalNode;
	mHead = newHead;
}
