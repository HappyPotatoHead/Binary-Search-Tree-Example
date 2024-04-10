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

string fileSelector();
void skipword(ifstream&, int);

int main() {
	int order = 0, source = 0;
	BST* t1 = new BST();
	bool terminate = 0;
	do {
		system("cls");
		switch (menu()) {
		case 1:
			if (readFile(fileSelector().c_str(), t1))
				cout << "\nRead File Success! ";
			else cout << "\nFailed To Read File! ";
			break;
		case 2:
			if (!t1->deepestNodes())
				cout << "Tree is empty! Please Read Data to BST first!\n\n";
			break;
		case 3:
			cout << R"(
	Print Order?
	1. Ascending
	2. Descending

	>> )";
			cin >> order;
			cout << R"(
	Output as?
	1. Terminal
	2. "student-info.txt" file

	>> )";
			cin >> source;
			if (!t1->display(order, source))
				cout << "Tree is empty! Please Read Data to BST first!\n\n";
			break;
		case 4:

			break;
		case 5:
			if (t1->printLevelNodes())
				cout << "Print Level Nodes success! ";
			else
				cout << "Failed to Print Level Nodes! Please Read Data to BST first!\n\n";
			break;
		case 6:

			break;
		case 7: 
			terminate = 1;
			cout << "Program Terminated. ";
			break;
		default: 
			cout << "\nInvalid Option!";
		}
		system("pause");
	} while (!terminate);

	////a
	//readFile("student.txt", t1);		//Error Message not added
	////b
	////c
	//cout << "Print in 1.asc or 2.desc         : ";
	//cin >> order;
	//cout << "Enter a cout option 1.Cout 2.txt : ";
	//cin >> source;
	//t1->display(order, source);
	//if(t1->printLevelNodes());
	//////
	//cout << endl;
	//system("pause");
	//return 0;
}

//a
bool readFile(const char* filename, BST* t1) {
	type* temp = new type;

	ifstream in;
	in.open(filename);

	if (in.fail()) return 0;
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
	system("cls");
	return choice;
}

//OWN FUNCTION
void skipword(ifstream& in, int skip) {
	for (int i = 0; i < skip; i++)
		in >> g_dump;
}

string fileSelector() {
	system("cls");
	char select[30];
	cout << "\nPlease select or enter file name ended with (.txt)";
	cout << "\n1. student.txt\n\n>> ";
	cin >> select;
	if (strcmp(select, "1") == 0)
			return "student.txt";
	else
		return select;
}