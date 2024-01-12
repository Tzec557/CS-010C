#include <iostream>
#include "Heap.h"

using namespace std;

// function to display menu and get user's choice
int menu() {
  int choice = 0;
  cout << endl << "Enter menu choice: ";
  cout << endl;
  cout << "1. Enqueue" << endl;
  cout << "2. Print" << endl;
  cout << "3. Dequeue" << endl;
  cout << "4. Quit" << endl;
  cin >> choice;

  // Fix buffer just in case a non-numeric choice is entered
  // Also gets rid of the newline character
  cin.clear();
  cin.ignore(256, '\n');
  return choice;
}

int main(){
  Heap max_heap;
  int choice = menu();

  while (choice != 4) {
    if (choice == 1) {
      int priority, jobNumber, numPages;
      cout << "Enter print job to enqueue (priority, job Number, number of pages): ";
      cin>>priority>>jobNumber>>numPages;
      cout << endl;
      // enqueue the printjob
      max_heap.enqueue(new PrintJob(priority, jobNumber, numPages));
    } 
    else if (choice == 2) {
      // print the highest priority printjob
      max_heap.print();
    }
    else if (choice == 3) {
      // dequeue the highest priority printjob
      max_heap.dequeue();
    }

    choice = menu();
  }
  return 0;
}