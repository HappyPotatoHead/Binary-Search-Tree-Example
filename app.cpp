#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include    "Student.h"

using namespace std;

char g_dump[100];

// Mandatory Tasks
bool readFile(const char*, BST*);
int menu();

// custom function
bool redundantCheck(BST*, type*);
bool redundantCheck2(BTNode*, type*);

void skipword(ifstream&, int);

int main() {
	int order = 0, source = 0;
	BST* t1 = new BST();
	switch (menu()) {
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	default: 
		cout << "\nInvalid Option!";
	}

	////a
	//readFile("student.txt", t1);		//Error Message not added
	////b
	////c
	//cout << "Print in 1.asc or 2.desc         : ";
	//cin >> order;
	//cout << "Enter a cout option 1.Cout 2.txt : ";
	//cin >> source;
	//t1->display(order, source);
	////d
	////e
	//if(t1->printLevelNodes());
	////f
	////g
	////h
	//////
	cout << endl;
	system("pause");
	return 0;
}

//QUESTION a
bool readFile(const char* filename, BST* t1) {
	type* temp = new type;

	ifstream in;
	in.open("student.txt");

	if (in.fail()) {
		cout << "Failed to open file" << endl;
	}
	while (in) {
		skipword(in, 3);
		in >> temp->id;
		if (!redundantCheck(t1, temp)) {
			skipword(in, 2);
			in.getline(temp->name, 30);
			skipword(in, 2);
			in.getline(temp->address, 100);
			skipword(in, 2);
			in.getline(temp->DOB, 20);
			skipword(in, 3);
			in.getline(temp->phone_no, 10);
			skipword(in, 2);
			in.getline(temp->course, 5);
			skipword(in, 2);
			in >> temp->cgpa;
			t1->insert(*temp);
			in.get();
		}
	}
	in.close();
	return 1;
}

//Redundancy Check //USED in a
bool redundantCheck(BST* tree, type* temp) {
	if (tree->empty()) return 0;

	BTNode* cur = tree->root;
	return redundantCheck2(cur, temp);
}

//Redundancy Check - Recursive
bool redundantCheck2(BTNode* cur, type* temp) {
	//Base
	if (cur == NULL) return 0;					//No Redundant ID
	if (cur->item.compare2(*temp)) return 1;	//Found Redundant ID


	//Recursion
	if (cur->item.compare1(*temp))
		return redundantCheck2(cur->left, temp);
	return redundantCheck2(cur->right, temp);

}

//QUESTION h 
int menu() {
	int choice{};
	do {
		cout << R"(
**********STUDENT INFORMATION SYSTEM**********
	(1)	Read data to BST
	(2)	Print deepest nodes
	(3)	Display student
	(4)	Clone Subtree
	(5)	Print Level Nodes
	(6)	Print Path
	(7)	Exit

	>> )";
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "Please input only integers!\n";
		}
	} while (cin.fail());
	return choice;
}

//OWN FUNCTION
void skipword(ifstream& in, int skip) {
	for (int i = 0; i < skip; i++)
		in >> g_dump;
}
