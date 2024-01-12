#include "AVLTree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;
AVLTree::AVLTree( ){
  root = 0;
}

AVLTree::~AVLTree( ){
  deleteNodes(root);
}

void AVLTree::deleteNodes(Node* cur) {
  // if current node is null, return
  if (cur == 0) {
    return;
  }
  // delete left and right subtree recursively
  deleteNodes(cur->left);
  deleteNodes(cur->right);
  // deallocate memory of node
  delete cur;
}

void AVLTree::insert(const string &str){
  Node* newNode = new Node(str); 
  Node* cur = root;
  // if the tree is empty, make the new node the root
  if (root == 0) {
    root = newNode; 
    root->parent = 0;
    return;
  }
  // traverse the tree to find the appropriate position for the new node
  while (cur != 0) {
    // if the new node's data is equal to the current node's data, exit the loop
    if(newNode->data == cur->data){
      cur = 0;
    }
    // if the new node's data is less than the current node's data
    else if (newNode->data < cur->data) {
      // if the current node has no left child, insert the new node as the left child
      if (cur->left == 0) {
        cur->left = newNode;
        newNode->parent = cur;
        cur = 0;
      }
      // otherwise, traverse the left subtree
      else{
        cur = cur->left;
      }
    }
    // if the new node's data is greater than the current node's data
    else if (newNode->data > cur->data){
      // if the current node has no right child, insert the new node as the right child
      if (cur->right == 0) {
        cur->right = newNode;
        newNode->parent = cur;
        cur = 0;
      }
      // otherwise, traverse the right subtree
      else{
        cur = cur->right;
      }
    }
  }
  // check for balance and rebalanced if necessary after inserting a new node.
  newNode = newNode->parent;
  while (newNode != 0) { 
    rebalance(newNode); 
    newNode = newNode->parent;    
  }
}

int AVLTree::balanceFactor(Node *cur) const{
  int leftH = -1;
  if (cur->left != 0){
    // get the height of the left child
    leftH = cur->left->height;
  }
  int rightH = -1;
  if (cur->right != 0 ){
    // get the height of the right child
    rightH = cur->right->height;
  }
   // calculate and return the balance factor of the current node
  return leftH - rightH;
}

void AVLTree::printBalanceFactors() const{
  printBalanceFactors(root);
}

void AVLTree::printBalanceFactors(Node* cur) const{
  // if current is not empty
  if(cur != 0){
    // recursively print balance factors of the left subtree
    printBalanceFactors(cur->left);
    cout << cur->data << "(" << balanceFactor(cur) << "), ";
    // recursively print balance factors of the right subtree
    printBalanceFactors(cur->right);
  }
}

bool AVLTree::setChild(Node* parent, string whichChild, Node* child){
  // if the provided child position is valid
  if(whichChild != "left" && whichChild != "right"){
    return false;
  }
  if(whichChild == "left"){
    // set the left child of the parent
    parent->left = child;
  }
  else{
    // set the right child of the parent
    parent->right = child;
  }
  if(child != 0){
    // update the parent pointer of the child
    child->parent = parent;
  }
  // update the height of the parent node
  updateHeight(parent);
  return true;
}

bool AVLTree::replaceChild(Node* parent, Node* currentChild, Node* newChild){
  // if the current child is the left child of the parent
  if(parent->left == currentChild){
    // replace the left child with the new child
    return setChild(parent, "left", newChild);
  }
  // if the current child is the right child of the parent
  else if(parent->right == currentChild){
     // replace the right child with the new child
    return setChild(parent, "right", newChild);
  }
  return false;
}

void AVLTree::updateHeight(Node *cur){
  int leftH = -1;
  if (cur->left){
    // get the height of the left child
    leftH = cur->left->height;
  }
  int rightH = -1;
  if (cur->right){
     // get the height of the right child
    rightH = cur->right->height;
  }
    // update the height of the current node
  cur->height = max(leftH, rightH) + 1;
}

void AVLTree::rotateLeft(Node *cur){
  // store the left child of the right child
  Node* rightLeftChild = cur->right->left;
  // if the parent node is not empty
  if (cur->parent != 0){
    // replace the current node with its right child
    replaceChild(cur->parent, cur, cur->right);
  }
  else{
    // update the root of the tree
    root = cur->right;
    root->parent = 0;
  }
  // set the appropriate child pointers
  setChild(cur->right, "left", cur);
  setChild(cur, "right", rightLeftChild);
}

void AVLTree::rotateRight(Node* cur){
  // store the right child of the left child
  Node* leftRightChild = cur->left->right;
  // if the parent node is not empty
  if(cur->parent != 0){
    // replace the current node with its left child
    replaceChild(cur->parent, cur, cur->left);
  }
  else{
    // update the root of the tree
    root = cur->left;
    root->parent = 0;
  }
  // set the appropriate child pointers
  setChild(cur->left, "right", cur);
  setChild(cur, "left", leftRightChild);
}

void AVLTree::rebalance(Node* cur){
  // update the height of the current node
  updateHeight(cur);
  // check the balance factor and perform rotations if necessary
  if(balanceFactor(cur) == -2){
    if(balanceFactor(cur->right) == 1){
      // double rotation case: right-left
      rotateRight(cur->right);
    }
    // single rotation case: left
    rotateLeft(cur);
  }
  else if(balanceFactor(cur) == 2){
    if(balanceFactor(cur->left) == -1){
      // double rotation case: left-right
      rotateLeft(cur->left);
    }
    // single rotation case: right
    rotateRight(cur);
  }
}

void AVLTree::visualizeTree(const string &outputFilename){
  // open the output file
  ofstream outFS(outputFilename.c_str());
  if(!outFS.is_open()){
    cout << "Error" << endl;
    return;
  }
  // write the graph header
  outFS << "digraph G {" << endl;
  // recursively visualize the tree
  visualizeTree(outFS,root);
  // write the graph footer
  outFS << "}";
  // close the output file
  outFS.close();
  // generate the image file using the 'dot' command
  string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
  string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
  system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *cur){
  if(cur){
    if(cur->left){
      // visualize the left child and draw an edge from the current node to the left child
      visualizeTree(outFS,cur->left);
      outFS << cur->data << " -> " << cur->left->data << ";" << endl;    
    }

    if(cur->right){
      // visualize the right child and draw an edge from the current node to the right child
      visualizeTree(outFS,cur->right);
      outFS << cur->data <<" -> " << cur->right->data << ";"<<endl;    
    }
  }
}