//----------------------------------
// Assignment : Project 2
// Author : Savion Peebles
// Date : 8/13/2023
// Professor Susalla
// Course: CS-300
//-----------------------------------


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

//This portion displays the menu
void showMenu() {
	cout << "1. Load selected data structure" << endl;
	cout << "2. Print the course list" << endl;
	cout << "3. Print the selected course" << endl;
	cout << "9. Exit the program" << endl;
	cout << "What choice would you like to make?";
}

// defines the structure used to store the course info
struct Course {
	string courseID;
	string courseTitle;
	vector<string> preReq;
};

// defines the structure for the tree nodes
struct Node {
	Course course;
	Node* left;
	Node* right;

	Node() { // constructor
		left = nullptr;
		right = nullptr;

	}
// This portion is used to intialize with an example course
	Node(Course eCourse) : Node() {
		this->course = eCourse;
	}
};

// defines the class with the needed data values in order to implement BST
Class BinarySearchTree{

private:

	void Destruct(Node* node);

public:
	Node* root;
	BinarySearchTree();
	virtual BinarySearchTree();
	void Insert(BinarySearchTree* tree, Node* node);
	void search(string courseID);
	void printCourse(Node* node);
};

// default constructor for Binary Search Tree
BinarySearchTree::BinarySearchTree() {
	root = nullptr;
};

// destructor for Binary Search Tree
BinarySearchTree::~BinarySearchTree() {
	Destruct(root);
};

// This will take the right and left pointer and delete them after destruct
void BinarySearchTree::Destruct(Node* node) {
	if (node != nullptr) {
		Destruct(node->left);
		node->left = nullptr;
		Destruct(node->right);
		node->right = nullptr;
		delete node;
	}
};

// This will allow the search for a desired course
void BinarySearchTree::Search(string courseID) {
	Node* currNode = root;

	while (currNode != nullptr) {
		if (currNode->course.courseID == courseID) {
			//this will print the course id and the name of the class
			cout << currNode->course.courseID << " , ";
			cout << currNode->course.courseTitle;
			cout << endl;
			cout << "The prerequsites are: ";
			// This will print all prereqs needed
			for (string preReq : currNode->course.preReq) {
				if (preReq == currNode->course.preReq.back()) {

					cout << preReq << endl;
				}
				else {
					cout << preReq << " , "

				}
			}

			return;
		}

		//this will search for the left pointer if not found
		else if (courseID < currNode->course.courseID) {

			if (currnode->left != nullptr) {
				currnode = currnode->left;
			}

		}
		// This will search for the right pointer if is not found
		else {
			currNode = currNode->right;
		}

	}

	//if the course is not found in the list
	cout << "Course" << courseID << "Not Available. " << endl;
	return;
}

//this will insert the course into a list
void BinarySearchTree::Insert(BinarySearchTree* tree, Node* node) {

	if (tree->root == nullptr) {
		tree->root = node;
	}
	else {
		Node* curr = tree->root;
		while (curr != nullptr) {

			if (node->course.courseID < curr->course.courseID) {
				if (curr->left == nullptr) {
					curr->left = node;
					curr = nullptr;
				}
				else {
					curr = curr->left;

				}
			}
			else {
				if (curr->right == nullptr) {
					curr->right = node;
					curr = nullptr;
				}
				else {
					curr = curr->right;
				}
			}

		}

	}

}
// This will print our course list
void BinarySearchTree::printCourse(Node* node) {
	//prints tree
	if (node == nullptr) {
		return;
	}

	//takes left node, then print courseID and the coruse title then move to next node
	printCourses(node->left);
	cout << node->course.courseID << " , ";
	cout << node->course.courseTitle << endl;
	printCourse(node->right);
};

// takes the course list and then loads the file
void loCourse(string filename, BinarySearchTree* bst) {
	ifstream file(filename);
	if (file.is_open()) {
		cout << "The file has been loaded." << endl;

		int numb;
		string line;
		string word;

		while (getline(file, line)) {
			numb = 0;
			Node* node = new Node();
			stringstream str(line);

			while (numb < 2) {
				getline(str, word, ',');
				if (numb == 0) {
					node->course.courseID = word;
				}
				else {
					node->course.courseTitle = word;
				}
				numb++;
			}
			while (getline(str, word, ',')) {
				node->course.preReq.push_back(word);
			}

			//this will insert our node into the Binary Search Tree
			bst->Insert(bst, node)
		}

	}
	//Provides an error if the file cannot be found
	else {
		cout << "There has been a file error, please try again." << endl;
		return;
	}

}

void main() {
	BinarySearchTree* bst = new BinarySearchTree();

	string filesChoice;
	string courseChoice;

	int userChoice = 0;

	// This will show our menu and how it is implemented
	cout << "Hello, Welcome to the course schedule planner." << endl << endl;

	while (userChoice != 9) {
		showMenu();
		cin >> userChoice;

		switch (userChoice) {
			//this will load the file that the user has chosen
		case 1:
			cout << endl;
			cout << "What file would you like to open? The defuault file for this program is Courses.csv";
			cin >> userChoice;

			loCourse(filesChoice, bst);
			cout << endl;
			break;

		// this will output our courses in alphanumeric form
		case 2:
			cout << endl;
			cout << "Course ID |       Course Title" << endl;

			//this will print the courses at the root
			bst->printCourse(bst->root);
			cout << endl;
			break;

			//this will print the courses that the user has chosen and Prereqs
		case 3:
			cout << endl;
			cout << "What course would you like to choose?";
			cin >> courseChoice;
			cout << endl;

			std::transform(courseChoice.begin(), courseChoice.end(), courseChoice.begin(), ::toupper);
			bst->Search(courseChoice);
			
			cout << endl;
			break;

		//This will exit the program
		case 9:
			cout << "Thank you so much for using our planner. Enjoy your day!" << endl;
			break;

		//Message if an option above is not chosen
		default:
			cout << userChoice << "This is not a valid option." << endl << endl;
			break;
			
		}
	}
}