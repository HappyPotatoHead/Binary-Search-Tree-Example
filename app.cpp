#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include    "Student.h"
#include	<iomanip>		//For Fixed UI Purpose

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
void exit();

int main() {
	BST* t1 = new BST(), * t2;
	type item;
	int order = 0, source = 0;
	char file[30];
	bool terminate = 0;

	do {
		system("cls");
		switch (menu()) {
		case 1:
			strcpy(file, fileSelector().c_str());
			if (strcmp(file, "0") != 0) {
				if (readFile(file, t1))
					cout << "\nRead File Success! ";
				else cout << "\nFailed To Read File! ";
			}
			else cout << "\nOperation Canceled! ";
			break;
		case 2:
			if (t1->deepestNodes())
				cout << "Print Deepest Nodes Success! ";
			else
				cout << "Tree is empty! Please Read Data to BST first! ";
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
			t2 = new BST();
			do {
				cout << "***Enter 0 to see cloneable IDs***\nClone Subtree of ID : ";
				cin >> item.id;
				if (item.id == 0) {
					system("cls");
					cout << "Available,\n";
					t1->inOrderPrint();
				}

			} while (item.id <= 0);
			system("cls");
			if (t2->CloneSubtree(*t1, item)) {
				cout << "\n============================= Tree 1 =============================\n";
				t1->preOrderPrint();
				cout << "============================= Tree 1 =============================\n\n";
				cout << "\n======================= Tree 2 (Root: "
					<< std::setw(3) << item.id << ") =======================\n";
				t2->preOrderPrint();
				cout << "============================= Tree 2 =============================\n\n";
			}
			break;
		case 5:
			if (t1->printLevelNodes())
				cout << "\n\nPrint Level Nodes Success! ";
			else
				cout << "Failed to Print Level Nodes! Please Read Data to BST first!\n\n";
			break;
		case 6:
			if (t1->printPath())
				cout << "\nPrint External Path Success. ";
			else
				cout << "Failed to Print Level Nodes! Please Read Data to BST first!\n\n";
			break;
		case 7:
			terminate = 1;
			exit();
			break;
		default:
			cout << "\nInvalid Option! ";
		}
		system("pause");
	} while (!terminate);
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
		in.get();
		if (!redundantCheck(t1, temp))
			t1->insert(*temp);
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
	****STUDENT INFORMATION SYSTEM****
	*                                *
	*   (1)  Read data to BST        *
	*   (2)  Print deepest nodes     *
	*   (3)  Display student         *
	*   (4)  Clone Subtree           *
	*   (5)  Print Level Nodes       *
	*   (6)  Print Path              *
	*   (7)  Exit                    *
	*                                *
	**********************************
	CHOOSE
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


//OWN FUNCTION//
void skipword(ifstream& in, int skip) {
	for (int i = 0; i < skip; i++)
		in >> g_dump;
}

string fileSelector() {
	system("cls");
	char select[30];
	cout << "Please select or enter file name ended with (.txt)";
	cout << "\n1. student.txt\n0. Cancel\n\n >> ";
	cin >> select;
	if (strcmp(select, "1") == 0)
		return "student.txt";
	else
		return select;
}

void exit() {
	system("cls");
	cin.ignore();
	cout << R"(
             ////Session Ended////


     _____ _           _      __ __         
    |_   _| |_ ___ ___| |_   |  |  |___ _ _ 
      | | |   | .'|   | '_|  |_   _| . | | |
      |_| |_|_|__,|_|_|_,_|    |_| |___|___|

    _______________________________________
    | |              Made By              |
    ---------------------------------------
    |1| Jimmy Ding Jia Kang   |  2203252  |
    |2| Yee Jia Hao           |  2301823  |
    ---------------------------------------
    )";
}