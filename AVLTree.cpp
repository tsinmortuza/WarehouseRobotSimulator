#include "AVLTree.h"

#include <bits/stdc++.h>
using namespace std;

// NODE CONSTRUCTOR
AVLTree::Node::Node(int id,int x,int y) {

    this->id = id;
    this->x = x;
    this->y = y;

    height = 1;
    left = nullptr;
    right = nullptr;
}

// AVL TREE CONSTRUCTOR
AVLTree::AVLTree() {
    root = nullptr;
}

// HEIGHT
int AVLTree::height(Node* node) {
    if (node == nullptr)        return 0;
    return node->height;
}

// BALANCE FACTOR
int AVLTree::getBalance(Node* node) {
    if (node == nullptr)        return 0;
    return height(node->left) - height(node->right);
}

// RIGHT ROTATION
AVLTree::Node* AVLTree::rightRotate(Node* y) {

    Node* x = y->left;
    Node* T = x->right;
    x->right = y;
    y->left = T;
    y->height = 1 + max(height(y->left),height(y->right));
    x->height = 1 + max(height(x->left),height(x->right));

    return x;
}

// LEFT ROTATION
AVLTree::Node* AVLTree::leftRotate(Node* x) {

    Node* y = x->right;
    Node* T = y->left;
    y->left = x;
    x->right = T;
    x->height = 1 + max(height(x->left),height(x->right));
    y->height = 1 + max(height(y->left),height(y->right));

    return y;
}


// INSERT
AVLTree::Node* AVLTree::insertNode(
    Node* node,
    int id,int x,int y
) {
    if (node == nullptr)        return new Node(id,x,y);

    if (id < node->id) {
        node->left = insertNode(node->left,id,x,y);
    }
    else if (id > node->id) {
        node->right = insertNode(node->right,id,x,y);
    }
    else {
        cout << "Item ID already exists.\n";
        return node;
    }

    node->height = 1 + max(height(node->left),height(node->right));
    int balance = getBalance(node);

    // LL Case
    if (balance > 1 && id < node->left->id)     
        return rightRotate(node);

    // RR Case
    if (balance < -1 && id > node->right->id) 
        return leftRotate(node);

    // LR Case
    if (balance > 1 && id > node->left->id) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
 
    // RL Case
    if (balance < -1 && id < node->right->id) {
        node->right = rightRotate(node->right); 
        return leftRotate(node);
    }
    return node;
}

// PUBLIC INSERT
void AVLTree::insert(int id,int x,int y) {
    root = insertNode(root,id,x,y);
}

// SEARCH
AVLTree::Node* AVLTree::searchNode(Node* node,int id) {

    if (node == nullptr || node->id == id)     return node;

    if (id < node->id)      return searchNode(node->left,id);

    return searchNode(node->right,id);
}

// GET ITEM LOCATION
bool AVLTree::getItemLocation(int id,int& x,int& y) {

    Node* item = searchNode(root,id);
    if (item == nullptr)   
        return false;
    x = item->x;
    y = item->y;
    return true;
}

// INORDER TRAVERSAL
void AVLTree::inorder(Node* node) {

    if (node == nullptr)        
        return;
    inorder(node->left);
    cout << "Item " << node->id << " at ("
         << node->x << "," << node->y << ")\n";
    inorder(node->right);
}

// DISPLAY
void AVLTree::display() {
    cout << "\nInventory:\n";
    if (root == nullptr) {
        cout << "-----Empty-----\n";
        return;
    }
    inorder(root);
}

// CHECK EMPTY
bool AVLTree::empty() {
    return root == nullptr;
}

// DELETE TREE
void AVLTree::deleteTree(Node* node) {
    if (node == nullptr)        
        return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// DESTRUCTOR
AVLTree::~AVLTree() {
    deleteTree(root);
}