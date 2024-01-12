#ifndef BSTREE_H
#define BSTREE_H
#include <string>
#include "Node.h"

class BSTree{
    private:
        // Copy constructor is private to prevent accidental copying of the list
        BSTree(const BSTree &);
        // Disabling the copy assignment operator
        BSTree& operator=(const BSTree&);
        
        Node* root;
        void deleteNodes(Node* );
        void insert_helper(const string &, Node* &);
        void remove_helper(const string &, Node* &, Node* );
        Node* search_helper(const string&, Node* ) const;
        int height_helper(Node* ) const;

        void preOrder_helper(Node* ) const;
        void inOrder_helper(Node* ) const;
        void postOrder_helper(Node* ) const;
        
    public:
        BSTree();
        ~BSTree();
        
        void insert(const string &);
        void remove(const string &);
        bool search(const string &) const;
        int height(const string &) const;
        string largest() const;
        string smallest() const;
    
        void preOrder();
        void inOrder();
        void postOrder();
};

#endif