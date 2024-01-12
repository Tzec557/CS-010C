#include "IntList.h"
#include <iostream>
#include <string>

using namespace std;

IntList::IntList() {
    // Create dummy head and tail nodes with value 0
    dummyHead = new IntNode(0);
    dummyTail = new IntNode(0);

    // Connect dummy head and tail nodes to each other
    dummyHead -> next = dummyTail;
    dummyTail -> prev = dummyHead;
}

IntList::~IntList(){
    // Delete all nodes in the list
    while (!empty()) {
        pop_front();
    }

    // Delete dummy head and tail nodes
    delete dummyHead;
    delete dummyTail;
}

void IntList::push_front(int value){
    IntNode* newNode = new IntNode(value);

    // Connect new node after the dummy head node
    newNode -> next = dummyHead -> next;
    dummyHead -> next =  newNode;
    newNode -> prev = dummyHead;
    newNode -> next -> prev = newNode;
    
}

void IntList::pop_front(){
    // Check if the list is empty
    if(empty()){
        return;
    }

    // Remove the node after the dummy head node
    IntNode* nodeToRemove = dummyHead -> next;
    nodeToRemove -> next -> prev = dummyHead;
    dummyHead -> next = nodeToRemove -> next;
    delete nodeToRemove;
}

void IntList::push_back(int value){
    IntNode* newNode = new IntNode(value);

    // Connect new node before the dummy tail node
    newNode -> prev = dummyTail -> prev;
    dummyTail -> prev -> next =  newNode;
    newNode -> next = dummyTail;
    dummyTail -> prev = newNode;
}

void IntList::pop_back(){
    // Check if the list is empty
    if(empty()){
        return;
    }
   
    // Remove the node before the dummy tail node
    IntNode* nodeToRemove = dummyTail -> prev;
    nodeToRemove -> prev -> next = dummyTail;
    dummyTail -> prev = nodeToRemove -> prev;
    delete nodeToRemove;
}

bool IntList::empty() const{
    // Returns true if the list does not store any data values (it only has dummy head and dummy tail)
    return dummyHead -> next == dummyTail;
}

// Print the contents of the list
ostream & operator<<(ostream &out, const IntList &rhs){
    IntNode* cur = rhs.dummyHead -> next;
    while(cur != rhs.dummyTail){
        out << cur -> data;
        // Move to the next node
        cur = cur -> next;

        // Output a space if this is not the last node
        if(cur != rhs.dummyTail){
            out << " ";
        }
    }
    return out;
}

void IntList::printReverse() const{
    IntNode* cur = dummyTail -> prev;
    while(cur != dummyHead){
        cout << cur -> data << " ";

        // Move to the previous node
        cur = cur -> prev;
    }
}