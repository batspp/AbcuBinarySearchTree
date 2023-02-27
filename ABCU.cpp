// ABCU.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Joshua Battaglia
// 19FEB2023

#include <time.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Define a structure to hold course information.
struct Course {
    string courseId; // Unique identifier.
    string title;
    string prereqs;
    Course() {
        prereqs = "none";
    }
};

// Internal structure for tree node.
struct Node {
    Course course;
    Node* left;
    Node* right;

    // Default constructor.
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // Initialize with a course.
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

/*
 * Binary Tree class definition
 */
class BinaryTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);

public:
    BinaryTree();
    void Insert(Course course);
    virtual ~BinaryTree();
    void InOrder();
    Course Search(string courseId);
};

/*
 * Default constructor
 */   
BinaryTree::BinaryTree() {
    // Root is equal to nullptr.
    root = nullptr;
}

/*
 * Destructor
 */
BinaryTree::~BinaryTree() {
    // Delete recursively from root.
}

/*
 * Traverse the tree in order.
 */
void BinaryTree::InOrder() {
    // Call inOrder() and pass root.
    inOrder(root);
}

/*
 * Insert course.
 */
void BinaryTree::Insert(Course course) {

    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        addNode(root, course);
    }
}

/*
 * Search for a course.
 */
Course BinaryTree::Search(string courseId) {
    // Set current node equal to root.
    Node* cur = root;

    // Keep looping down until bottom reached or matching courseId.
    while (cur != nullptr) {
        if (cur->course.courseId.compare(courseId) == 0) {
            return cur->course;
        }
        else if (courseId.compare(cur->course.courseId) < 0) {
            cur = cur->left;
        }
        else {
            cur = cur->right;
        }
    }
    Course course;
    return course;
}

/*
 * Add a course to some node
 *
 * @param node is current node in tree
 * @param Course course to be added.
 */
void BinaryTree::addNode(Node* node, Course course) {
    // If node is larger add to left.
    if (node->course.courseId.compare(course.courseId) > 0) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        // else recurse down the left node.
        else {
            addNode(node->left, course);
        }
    }
    else {
        // If no right node.
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            addNode(node->right, course);
        }
    }
}

/*
 * Print tree in order
 */
void BinaryTree::inOrder(Node* node) {
    // If node is not equal to nullptr.
    if (node != nullptr) {
        inOrder(node->left);

        // Print courseId, title, prereqs.
        cout << node->course.courseId << ", " << node->course.title << endl;

        inOrder(node->right);
    }
}

void loadFile(BinaryTree* bst, string file) {
    string line;
    ifstream courseFile(file);
    if (courseFile.is_open()) {
        while (getline(courseFile, line)) {
            // Load file data into data structure.

        }
        courseFile.close();
    }
    else {
        cout << "File not found." << endl;
    }
}

int main()
{
    // Define binary tree to hold courses.
    BinaryTree* bst;
    bst = new BinaryTree();
    Course course;
    string courseId;

    int choice = 0;   // Loop variable.
    string file;

    while (choice != 9) {
        // Welcome screen and menu.
        std::cout << "Welcome to the course planner.\n" << endl;
        std::cout << "1. Load Data Structure.\n2. Print Course List.\n3Print Course.\n9. Exit." << endl << endl;
        std::cout << "What would you like to do? ";

        cin >> choice;

        switch (choice) {

            // Prompt file name.
        case 1:
            std::cout << "Enter file name with file extention." << endl;

            cin >> file;

            loadFile(bst, file);

            // Print tree in order.
        case 2:
            bst->InOrder();
            break;

            // Print course information.
        case 3:
            std::cout << "what course do you want to know about?";
            cin >> courseId;

            bst->InOrder();
            break;

            // Exit.
        default:
            std::cout << "Thank you for using the course planner!" << endl;
            break;
        }
    }
}
