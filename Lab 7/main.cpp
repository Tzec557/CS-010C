#include <iostream>
#include "AVLTree.h"

using namespace std;

// function to display the menu and get user choice
int menu() {
  int choice = 0;
  cout << endl << "Enter menu choice: ";
  cout << endl;
  cout 
    << "1. Insert" << endl
    << "2. Print" << endl
    << "3. Quit" << endl;
  cin >> choice;

  // fix buffer just in case non-numeric choice entered
  // also gets rid of newline character
  cin.clear();
  cin.ignore(256, '\n');
  return choice;
}

int main( ) {

  AVLTree tree;

  int choice = menu();

  string entry;

  while (choice != 3) {

    if (choice == 1) {
      cout << "Enter string to insert: ";
      getline(cin, entry);
      cout << endl;
      // insert the entered string into the AVL tree
      tree.insert(entry);
    } 
    else if (choice == 2) {
      // print the balance factors of all nodes in the AVL tree
      tree.printBalanceFactors();
      cout << endl;

    } 
    //fix buffer just in case non-numeric choice entered
    choice = menu();
  }

  return 0;
}