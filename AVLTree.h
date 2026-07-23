#ifndef AVLTREE_H
#define AVLTREE_H

class AVLTree {

    private:
        struct Node {
            int id,x,y;
            int height;

            Node* left;
            Node* right;
            Node(int id, int x, int y);
        };

        Node* root;
        int height(Node* node);
        int getBalance(Node* node);

        Node* rightRotate(Node* node);
        Node* leftRotate(Node* node);
        Node* insertNode(Node* node,int id,int x,int y);
        Node* searchNode(Node* node,int id);

        void inorder(Node* node);
        void deleteTree(Node* node);

    public:
        AVLTree();
        ~AVLTree();

        void insert(int id,int x,int y);
        bool getItemLocation(int id,int& x,int& y);
        void display();
        bool empty();
};

#endif