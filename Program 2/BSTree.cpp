#include <iostream>
#include <string>
#include "Node.h"
#include "BSTree.h"

using namespace std;

BSTree::BSTree(){
    // set the root pointer to null
    root = 0;
}

BSTree::~BSTree(){
    // deallocate memory of all nodes using helper function
    deleteNodes(root);
}
void BSTree::deleteNodes(Node* cur) {
    // if node is null, return
    if (cur == 0) {
        return;
    }
    // delete left and right subtree recursively
    deleteNodes(cur->left);
    deleteNodes(cur->right);
    // deallocate memory of node
    delete cur;
}

void BSTree::insert(const string &newString){
    insert_helper(newString, root);
}

void BSTree::insert_helper(const string &newString, Node* &cur){
    // if current node is null, create a new node with the given string
    if(cur == 0){
        cur = new Node(newString);
    }
    // if the given string already exists, increment its count
    else if(cur -> data == newString){
        cur -> count++;
    }
    // if the given string is less than current node's value, insert it into the left subtree 
    else if(newString < cur -> data){
        insert_helper(newString, cur -> left);
    }
    // if the given string is greater than current node's value, insert it into the right subtree 
    else{
        insert_helper(newString, cur -> right);
    }
}

void BSTree::remove(const string &key) {
    remove_helper(key, root, nullptr);
}

void BSTree::remove_helper(const string &key, Node* &cur, Node* parent) {
    // if the current node is null, return
    if (cur == nullptr) {
        return;
    }
    // if the given string is less than current node's value,recursively find the place of key node in the left subtree
    if (cur -> data > key) {
        remove_helper(key, cur -> left, cur);
    } 
    // if the given string is greater than current node's value,recursively find the place of key node in the right subtree
    else if (cur -> data < key) {
        remove_helper(key, cur -> right, cur);
    } 
    // if found the node to be removed
    else { 
        // if the current node's count is more than 1, decrement the count
        if (cur -> count > 1) {
            cur -> count--;
        } 
        // if the current node is a leaf node
        else if (cur -> left == nullptr && cur -> right == nullptr) {
            // check if the cur is the root
            if (parent == nullptr) {
                root = nullptr;
            } 
            // update the parent's link to the node to be removed
            else if (parent -> left == cur) {
                parent -> left = nullptr;
            } 
            else {
                parent -> right = nullptr;
            }
            // delete the node
            delete cur;
        }
        // if the node has a left child
        else if (cur -> left != nullptr) {
            // find the maximum value in the left subtree
            Node* max_left = cur -> left;
            while (max_left -> right != nullptr) {
                max_left = max_left -> right;
            }
            // swap the data and the count of maximum node with the node to be removed 
            string max_left_data = max_left -> data;
            int max_left_count = max_left -> count;
            max_left -> count = 1;
            // remove the maximum node from its current position
            remove_helper(max_left -> data, cur -> left, cur);
            // update the data and the count
            cur -> data = max_left_data;
            cur -> count = max_left_count;
        } 
        // if the node has a right child
        else {
            // find the minimum value in the right subtree
            Node* min_right = cur -> right;
            while (min_right -> left != nullptr) {
                min_right = min_right -> left;
            }
            // swap the data and the count of minimum node with the node to be removed 
            string min_right_data = min_right -> data;
            int min_right_count = min_right -> count;
            min_right -> count = 1;
            // remove the maximum node from its current position
            remove_helper(min_right -> data, cur->right, cur);
            // update the data and the count
            cur -> data = min_right_data;
            cur -> count = min_right_count;
        }
    }
}

bool BSTree::search(const string &key) const{
    // check if the helper function returns a non-null pointer
    return (search_helper(key, root) != nullptr);
}

Node* BSTree::search_helper(const string &key, Node* cur) const{
    // if current node is null, return null
    if(cur == 0){
        return nullptr;
    }
    // if the current node's value match, return it
    if(cur -> data == key){
        return cur;
    }
    // if the the given string is less than the current node's value, search it in the left subtree
    if(key < cur -> data){
        return search_helper(key, cur -> left);
    }
    // if the the given string is greater than the current node's value, search it in the right subtree
    else{
        return search_helper(key, cur -> right);
    }
}

int BSTree::height(const string &key) const{
    Node* cur = search_helper(key,root);
    // if the value not found in the tree, return -1
    if(cur == 0){
        return -1;
    }
    // if the value found in the tree, call helper function
    else{
        return height_helper(cur);
    }
}
int BSTree::height_helper(Node* cur) const{
    int max;
    int leftHeight = 0;
    int rightHeight = 0;
    // if it is a empty node, return -1
    if(cur == 0){
        return -1;
    }
    else{
        // calculate the heights of the left and right subtrees
        leftHeight = height_helper(cur -> left);
        rightHeight = height_helper(cur -> right);
        // check which is the maximum height and return it
        if(leftHeight > rightHeight){
            max = 1 + leftHeight;
        }
        else{
            max = 1 + rightHeight;
        }
        return max;
    }
}

string BSTree::largest() const{
    Node* cur = root;
    // check if the tree is empty
    if(cur != 0){
        // traverse to the rightmost node to find the largest value
        while(cur -> right != 0){
            cur = cur -> right;
        }
        return cur -> data;
    }
    // if the tree is empty, return an empty string
    else{
        return "";
    }
}

string BSTree::smallest() const{
    Node* cur = root;
    // check if the tree is empty
    if(cur != 0){
        // traverse to the leftmost node to find the smallest value
        while(cur -> left != 0){
            cur = cur -> left;
        }
        return cur -> data;
    }
    // if the tree is empty, return an empty string
    else{
        return "";
    }
}

void BSTree::preOrder(){
    preOrder_helper(root);
    cout << endl;
}

void BSTree::preOrder_helper(Node* cur) const{
    // if the current node is null, return
    if(cur != 0){
        // print data and count
        cout << cur -> data << "(" << cur -> count << "), ";
        // recursively traverse the left and right subtree
        preOrder_helper(cur -> left);
        preOrder_helper(cur -> right);
    }
}

void BSTree::inOrder(){
    inOrder_helper(root);
    cout << endl;
}

void BSTree::inOrder_helper(Node* cur) const{
    // if the current node is null, return
    if(cur != 0){
        // recursively traverse the left subtree
        inOrder_helper(cur -> left);
        // print data and count
        cout << cur -> data << "(" << cur -> count << "), ";
        // recursively traverse the right subtree
        inOrder_helper(cur -> right);
    }
}

void BSTree::postOrder(){
    postOrder_helper(root);
    cout << endl;
}

void BSTree::postOrder_helper(Node* cur) const{
    if(cur != 0){
        // recursively traverse the left and right subtree
        postOrder_helper(cur -> left);
        postOrder_helper(cur -> right);
         // print data and count
        cout << cur -> data << "(" << cur -> count << "), ";
    }
}