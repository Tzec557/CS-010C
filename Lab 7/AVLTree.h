#ifndef __AVLTREE_H
#define __AVLTREE_H

#include "Node.h"

class AVLTree {
  private:
    Node *root;

  public:
    AVLTree( );
    ~AVLTree( );
    void insert(const string &);
    int balanceFactor(Node*) const;
    void printBalanceFactors() const;
    void visualizeTree(const string &);
  

  private:
    void deleteNodes(Node* );
    void printBalanceFactors(Node* ) const;
    bool setChild(Node* , string , Node* );
    bool replaceChild(Node* , Node* , Node* );
    void updateHeight(Node *);
    void rotateLeft(Node *);
    void rotateRight(Node* );
    void rebalance(Node* );
    void visualizeTree(ofstream & , Node *);

    // Copy constructor is private to prevent accidental copying of the list
    AVLTree(const AVLTree &);
    // Disabling the copy assignment operator
    AVLTree& operator=(const AVLTree&);
};

#endif

