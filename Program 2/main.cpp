#include <iostream>
#include <limits>
#include "BSTree.h"

using namespace std;

// function to display preorder, inorder, and postorder of a BSTree
void printOrders(BSTree *tree) {
    cout << "Preorder = ";
    tree->preOrder( );
    cout << "Inorder = ";
    tree->inOrder( );
    cout << "Postorder = ";
    tree->postOrder( );
}

// function to display the menu and get the user's choice
int menu() {
    int choice = 0;
    cout << endl << "Enter menu choice: ";
    cout << endl;
    cout << "1. Insert" << endl;
    cout << "2. Remove" << endl;
    cout << "3. Print" << endl;
    cout << "4. Search" << endl;
    cout << "5. Smallest" << endl;
    cout << "6. Largest" << endl;
    cout << "7. Height" << endl;
    cout << "8. Quit" << endl;
    cin >> choice;
    // ignore any remaining characters in the input stream
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

int main( ) {
    BSTree tree;
    // get user choice from the menu function
    int choice = menu();
    string entry;

    while (choice != 8) {
        if (choice == 1) {
            // insert string into tree
            cout << "Enter string to insert: " << endl;
            getline(cin,entry);
            tree.insert(entry);
        }
        else if (choice == 2) {
            // remove string from tree
            cout << "Enter string to remove: " << endl;
            getline(cin,entry);
            tree.remove(entry);
        }
        else if (choice == 3) {
            // print the tree in different traversal orders
            printOrders(&tree);
        }
        else if (choice == 4) {
            // search the string in the tree
            cout << "Enter string to search for: " << endl;
            getline(cin,entry);
            bool found = tree.search(entry);

            if(found){
                cout << "Found" << endl;
            }
            else{
                cout << "Not Found" << endl;
            }
        }       
        else if (choice == 5) {
            // print the smallest string in the tree
            cout << "Smallest: " << tree.smallest() << endl;
        }
        else if (choice == 6) {
            // print the largest string in the tree
            cout << "Largest: " << tree.largest() << endl;
        }
        else if (choice == 7) {
            // print the height of the subtree rooted at the given string
            cout << "Enter string: " << endl;
            getline(cin,entry);
            cout << "Height of subtree rooted at " << entry << ": " << tree.height(entry) << endl;
        }
        // get the next user choice from the menu function
        choice = menu();
    }
    return 0;
}

