#ifndef __NODE_H
#define __NODE_H

#include <string>

using namespace std;

class Node {
  public:
    Node(string);
    // declare AVLTree as friend class to access the private members
    friend class AVLTree;

  private:
    Node *left;
    Node *right;
    Node *parent;
    string data;
    int height;

};

#endif