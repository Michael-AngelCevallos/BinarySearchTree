//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Your name
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Lab 5-2 Binary Search Tree
//============================================================================

#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations - MAKES A FUNCTION DECLARATION PROMISING THAT THIS FUNCTION WILL BE USED LATER ON IN THE CODE
// This Function will be used to CONVERT A STRING INTO A NUMBER(DOUBLE)
// JUST A DECLARATION FUNCTIONALITY HASNT BEEN SPECIFIED YET
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node {
    Bid bid;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Bid aBid) :
            Node() {
        bid = aBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree { // THE BST CLASS CONTAINS THE DATA MEMBERS AND METHODS TO IMPLEMENT A BINARY SEARCH TREE

private: // internal structure for tree node - PRIVATE MAKES IT SO THAT ONLY THE BST CLASS CAN USE THE NODE STRUCTURE - PRIVATE BECAUSE THESE NEVER CHANGE, USER SHOULD NOT CALL THESE
    Node* root; // CREATES/REPRESENTS/HOLDS THE STARTING POINT OF THE TREE/ THE ROOT OF THE TREE

    void addNode(Node* node, Bid bid); // INSERTS A NODE INTO PROPER LOCATION IN THE TREE - FINDS THE PROPER LOCATION IN THE TREE TO INSERT A NEW NODE
    void inOrder(Node* node); // RECURSIVE HELPER - DISPLAYS NODES IN SORTED ORDER - LEFT, ROOT, RIGHT
    void postOrder(Node* node); // RECURSIVE HELPER - DISPLAYS NODES IN POST-ORDER - LEFT, RIGHT, ROOT
    void preOrder(Node* node); // RECURSIVE HELPER - DISPLAYS NODES IN PRE-ORDER - ROOT, LEFT, RIGHT
    Node* removeNode(Node* node, string bidId); // RECURSIVE HELPER - REMOVES NODE FROM THE TREE - FINDS THE PROPER LOCATION IN THE TREE TO REMOVE A NODE

public:// METHODS THAT THE USER CAN CALL - OTHER CODE IS ALLOWED TO USE THESE METHODS
    BinarySearchTree(); // CONSTRUCTOR - CREATES EMPTY BST - INITILAZES ROOT TO NULLPTR
    virtual ~BinarySearchTree(); // DESTRUCTOR - OUTCOME: DELETE ALL NODES, FREE MEMORY, DESTROY TREE - RUNS AUTOMATICALLY WHEN BST TREE DIES
    void InOrder(); // PUBLIC WRAPPER- STARTS an inorder Traversal of the entire BST(Starts It!) - OUTCOME: Passes ROOT node to private method- CALLS: inOrder(root);
    void PostOrder(); // TRAVERSE TREE USING POSTORDER - CALLS: postOrder(root);
    void PreOrder(); // TRAVERSE TREE USING PREORDER - CALLS: preOrder(root);
    void Insert(Bid bid); // ADDS A NEW BID INTO THE BST - THIS IS WHAT HAPPENS WHEN LOADING BIDS FROM THE CSV FILE - CALLS: addNode(root, bid);
    void Remove(string bidId);// REMOVES BID WITH MATCHING bidID
    Bid Search(string bidId); // FINDS BID WITH MATCHING bidId, AND  RETURNS THAT BID OBJECT- EXAMPLE: Bid bid = bst.Search("98223");
};

/**
 * Default constructor - PURPOSE: INITIALIZES THE ROOT TO NULLPTR, CREATES AN EMPTY BST SO DATA CAN BE ADDED TO THE TREE LATER ON
 */
BinarySearchTree::BinarySearchTree() {
    //! FixMe (1): initialize housekeeping variables(COMPLETED)

    //root is equal to nullptr
    root = nullptr; // FIRST INTIALIZES THE ROOT TO NULLPTR, OR CREATES AN EMPTY BST, SO DATA CAN BE ADDED TO THE TREE LATER ON - AVOIDS UNDEFINED BEHAVIOR, PREVENTS CRASHES, AND ALLOWS US TO CHECK IF THE TREE IS EMPTY LATER ON IN THE CODE (IF ROOT IS NULLPTR THEN THE TREE IS EMPTY)
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    //! FixMe (2)
    // recurse from root deleting every node
}

/**
 * Start an InOrder traversal from the Root Node - PURPOSE: Starts  the Traversal method / Passes the Root of a node to the inOrder Method - CALLS: inOrder(root);
 */
void BinarySearchTree::InOrder() {
    // ! FixMe (3a): In order root
    // call inOrder function and pass root 
    inOrder(root); // Calls the private inOrder function and passes in (root) into the Public InOrder Function - This Makes sure thate the Public InOrder() When Called starts the Traversal method at the Root Node of the Tree - THIS IS THE STARTING POINT OF THE INORDER TRAVERSAL, THE INORDER FUNCTION WILL THEN RECURSIVELY CALL ITSELF TO TRAVERSE THE LEFT AND RIGHT SUBTREES OF THE ROOT NODE, AND EVENTUALLY DISPLAY ALL BIDS IN SORTED ORDER
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // ! FixMe (4a): Post order root
    // postOrder root
    postOrder(root); // Passes of a staring point theroughtthe rtroot of a node , to the postOrder function, which will then recursively call itself to traverse the left and right subtrees of the root node, and eventually display all bids in post-order (LEFT, RIGHT, ROOT)
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    //! FixMe (5a): Pre order root
    // preOrder root
    preOrder(root); // Passes the Root to the Private method of preOrder , makes sure it starts at the root
}



/**
 * Insert a bid- Checks if Root Node  Being Passed is Empty, If So 
 */
void BinarySearchTree::Insert(Bid bid) {
    // FIXME (6a) Implement inserting a bid into the tree

    // if root equal to null ptr- if root is empty 
    if (root == nullptr){
        
        // root is equal to new node bid
        root = new Node(bid);

    }
    // else
    else{
        // add Node root and bid
        addNode(root, bid);

    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // FIXME (7a) Implement removing a bid from the tree
    // remove node root bidID
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // ! FIXME (8) Implement searching the tree for a bid

    // set current node equal to root
    Node* current = root;
    
    // create empty bid to return if not found
    Bid bid;

    // keep looping downwards until bottom reached or matching bidId found
    while(current != nullptr){

        // if match found, return current bid
        if (current->bid.bidId == bidId){

            return current->bid;

        }

        // if bid is smaller than current node then traverse left
        if (bidId < current->bid.bidId){

            current = current->left;
        }
        // else larger so traverse right
        else{
            current = current->right;
        }
    }
    // bid not found
    return bid;
}



/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    //! FIXME (6b) Implement inserting a bid into the tree

    // if node is larger then add to left
    if (bid.bidId < node->bid.bidId){
        
        // if no left node
        if (node->left == nullptr){

            // this node becomes left
            node->left = new Node(bid);
        }
        // else recurse down the left node
        else{
            addNode(node->left, bid);
        }   
    }
        // else
        else{
            // if no right node
            if (node->right == nullptr){
                // this node becomes right
                node->right = new Node(bid);

            }
            //else
            else{
                // recurse down the right node
                addNode(node->right, bid);
            }  
    }
}


void BinarySearchTree::inOrder(Node* node) {
      // ! FixMe (3b): In order root - Display in order of: Left, Root, Right
      //if node is not equal to null ptr- Before Doing anything Make Sure Node Actualy Exists
if (node != nullptr){ 

    //InOrder not left- Go to the Left Child First
    inOrder(node->left);

    //output bidID, title, amount, fund - Process the Current Node -- This Is where We Display The Bids
    cout << node->bid.bidId << ": "
            << node->bid.title << " | "
            << node->bid.amount << " | "
            << node->bid.fund << endl;


    //InOrder right - Now Go to the Right Child
    inOrder(node->right);
    }
}



void BinarySearchTree::postOrder(Node* node) {
      // ! FixMe (4b): Post order root - Display order : Left, Right, Root
      //if node is not equal to null ptr
      if (node != nullptr){
          //postOrder left
          postOrder(node->left);
          
          //postOrder right
          postOrder(node->right);

          //output bidID, title, amount, fund
            cout << node->bid.bidId << ": "
                << node->bid.title << " | "
                << node->bid.amount << " | "
                << node->bid.fund << endl;
      }

}

void BinarySearchTree::preOrder(Node* node) {
      //! FixMe (5b): Pre order root - Order: Current , Left , Right

      //if node is not equal to null ptr
      if (node != nullptr){

          //output bidID, title, amount, fund
            cout << node->bid.bidId << ": "
                << node->bid.title << " | "
                << node->bid.amount << " | "
                << node->bid.fund << endl;
         //preOrder left
          preOrder(node->left);
          
        //preOrder right   
        preOrder(node->right);   

      }
}

/**
 * Remove a bid from some node (recursive)
 */
Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    // ! FIXME (7b) Implement removing a bid from the tree
    // if node = nullptr return node
    // (otherwise recurse down the left subtree)
    // check for match and if so, remove left node using recursive call 
    // (otherwise recurse down the right subtree)
    // check for match and if so, remove right node using recursive call
    // (otherwise no children so node is a leaf node)
    // if left node = nullptr && right node = nullptr delete node 
    // (otherwise check one child to the left)
    // if left node != nullptr && right node = nullptr delete node 
    // (otherwise check one child to the right)
    // if left node = nullptr && right node != nullptr delete node
    // (otherwise more than one child so find the minimum)
    // create temp node to right
    // while left node is not nullptr keep moving temp left
    // make node bid (right) equal to temp bid (left)
    // remove right node using recursive call
    // return node
}



//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98223";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales.csv";
        bidKey = "98223";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
