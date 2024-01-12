#ifndef STACK_H
#define STACK_H
#include <string>
#include <stdexcept>

using namespace std;

const int MAX_SIZE = 20;

template<typename T> class stack{
    private:
        T data[MAX_SIZE]; // array to hold stack elements
        int size; // stack's size

    public:
        stack();
        void push(T val);
        void pop();
        void pop_two();
        T top() const;
        bool empty() const;
};
#endif

template<typename T>
stack<T>::stack(){
    size = 0;
}

template<typename T>
void stack<T>::push(T val){
    // if the stack is full, throw an overflow error
    if(size == MAX_SIZE){
        throw overflow_error("Called push on full stack.");
    }
    // add a new element to the top of the stack
    size ++;
    data[size] = val; 
}

template<typename T>
void stack<T>::pop(){
    // if the stack is empty, throw an out of range error 
    if(size <= 0){
        throw out_of_range("Called pop on empty stack.");
    }
    // remove the top element from the stack
    size --;
}

template<typename T>
void stack<T>::pop_two(){
    // if the stack is empty, throw an out of range error
    if(size == 0){
        throw out_of_range("Called pop_two on empty stack.");
    }
    //if the stack's size is 1, throw an out of range error 
    if(size == 1){
        throw out_of_range("Called pop_two on a stack of size 1.");
    }
    // remove the top two elements from the stack
    size -= 2;
}

template<typename T>
T stack<T>::top() const{
    // if the stack is empty, throw an underflow error
    if(size == 0){
        throw underflow_error("Called top on empty stack.");
    }
    // return the top element of the stack
    return data[size];
}

template<typename T>
bool stack<T>::empty() const{
    // check if the stack is empty
    return (size == 0);
}
