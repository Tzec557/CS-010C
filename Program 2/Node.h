#ifndef NODE_H
#define NODE_H
#include <string>

using namespace std;

class Node{
    private:
        Node* left;
        Node* right;
        string data;
        int count;
        
    public:
        Node(string);
        // declare BStree as friend class to access the private members
        friend class BSTree;
};

#endif