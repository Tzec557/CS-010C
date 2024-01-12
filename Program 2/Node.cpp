#include "Node.h"
#include <iostream>
#include <string>

using namespace std;

Node::Node(string val){
    // initialize the value
    left = 0;
    right = 0;
    data = val;
    count = 1;
}