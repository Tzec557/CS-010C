#include "arithmeticExpression.h"
#include <cstdlib>
#include <stack>
#include <fstream>
#include <sstream>

/* Initializes an empty tree and sets the infixExpression
    to the value of parameter passed in. */
arithmeticExpression::arithmeticExpression(const string &input){
    // initializes an empty tree and sets the infixExpression to the passed in value
    root = 0;
    infixExpression = input;
}

/* Implementation of destrucor is optional.
       The destructor should deallocate all the nodes in the tree. */
arithmeticExpression::~arithmeticExpression(){
    // deallocates all the nodes in the tree
    deleteNodes(root);
}
// helper function used by the destructor to delete nodes
void arithmeticExpression::deleteNodes(TreeNode* cur) {
    // if node is null, return
    if (cur == 0) {
        return;
    }
    // delete left and right subtree recursively
    deleteNodes(cur -> left);
    deleteNodes(cur -> right);
    // deallocate memory of node
    delete cur;
    cur = 0;
}

/* Converts the infixExpression to its equivalent postfix string
       and then generates the tree and assigns the root node to the 
       root data field. The key for the first node is 'a', 'b' for the second node and so on. */
void arithmeticExpression::buildTree(){
    infixExpression = infix_to_postfix();
    stack <TreeNode*> stack1;
    char key = 'a';

    for(unsigned i = 0; i < infixExpression.size(); i++, key++){
        // create a new TreeNode with the current character and a unique key
        TreeNode *newNode = new TreeNode(infixExpression.at(i), key);
        // if the current character is an operator
        if(priority(infixExpression.at(i)) != 0){
            // assign them as the left and right children of newNode and pop the top two nodes from the stack
            newNode -> right = stack1.top();
            stack1.pop();
            newNode -> left = stack1.top();
            stack1.pop();
        }
        // push the new node onto the stack
        stack1.push(newNode);
    }
    // the top of the stack will contain the root of the expression tree
    root = stack1.top();
}

void arithmeticExpression::infix() const{
    infix(root);
}

// infix() helper function
void arithmeticExpression::infix(const TreeNode *cur) const{
    // check if the current node is not null
    if(cur != 0){
        // output '(' if the left child exists
        if(cur -> left != 0){
            cout << "(";
        }
        // recursively traverse the left subtree
        infix(cur -> left);
        // output the data of the current node
        cout << cur -> data;
        // recursively traverse the right subtree
        infix(cur -> right);

        // output ')' if the right child exists
        if(cur -> right != 0){
            cout << ")";
        }
    }
}

void arithmeticExpression::prefix() const{
    prefix(root);
}

// prefix() helper function
void arithmeticExpression::prefix(const TreeNode *cur) const{
    // check if the current node is not null
    if(cur != 0){
        // output the data of the current node
        cout << cur -> data;
        // recursively traverse the left and subtree
        prefix(cur -> left);
        prefix(cur -> right);
    }
}

void arithmeticExpression::postfix() const{
    postfix(root);
}

// postfix() helper function
void arithmeticExpression::postfix(const TreeNode *cur) const{
    // check if the current node is not null
    if(cur != 0){
        // recursively traverse the left and subtree
        postfix(cur -> left);
        postfix(cur -> right);
        // output the data of the current node
        cout << cur -> data;
    }
}

int arithmeticExpression::priority(char op) const{
    int priority = 0;
    // parentheses have the highest priority
    if(op == '('){
        priority =  3;
    }
    // multiplication and division have second higher priority
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    // addition and subtraction have the lowest priority
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    // returns the priority level of the given operator
    return priority;
}

// converts the infix expression to its equivalent postfix string
string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        // skip whitespace
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            // push '(' onto the stack
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                // pop operators from the stack and append them to the output string until '(' encountered
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                // pop '(' from the stack
                s.pop();
            }
            else{
                // pop operators from the stack and append them to the output string 
                // when they have higher or equal priority with c
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                // push c onto the stack
                s.push(c);
            }
        }
        else{ 
            // c is an operand, append it to the output string
            oss << c;
        }
    }
    // pop any remaining operators from the stack and append them to the output string
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

/* Graphviz part (optional)
void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}


void arithmeticExpression::visualizeTree(ofstream &, TreeNode *){

}
*/