#include "Tree.h"
#include <iostream>

using namespace std;

Tree::Tree( ){
  root = 0;
}

Tree::~Tree( ){
  deleteTree(root);
}

void Tree::deleteTree(Node* cur){
  // check if the tree is not empty
  if(cur != 0){
    // recursively deletes all nodes in the tree to deallocate memory
    deleteTree(cur -> left);
    deleteTree(cur -> middle);
    deleteTree(cur -> right);
    delete cur;
  }
}

void Tree::insert(const string &str){
  insert(root, str);
}

void Tree::insert(Node* cur, const string &str) {
  // if the string already exists, return 
  if (search(str)) {
    return;
  }
  // if the current node is empty
  if (cur == 0) {
    // set root to the given string
    root = new Node(str);
    return;
  }
  // if current node is a leaf node
  if (cur -> left == 0 && cur -> middle == 0 && cur -> right == 0) {
    // check if the large value of cur is empty
    if (cur -> large == "") {
      // if the given string is smaller than the small value of current node
      if (str < cur -> small) {
        // swap the values to maintain the order
        cur -> large = cur -> small;
        cur -> small = str;
      }
      else {
        // set large value of current node to the given string
        cur -> large = str;
      }
    } 
    // if the large value of cur is not empty
    else {
      // create three string value to store the left, middle, and right value
      string leftV, middleV, rightV;
      // if string is smaller than the small value of current node, update the values
      if (str < cur -> small) {
        leftV = str;
        middleV = cur -> small;
        rightV = cur -> large;
      } 
      // if string is greater than the small value of current node
      // and less than the large value of current node, update the values
      else if (str > cur -> small && str < cur -> large) {
        leftV = cur -> small;
        middleV = str;
        rightV = cur -> large;
      } 
      // if string is greater than the large value of current node, update the values
      else if (str > cur -> large) {
        leftV = cur -> small;
        middleV = cur -> large;
        rightV = str;
      }
      // create new nodes for the updated values
      Node* leftN = new Node(leftV);
      Node* middleN = new Node(middleV);
      Node* rightN = new Node(rightV);

      // if the current node is the root
      if (cur == root) {
        // update the root and rearrange the nodes accordingly
        root = middleN;
        delete cur;
        middleN -> left = leftN;
        middleN -> middle = rightN;
        // set the parent to connect
        leftN -> parent = middleN;
        rightN -> parent = middleN;
      } 
      // if the current node is not the root
      else {
        Node* parent = root;
        // if middle child of the parent node is the current node
        if(parent -> middle == cur){
          // update the values of the parent node and rearrange the nodes
          parent -> large = middleV;
          parent -> middle -> large = "";
          parent -> right = rightN;
          // set the parent to connect
          rightN -> parent = middleN;
        }
      }
    }
    return;
  }
  Node* nextNode;
  // determine the next node to traverse based on the string value
  if (str < cur -> small) {
    nextNode = cur -> left;
  } 
  else if (cur -> large != "" && str > cur -> large) {
    nextNode = cur -> right;
  } 
  else {
    nextNode = cur -> middle;
  }
  insert(nextNode, str);
}

void Tree::remove(const string &str){
  remove(root, str);
}
void Tree::remove(Node* cur, const string &str){
  // if the current node is empty, return
  if(cur == 0){
    return;
  }
  // if the given string doesn't exist in the tree, return
  if(!search(str)){
    return;
  }
  // if the current node is a leaf node
  if(cur -> left == 0 && cur -> right == 0){
    // check if the small value of the current node match
    if(cur -> small == str){
      // update the current node's small value
      cur -> small = cur -> large;
      // clear the large value
      cur -> large = "";
    }
    // check if the large value of the current node match
    else if(cur -> large == str){
      // clear the large value
      cur -> large = "";
    }
    // if both small and large values are empty
    if (cur -> small == "" && cur -> large == "") {
      // if the current node is the root
      if (cur == root) {
        delete cur;
        // update the root
        root = 0;
      } 
      else {
        Node* parent = root;
        // update the parent node based on the child node being removed
        if(parent -> left == cur){
          parent -> large = parent -> middle -> small;
          // clear the left and middle child.
          parent -> left = 0;
          parent -> middle = 0;
        }
        else if(parent -> middle == cur){
          parent -> large = parent -> small;
          parent -> small = parent->left->small;
          // clear the left and middle child.
          parent -> left = 0;
          parent -> middle = 0;
        }
      }
    }
  }
  // if the root node's small value match the given string and there are two child nodes
  else if(root -> small == str && cur -> left != 0 && cur -> middle != 0){
    // update the root node's small and large value
    root -> small = root -> left -> small;
    root -> large = root -> middle -> small;
    // clear the left and middle child
    root -> left = 0;
    root -> middle = 0;
  }
  else{
    Node* nextNode;
    // determine the next node to traverse based on the string value
    if (str < cur -> small) {
      nextNode = cur -> left;
    } 
    else if (cur -> large != "" && str > cur -> large) {
      nextNode = cur -> right;
    } 
    else {
      nextNode = cur -> middle;
    }
    remove(nextNode, str);
  }
}

void Tree::preOrder( ) const{
  preOrder(root);
}

void Tree::preOrder(Node* cur) const{
  if(cur != 0){
    // output the small value of the current node
    cout << cur -> small << ", ";
    // recursively traverse the left subtree
    preOrder(cur -> left);
    if(cur -> large != ""){
      // output the large value of the current node if it exists
      cout << cur -> large << ", ";
    }
    // Recursively traverse the middle subtree and the right subtree.
    preOrder(cur -> middle);
    preOrder(cur -> right);
        
  }
}

void Tree::inOrder( ) const{
  inOrder(root);
}

void Tree::inOrder(Node* cur) const{
  if(cur != 0){
    // recursively traverse the left subtree
    inOrder(cur -> left);
    // output the small value of the current node
    cout << cur -> small << ", ";
    // recursively traverse the middle subtree
    inOrder(cur -> middle);
    if(cur -> large != ""){
      // output the large value of the current node if it exists
      cout << cur -> large << ", ";
    }
    // recursively traverse the right subtree
    inOrder(cur -> right);
        
  }
}

void Tree::postOrder( ) const{
  postOrder(root);
}

void Tree::postOrder(Node* cur) const {
  if (cur != nullptr) {
    // recursively traverse the left subtree and middle subtree
    postOrder(cur -> left);
    postOrder(cur -> middle);
    // output the small value of the current node
    cout << cur -> small << ", ";
    if (cur -> large != "") {
      // recursively traverse the right subtree
      postOrder(cur -> right);
      // output the large value of the current node if it exists
      cout << cur -> large << ", ";
    }
  }
}

bool Tree::search (const string &str) const{
  return search(root, str);;
}

bool Tree::search(Node* cur, const string &str) const{
  // check if the current node is empty
  if(cur == 0){
    return false;
  }
  // check if the string is found in the current node
  if(cur -> small == str || cur -> large == str){
    return true;
  }
  // if string is smaller than the small value of current node
  if(str < cur -> small){
    // recursively search in the left subtree
    return search(cur -> left, str);
  }
   // if the large value of the current node is not empty 
   // and the given string is greater than the large value
  else if(cur -> large != "" && str > cur -> large){
    // recursively search in the right subtree
    return search(cur -> right, str);
  }
  // if the given string falls between the small and large values of the current node
  else{
    // recursively search in the middle subtree
    return search(cur -> middle, str);
  }
}