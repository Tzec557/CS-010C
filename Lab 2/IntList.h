#ifndef INTLIST_H
#define INTLIST_H
#include <string>

using namespace std;

struct IntNode {
    int data;
    IntNode *prev;
    IntNode *next;
    IntNode(int data) : data(data), prev(0), next(0) {}
};

class IntList {
    private:
        // Copy constructor is private to prevent accidental copying of the list
        IntList(const IntList&);

        IntNode* dummyHead;
        IntNode* dummyTail;

    public:
        // Constructor and destructor
        IntList();
        ~IntList();

        void push_front(int value);
        void pop_front();
        void push_back(int value);
        void pop_back();
        bool empty() const;
        friend ostream & operator<<(ostream &out, const IntList &rhs);
        void printReverse() const;
};

#endif