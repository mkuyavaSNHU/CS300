//============================================================================
// Name        : ProjectTwoABCU.cpp
// Author      : Marisa Kuyava
// Version     : 1.0
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Structure to hold Course information
struct Course {
    string CourseId{ NULL };
    string CourseName{ NULL };
    string PreReq1{ NULL };
    string PreReq2{ NULL };

};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

////============================================================================
//// Binary Search Tree class definition
////============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;
    void addNode(Node* node, Course course);
    void inOrder(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Course course);
    Course Search(string courseId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    root = nullptr; //root is equal to nullptr
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {

    this->inOrder(root); //call inOrder fuction and pass root
}


void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {//if node is not equal to null ptr

        inOrder(node->left); //recursive call to inOrder on left

        if(node->course.CourseId != ""){ //Eleminates printing empty node
            cout << "Course ID: " << node->course.CourseId << endl; //Output course ID
            cout << "Course Name: " << node->course.CourseName << endl;  //Output course name
            cout << endl;
        }

        inOrder(node->right); //recursive call to inOrder on right
    }

}

// Inserts a course into the tree
void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) { //if root is null 
        root = new Node(course); // make new node the root
    }
    else {
        this->addNode(root, course); //call add node
    }
}

// Adds a course to the tree
void BinarySearchTree::addNode(Node* node, Course course) {
    if (node->course.CourseId.compare(course.CourseId) > 0) { //if  node.courseId is larger than course.courseId : The bid is added to the leftside of the BinarySearchTree
        if (node->left == nullptr) { // if the left node is null
            node->left = new Node(course); //the new node is created to the left
        }
        else { //else
            this->addNode(node->left, course); //recursive call
        }
    }
    else {
        if (node->right == nullptr) {// if the right node is null
            node->right = new Node(course); //the new node is created to the left
        }
        else {
            this->addNode(node->right, course); //recursive call
        }
    }
}

/**
 * Search for a bid
 */
Course BinarySearchTree::Search(string courseId) {

    Node* current = root; // set current node equal to root

    while (current != nullptr) { //while current node is not null
        // keep looping downwards until bottom reached or matching bidId found
        if (current->course.CourseId.compare(courseId) == 0) { // If current bid matches bidId
            return current->course; //return current bid
        }
        else if (courseId.compare(current->course.CourseId) < 0) { //else if bid is smaller than current bid 
            current = current->left; //traverse the left side of the tree
        }
        else if (courseId.compare(current->course.CourseId) > 0) {//else (if bid is greater than current bid)
            current = current->right;//traverse the right side of the tree
        }
        else {
            cout << "No match found";
        }
    }
    
    return current->course; // return course
}





