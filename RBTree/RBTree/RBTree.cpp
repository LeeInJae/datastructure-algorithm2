#include <iostream>
#include <queue>

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

bool NillNodeInit(Node_t * node){
	if (node == nullptr)
		return false;

	node->blackHeight = 0;
	node->color = BLACK;
	node->leftChild = nullptr;
	node->rightChild = nullptr;
	node->parent = nullptr;
	node->data = -1;
	return true;
}

bool RedBlackTreeInit(Tree_t * tree, Node_t * nillNode){
	if (tree == nullptr || nillNode == nullptr)
		return false;
	tree->root = nillNode;
	tree->root->parent = nillNode;
	tree->root->leftChild = nillNode;
	tree->root->rightChild = nillNode;
	return false;
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

bool LeftRotate(Tree_t * tree, Node_t * nodeX, Node_t * nillNode){
	if (tree == nullptr || nodeX == nullptr)
		return false;
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
	return true;
}

bool RightRotate(Tree_t * tree, Node_t * nodeY, Node_t * nillNode){
	if (tree == nullptr || nodeY == nullptr)
		return false;
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
	return true;
}

bool InsertFixUp(Tree_t * tree, Node_t * node, Node_t * nillNode){
	if (tree == nullptr || node == nullptr)
		return false;
	Node_t * fixupNode = node;
	Node_t * uncloeNode = nullptr;

	while (fixupNode->parent->color == RED){
		if (fixupNode->parent == fixupNode->parent->parent->leftChild){
			uncloeNode = fixupNode->parent->parent->rightChild;

			if (uncloeNode->color == RED){
				fixupNode->parent->color = BLACK;
				uncloeNode->color = BLACK;
				fixupNode->parent->parent->color = RED;
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
			uncloeNode = fixupNode->parent->parent->leftChild;

			if (uncloeNode->color == RED){
				fixupNode->parent->color = BLACK;
				uncloeNode->color = BLACK;
				fixupNode->parent->parent->color = RED;
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
	return true;
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

// bool PrintLevelTreeOrder(Tree_t * tree){
// 	if (tree == nullptr)
// 		return false;
// 
// 	queue<Node_t *> q;
// 	q.push(tree->root);
// 
// 	while (!q.empty()){
// 		Node_t * curNode = q.front();
// 		cout << curNode->data << curNode->color << endl;
// 
// 		if (curNode->leftChild != nullptr){
// 			q.push(curNode->leftChild);
// 		}
// 		if (curNode->rightChild != nullptr){
// 			q.push(curNode->rightChild);
// 		}
// 
// 		q.pop();
// 	}
// 	return true;
// }

Node_t * SearchNode(Tree_t * tree, int key, Node_t * nillNode){
	if (tree == nullptr || tree->root == nillNode)
		return nullptr;
	
	Node_t * curNode = tree->root;
	Node_t * curNodeParent = nullptr;

	while (curNode != nillNode){
		curNodeParent = curNode;
		if (curNode->data == key)
			break;
		else if (curNode->data < key){
			curNode = curNode->rightChild;
		}
		else
			curNode = curNode->leftChild;
	}
	if (curNodeParent->data != key){
		return nullptr;
	}
	return curNodeParent;
}

bool TransPlant(Tree_t * tree, Node_t * targetNode, Node_t * plantNode, Node_t * nillNode){
	if (tree == nullptr || targetNode == nullptr)
		return false;

	if (targetNode->parent == nillNode)
		tree->root = plantNode;
	else if (targetNode->parent->leftChild == targetNode)
		targetNode->parent->leftChild = plantNode;
	else
		targetNode->parent->rightChild = plantNode;

	if (plantNode != nillNode)
		plantNode->parent = targetNode->parent;

	return false;
}

Node_t * treeMinimum(Tree_t * tree, Node_t * targetNode, Node_t * nillNode){
	if (tree == nullptr || nillNode == nullptr)
		return false;

	Node_t * curNode = targetNode;
	Node_t * curNodeParent = nullptr;

	while (curNode != nillNode){
		curNodeParent = curNode;
		curNode = curNode->rightChild;
	}
	return curNodeParent;
}

Node_t * treeMaximum(Tree_t * tree, Node_t * targetNode, Node_t * nillNode){
	if (tree == nullptr || nillNode == nullptr)
		return false;

	Node_t * curNode = targetNode;
	Node_t * curNodeParent = nullptr;

	while (curNode != nillNode){
		curNodeParent = curNode;
		curNode = curNode->leftChild;
	}
	return curNodeParent;
}

bool DeleteFixup(Tree_t * tree, Node_t * fixupNode, Node_t * nillNode){
	if (tree == nullptr || fixupNode == nullptr)
		return false;

	Node_t * siblingNode = nullptr;

	while (fixupNode != tree->root && fixupNode->color == BLACK){
		if (fixupNode == fixupNode->parent->leftChild){
			siblingNode = fixupNode->parent->rightChild;
			if (siblingNode->color == RED){
				fixupNode->parent->color = RED;
				siblingNode->color = BLACK;
				LeftRotate(tree, fixupNode->parent, nillNode);
				siblingNode = fixupNode->parent->rightChild;
			}
			if (siblingNode->leftChild->color == BLACK && siblingNode->rightChild->color == BLACK){
				siblingNode->color = RED;
				fixupNode = fixupNode->parent;
			}
			else{
				if (siblingNode->rightChild->color == BLACK){
					siblingNode->leftChild->color = BLACK;
					siblingNode->color = RED;
					RightRotate(tree, siblingNode, nillNode);
					siblingNode = fixupNode->parent->rightChild;
				}
				siblingNode->color = fixupNode->parent->color;
				fixupNode->parent->color = BLACK;
				siblingNode->rightChild->color = BLACK;
				LeftRotate(tree, fixupNode->parent, nillNode);
				fixupNode = tree->root;//끝
			}
		}
		else{
			siblingNode = fixupNode->parent->leftChild;
			if (siblingNode->color == RED){
				fixupNode->parent->color = RED;
				siblingNode->color = BLACK;
				RightRotate(tree, fixupNode->parent, nillNode);
				siblingNode = fixupNode->parent->leftChild;
			}
			if (siblingNode->rightChild->color == BLACK && siblingNode->leftChild->color == BLACK){
				siblingNode->color = RED;
				fixupNode = fixupNode->parent;
			}
			else{
				if (siblingNode->leftChild->color == BLACK){
					siblingNode->rightChild->color = BLACK;
					siblingNode->color = RED;
					LeftRotate(tree, siblingNode, nillNode);
					siblingNode = fixupNode->parent->leftChild;
				}
				siblingNode->color = fixupNode->parent->color;
				fixupNode->parent->color = BLACK;
				siblingNode->leftChild->color = BLACK;
				RightRotate(tree, fixupNode->parent, nillNode);
				fixupNode = tree->root;//끝
			}
		}
	}
	fixupNode->color = BLACK;
	return true;
}

bool DeleteNode(Tree_t * tree, Node_t * targetNode, Node_t * nillNode){
	if (tree == nullptr || targetNode == nullptr)
		return false;

	Node_t * successor, * fixupNode;
	Color_t erasedColor = targetNode->color;

	if (targetNode->leftChild == nillNode){
		fixupNode = targetNode->rightChild;
		TransPlant(tree, targetNode, targetNode->rightChild, nillNode);
	}
	else if (targetNode->rightChild == nillNode){
		fixupNode = targetNode->leftChild;
		TransPlant(tree, targetNode, targetNode->leftChild, nillNode);
	}
	else{
		successor = treeMinimum(tree, targetNode->rightChild, nillNode);
		erasedColor = successor->color;
		fixupNode = successor->rightChild;

		//이것의 의미
		if (successor->parent == targetNode)
			fixupNode->parent = successor;

		if (successor != targetNode->rightChild){
			TransPlant(tree, successor, successor->rightChild, nillNode);
			successor->rightChild = targetNode->rightChild;
			successor->rightChild->parent = successor;
		}
		TransPlant(tree, targetNode, successor, nillNode);
		successor->leftChild = targetNode->leftChild;
		successor->leftChild->parent = successor;
		successor->color = targetNode->color;
	}

	if (erasedColor == BLACK)
		DeleteFixup(tree, fixupNode, nillNode);
	return true;
}

int CheckBlackHeight(Tree_t * tree, Node_t * node, Node_t * nillNode){
	if (tree == nullptr || node == nullptr) 
		return -1;

	if (node == nillNode)
		return 0;

	int left = CheckBlackHeight(tree, node->leftChild, nillNode);
	int right = CheckBlackHeight(tree, node->rightChild, nillNode);
		
	if (left == -1 || right == -1)
		return -1;

	if (node->leftChild == nillNode || node->leftChild->color == BLACK)
		++left;
	
	if (node->rightChild == nillNode || node->rightChild->color == BLACK)
		++right;
	
	if (left == right)
		return left;
	
	return -1;
}

void IsRedBlackTreeCorrect(Tree_t * tree, Node_t * node, Node_t * nillNode){
	int height = CheckBlackHeight(tree, tree->root, nillNode);

	if (height != -1)
		cout << "Red Black Tree Height = " << height << endl;
	else
		cout << "Black Height 가 다름" << endl;
}

int main(void){
	Tree_t * tree = new Tree_t;
	Node_t * nillNode = new Node_t;
	Node_t * searchNode = nullptr;
	NillNodeInit(nillNode);
	RedBlackTreeInit(tree, nillNode);

	InsertNewNode(tree, 11, nillNode);
	IsRedBlackTreeCorrect(tree, tree->root, nillNode);
	InsertNewNode(tree, 2, nillNode);
	IsRedBlackTreeCorrect(tree, tree->root, nillNode);
	InsertNewNode(tree, 14, nillNode);
	InsertNewNode(tree, 5, nillNode);
	InsertNewNode(tree, 9, nillNode);
	InsertNewNode(tree, 1, nillNode);

	IsRedBlackTreeCorrect(tree, tree->root, nillNode);

	searchNode = SearchNode(tree, 2, nillNode);
	DeleteNode(tree, searchNode, nillNode);
	searchNode = SearchNode(tree, 2, nillNode);

	searchNode = SearchNode(tree, 11, nillNode);
	DeleteNode(tree, searchNode, nillNode);
	searchNode = SearchNode(tree, 11, nillNode);

	searchNode = SearchNode(tree, 14, nillNode);
	DeleteNode(tree, searchNode, nillNode);
	searchNode = SearchNode(tree, 14, nillNode);
	
	searchNode = SearchNode(tree, 5, nillNode);
	DeleteNode(tree, searchNode, nillNode);
	searchNode = SearchNode(tree, 5, nillNode);
	
	searchNode = SearchNode(tree, 9, nillNode);
	DeleteNode(tree, searchNode, nillNode);
	searchNode = SearchNode(tree, 9, nillNode);

	searchNode = SearchNode(tree, 1, nillNode);
	DeleteNode(tree, searchNode, nillNode);
	searchNode = SearchNode(tree, 1, nillNode);

	IsRedBlackTreeCorrect(tree, tree->root, nillNode);

	delete tree;
	delete nillNode;
	getchar();
	return 0;
}