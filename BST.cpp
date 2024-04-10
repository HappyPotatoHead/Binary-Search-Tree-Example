#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"

#include <string>

// more memory efficient 
// #include <vector>


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode* cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode* cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode* cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode* cur, int& count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode* cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)) {

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode* cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode* cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode* cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode* cur, BTNode* newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)) {
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode* pre, BTNode* cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)) {
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode* pre, BTNode* cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode* cur) {
	BTNode* is, * isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}

// Question B
bool BST::deepestNodes() {
	if (empty()) return 0;
	deepestNodes2(root);
	return 1;
}

void BST::deepestNodes2(BTNode* root) {
	if (!root) return;

	if (!root->left && !root->right)
		std::cout << root->item.id << '\n';
	else {
		deepestNodes2(root->left);
		deepestNodes2(root->right);
	}
}

// Question C
bool BST::display(int order, int source) {
	system("cls");

	if (root == NULL) return 0;					// handle special case
	BTNode* cur = root;
	if ((order == 1 || order == 2) && (source == 1 || source == 2)) {	//Can remove if not needed 
		if (order == 1) {
			if (source == 1)
				display2asc(cur, cout);
			else {
				ofstream out("student-info.txt");
				if (!out.fail())
					display2asc(cur, out);	//For output txt file
				else {
					cout << R"(Unable to output into "student-info.txt" file")";
					return 0;
				}
				out.close();
			}
		}
		else {
			if (source == 1)
				display2desc(cur, cout);
			else {
				ofstream out("student-info.txt");
				if (!out.fail())
					display2desc(cur, out);	//For output txt file
				else {
					cout << R"(Unable to output into "student-info.txt" file")";
					return 0;
				}
				out.close();
			}
		}
		cout << "\nOutput Successful. ";
		system("PAUSE");
		return 1;
	}
	cout << "Invalid order/source selection\n\n";
	system("PAUSE");
	return 0;
}

void BST::display2asc(BTNode* cur, ostream& out) {
	//Base
	if (cur == NULL) return;

	//Recur
	display2asc(cur->left, out);
	cur->item.print(out);
	display2asc(cur->right, out);
}

void BST::display2desc(BTNode* cur, ostream& out) {
	//Base
	if (cur == NULL) return;

	//Recur
	display2desc(cur->right, out);
	cur->item.print(out);
	display2desc(cur->left, out);
}

// Question D
bool BST::CloneSubtree(BST t1, type item) {
	// t2 must be empty before cloning
	if (t1.empty()) return 0;

	BTNode* temp{ nullptr };

	// item pased in will be the root
	if (checkExist(t1.root, temp, item)) {
		root = CloneSubtree2(temp);
	}
	//preOrderPrint();
	return 1;
}

BTNode* BST::CloneSubtree2(BTNode* root) {
	if (!root) return nullptr;
	BTNode* copy{ new BTNode(root->item) };
	copy->left = CloneSubtree2(root->left);
	copy->right = CloneSubtree2(root->right);
	count++;
	return copy;
}

// Question F
// not as efficient as vector
void BST::printPath2(BTNode* root, type path[], int pathLength) {
	if (!root) return;
	path[pathLength] = root->item;
	pathLength++;
	if (!root->left && !root->right) {
		for (int index{ 0 }; index < pathLength; index++) {
			cout << path[index].id << " ";
		}
		cout << '\n';
	}
	else {
		printPath2(root->left, path, pathLength);
		printPath2(root->right, path, pathLength);
	}
}

bool BST::printPath() {
	if (empty()) return 0;
	type path[250];
	int pathLength{};
	printPath2(root, path, pathLength);
	return 1;
}

// Alternative
/*
void BST::efficientway(BTNode*root, vector<type> path){
	if(!root) return;
	path.push_back(root->item);
	if(!root->left && !root->right){
		string temp;
		for (int index{0}; index < path.size(); index++){
			cout << path[index];
		}
		if(index < path.size() -1)
			cout << " ";
		cout << '\n';
	}
	else{
		efficientway(root->left, path);
		efficientway(root->right, path);
	}
}*/


// Custom
bool BST::checkExist(BTNode* root, BTNode*& node, type& item) {
	if (!root) return 0;
	if (root->item.id == item.id) {
		node = root;
		return 1;
	}
	if (root->item.id > item.id)
		return checkExist(root->left, node, item);
	else
		return checkExist(root->right, node, item);
}



