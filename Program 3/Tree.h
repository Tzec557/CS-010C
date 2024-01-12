#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree( );
  ~Tree( );
  void insert(const string &);
  void remove(const string &);
  bool search (const string &) const;
  void preOrder( ) const;
  void inOrder( ) const;
  void postOrder( ) const;

private:
  void deleteTree(Node* );
  void insert(Node* , const string &);
  void remove(Node* , const string &);
  bool search(Node* , const string &) const;
  void preOrder(Node* ) const;
  void inOrder(Node* ) const;
  void postOrder(Node* ) const;

  // Copy constructor is private to prevent accidental copying of the list
  Tree(const Tree &);
  // Disabling the copy assignment operator
  Tree& operator=(const Tree&);

};

#endif