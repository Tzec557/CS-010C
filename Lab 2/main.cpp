#include "IntList.h"
#include <iostream>

using namespace std;

int main(){
    // Test the default constructor
    IntList list1;
    cout << "List1: " << list1 << endl;

    // Test empty()
    cout << "Is List1 empty : " << boolalpha << list1.empty() << endl;
   

    // Test push_front()
    list1.push_front(1);
    list1.push_front(2);
    list1.push_front(3);
    list1.push_front(4);
    cout << "List1 (after push_front()): " << list1 << endl;

    // Test pop_front()
    list1.pop_front();
    cout << "List1 (after pop_front()): " << list1 << endl;

    // Test printReverse()
    cout << "List1 (reverse order): ";
    list1.printReverse();
    cout << endl;

    // Test empty()
    cout << "Is List1 empty: " << boolalpha << list1.empty() << endl;
    cout << endl;

    // Test push_back()
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    list1.push_back(4);
    cout << "List1 (after push_back()): " << list1 << endl;

    // Test pop_back()
    list1.pop_back();
    cout << "List1 (after pop_back()): " << list1 << endl;

    return 0;
}