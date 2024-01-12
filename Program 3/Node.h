#ifndef __NODE_H
#define __NODE_H

#include <string>

using namespace std;

class Node {
  public:
    Node(string);
    // declare Tree as friend class to access the private members
    friend class Tree;

  private:
    string small;
    string large;

    Node *left;
    Node *middle;
    Node *right;
    Node *parent;

};

#endif