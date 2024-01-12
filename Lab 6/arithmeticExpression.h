#ifndef ARITHMETICEXPRESSION_H
#define ARITHMETICEXPRESSION_H
#include <iostream>
#include <cstdlib>

using namespace std;
struct TreeNode{
    char data;
    char key;
    TreeNode* left;
    TreeNode* right;
    // constructor to initialize TreeNode
    TreeNode(char data, char key):data(data),key(key),left(0),right(0){}
};

class arithmeticExpression{
    private:
        string infixExpression;
        TreeNode* root;

    public:
        arithmeticExpression(const string &);
        ~arithmeticExpression();
        void buildTree();
        void infix() const;
        void prefix() const;
        void postfix() const;
        // (optional) void visualizeTree(const string &);

    private:
        // copy constructor is private to prevent accidental copying of the list
        arithmeticExpression(const arithmeticExpression&);   
        // copy assignment operator is declared private to prevent accidental copying of the list
        arithmeticExpression& operator=(const arithmeticExpression&);

        void deleteNodes(TreeNode* );
        int priority(char) const;
        string infix_to_postfix();
        void infix(const TreeNode *) const;
        void prefix(const TreeNode *) const;
        void postfix(const TreeNode *) const;
        // (optional) void visualizeTree(ofstream &, TreeNode *); 
};
#endif