#include <iostream>

using namespace std;

typedef enum _Color{
	RED,
	BLACK,
}Color_t;

typedef struct _Node{
	Color_t			color;
	_Node *			leftChild;
	_Node *			rightChild;
	_Node *			parent;
	unsigned int	blackHeight;
	int				data;
}Node_t;

typedef struct _Tree{
	Node_t * root;
}Tree_t;

void NillNodeInit(Node_t * node){
	node->blackHeight = 0;
	node->color = BLACK;
	node->leftChild = nullptr;
	node->rightChild = nullptr;
	node->parent = nullptr;
	node->data = -1;
}

void RedBlackTreeInit(Tree_t * tree, Node_t * nillNode){
	tree->root = new Node_t;
	tree->root = nillNode;
	tree->root->parent = nillNode;
	tree->root->leftChild = nillNode;
	tree->root->rightChild = nillNode;
}

bool RedParentViolationCheck(Tree_t * tree, Node_t * node){
	if (node == nullptr)
		return false;

	if (tree->root == node)
		return true;

	if (node->parent->color == RED)
		return true;

	return false;
}

void LeftRotate(Tree_t * tree, Node_t * nodeX, Node_t * nillNode){
	Node_t * nodeY = nodeX->rightChild;

	nodeX->rightChild = nodeY->leftChild;
	if (nodeY->leftChild != nillNode){
		nodeY->leftChild->parent = nodeX;
	}

	nodeY->parent = nodeX->parent;
	if (nodeX->parent == nillNode)
		tree->root = nodeY;
	else if (nodeX == nodeX->parent->leftChild)
		nodeX->parent->leftChild = nodeY;
	else
		nodeX->parent->rightChild = nodeY;

	nodeY->leftChild = nodeX;
	nodeX->parent = nodeY;
}

void RightRotate(Tree_t * tree, Node_t * nodeY, Node_t * nillNode){
	Node_t * nodeX = nodeY->leftChild;

	nodeY->leftChild = nodeX->rightChild;
	if (nodeX->rightChild != nillNode){
		nodeX->rightChild->parent = nodeY;
	}

	nodeX->parent = nodeY->parent;
	if (nodeY->parent == nillNode)
		tree->root = nodeX;
	else if (nodeY == nodeY->parent->rightChild)
		nodeY->parent->rightChild = nodeX;
	else
		nodeY->parent->leftChild = nodeX;

	nodeX->rightChild = nodeY;
	nodeY->parent = nodeX;
}

void InsertFixUp(Tree_t * tree, Node_t * node, Node_t * nillNode){

	Node_t * fixupNode = node;
	Node_t * uncloeNode = nullptr;

	while (fixupNode->parent->color == RED){
		if (fixupNode->parent == fixupNode->parent->parent->leftChild){
			uncloeNode = fixupNode->parent->parent->rightChild;

			if (uncloeNode->color == RED){
				fixupNode->parent->color = BLACK;
				uncloeNode->color = BLACK;
				fixupNode->parent->parent->color = BLACK;
				fixupNode = fixupNode->parent->parent;
			}
			else{
				if (fixupNode == fixupNode->parent->rightChild){
					fixupNode = fixupNode->parent;
					LeftRotate(tree, fixupNode, nillNode);
				}
				fixupNode->parent->color = BLACK;
				fixupNode->parent->parent->color = RED;
				RightRotate(tree, fixupNode->parent->parent, nillNode);
			}
		}
		else{
			uncloeNode = fixupNode->parent->parent->rightChild;

			if (uncloeNode->color == RED){
				fixupNode->parent->color = BLACK;
				uncloeNode->color = BLACK;
				fixupNode->parent->parent->color = BLACK;
				fixupNode = fixupNode->parent->parent;
			}
			else{
				if (fixupNode == fixupNode->parent->leftChild){
					fixupNode = fixupNode->parent;
					RightRotate(tree, fixupNode, nillNode);
				}
				fixupNode->parent->color = BLACK;
				fixupNode->parent->parent->color = RED;
				LeftRotate(tree, fixupNode->parent->parent, nillNode);
			}
		}

	}
	tree->root->color = BLACK;
}

bool InsertNewNode(Tree_t * tree, int data, Node_t * nillNode){
	Node_t * newNode = new Node_t;
	newNode->color = RED;
	newNode->blackHeight = 0;
	newNode->leftChild = nillNode;
	newNode->rightChild = nillNode;
	newNode->parent = nillNode;
	newNode->data = data;

	Node_t * curNode = tree->root;
	Node_t * curNodeParent = curNode;

	if (curNode == nillNode){
		tree->root = newNode;
		//tree->root->color = BLACK;
		//return true;
	}
	else{
		while (curNode != nillNode){
			curNodeParent = curNode;
			if (curNode->data < newNode->data)
				curNode = curNode->rightChild;
			else if (curNode->data > newNode->data)
				curNode = curNode->leftChild;
			else{ // 중복데이터가 존재
				cout << "해당 데이터가 이미 존재합니다" << endl;
				return false;
			}
		}

		if (curNodeParent->data < newNode->data)
			curNodeParent->rightChild = newNode;
		else
			curNodeParent->leftChild = newNode;

		newNode->parent = curNodeParent;
		newNode->leftChild = nillNode;
		newNode->rightChild = nillNode;
	}

	if (RedParentViolationCheck(tree, newNode)){
		InsertFixUp(tree, newNode, nillNode);
	}
	return true;
}

int main(void){
	Tree_t * tree = new Tree_t;
	Node_t * nillNode = new Node_t;

	NillNodeInit(nillNode);
	RedBlackTreeInit(tree, nillNode);

	InsertNewNode(tree, 11, nillNode);
	InsertNewNode(tree, 2, nillNode);
	InsertNewNode(tree, 14, nillNode);
	getchar();
	return 0;
}