Course lineParser(vector<string> line) {
    
    for (int i{0}; i < line.size(); i++) { //traverses string vector passed to function
        string tempString = line[i]; //stores vector element as string
        string delimiter = ","; //used to split string at comma delimiter 
        size_t pos {0}; //tracks position of delimiter
        string token; //temp storage
        vector<string> tokens; //vector of strings to store after split

        while ((pos = tempString.find(delimiter)) != string::npos) { //traverses string
            token = tempString.substr(0, pos); //splits and stores first word from string before delimiter
            tokens.push_back(token); //pushes word to vector 
            tempString.erase(0, pos + delimiter.length()); //removes portion of string that was stored
        }
        tokens.push_back(tempString);//pushes last word to vector
        
        for (int j = 0; j < tokens.size(); j++) { //Used to eliminate any empty elements in the vector created from CSV file
            if (tokens[j] == "") { //if element is empty
                tokens.pop_back(); //remove from vector
            }
        }
        
        if (tokens.size() == 2) { //If the vector has two elements 
            Course course; //create course
            course.CourseId = tokens[0]; //assign course id
            course.CourseName = tokens[1]; //assign course id
            return course; //return course
        }
        else if (tokens.size() == 3) { //If the vector has three elements 
            Course course;//create course
            course.CourseId = tokens[0];//assign course id
            course.CourseName = tokens[1];//assign course id
            course.PreReq1 = tokens[2]; //assign prereq 1 
            return course;//return course
        }
        else if (tokens.size() == 4) {
            Course course;//create course
            course.CourseId = tokens[0];//assign course id
            course.CourseName = tokens[1];//assign course id
            course.PreReq1 = tokens[2]; //assign prereq 1 
            course.PreReq2 = tokens[3];//assign prereq 2 
            return course;//return course
        }  
    }
}




    // Loads and stores a CSV file
    void loadFile(string file, BinarySearchTree * bst) {
        
        cout << endl;
        cout << "Loading CSV file... " << endl;
        cout << ". " << endl;

        vector<string> eachLine; //Create vector of strings to hold file data
        ifstream myfile(file); //Open file with Ifstream
        string str; //String variable to hold each line


        while (myfile.good()) { 
            getline(myfile, str); //gets line from file and stores in string variables
            eachLine.push_back(str); //pushes string variables to string vector
            Course newCourse =lineParser(eachLine); //creates new course and parses vector for correct format
            bst->Insert(newCourse); //inserts new course to tree
            eachLine.clear(); //clears vector
         }
        cout << ". " << endl;
        cout << ". " << endl;
        cout << "File has been loaded" << endl;
        cout << endl;
    }

    //Print formating for Course Printing
    void PrintCourse(Course course) {
        cout << "###############################" << endl;
        cout << "Course Id: " << course.CourseId << endl;;
        cout << " Course Name: " << course.CourseName << endl;
        cout << "   Prerequisite 1: " << course.PreReq1 << endl;;
        cout << "   Prerequisite 2: " << course.PreReq2 << endl;;
        cout << "###############################" << endl;
    }

    //Print formating function for menu
    void menuPrint() {
        cout << "###############################" << endl;
        cout << endl;
        cout << "Welcome to the course planner:" << endl;
        cout << endl;
        cout << "  1. Load Data Structure" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  9. Exit" << endl;
        cout << endl;
        cout << "###############################" << endl;
        cout << endl;
        cout << "What would you like to do? " ;
        cout << endl;
    }

    //clear input - used for input validation
    void clearCin() {
        system("CLS"); //clear screen
        cin.clear(); //clear input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear input
        cout << "###############################" << endl;
    }
       



/**
 *  main() method
 */
int main(int argc, char* argv[]) {


    // Define a binary search tree to hold all courses
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;
    string tempID;

    int choice{ 0 }; // variable for menu selection
    while (choice != 9) { 
        menuPrint(); //prints menu options
        cin >> choice; //captures input


            if(choice != 1 && choice != 2 && choice != 3 && choice != 9) { // if input is not one of the menu options
                if (!cin.good()) { //if cin is not an integer
                    clearCin();
                    cout << endl;
                    cout << "That is not a valid selection." << endl;
                    cout << endl;
                    cout << "Please pick a menu option: 1, 2, 3 or 9." << endl;
                    cout << endl;
                }
                else { //if cin is an integer but not a valid menu selection
                    clearCin();
                    cout << endl;
                    cout << "That is not a valid selection. Please try again." << endl;
                    cout << endl;
                }
            }

        switch (choice) {

        case 1:
            
            loadFile("ABCU.csv", bst);
            break;

        case 2:
            cout << "###############################" << endl;
            cout << "Course List" << endl; 
            cout << "###############################" << endl;
            cout << endl;
            bst->InOrder(); //prints  an alphanumeric list of all the courses in the Computer Science department 
            break;

        case 3:
            cout << endl;
            cout << "Please enter the Course Id you would like to view: " << endl;
            cout << endl;
            cout << "*******ENTER ALL LETTERS AS CAPITALS*******" << endl;
            cout << endl;
            cin >> tempID;
            cout << endl;
            cout << "###############################" << endl;
            cout << endl;
            course = bst->Search(tempID); //searches tree and stores resuls in course
            PrintCourse(course); //print formatting function
            break;

        case 9:

            break;
        }
    }

    cout << "Thank you for using the Course Planner! Good bye!" << endl;

    return 0;
}