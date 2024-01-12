#include "Heap.h"
#include <iostream>
#include <string>

using namespace std;

Heap::Heap(){
  numItems = 0;
}

void Heap::enqueue (PrintJob* job){
  // check if there is space available in the heap
  if(numItems < MAX_HEAP_SIZE){
    arr[numItems] = job;
    int curIndex = numItems;
    int parentIndex = (curIndex - 1)/2;
    // compare and swap the priority of the new added job and its parent index's priority
    while(curIndex > 0 && arr[curIndex]-> getPriority() > arr[parentIndex] -> getPriority()){
      swap(arr[curIndex], arr[parentIndex]);
      // update the index
      curIndex = parentIndex;
      parentIndex = (curIndex - 1)/2;
    }
    numItems++;
  }
}

void Heap::dequeue (){
  // check if there is only one item in the heap
  if(numItems == 1){
    arr[0] = nullptr;
    numItems--;
    return;
  }
  // check if there is more than one item in the heap
  if(numItems > 1){
    // replaced the root with the last item in the heap
    arr[0] = arr[numItems - 1];
    arr[numItems - 1] = nullptr;
    numItems--;
    // adjust the heap by calling trickleDown function
    trickleDown(0);
  }
}
  
PrintJob* Heap::highest () const{
  // check if the heap is empty
  if(numItems == 0){
    return nullptr;
  }
  else{
    // return the highest priority element
    return arr[0];
  }
}

void Heap::print () const{
  // check if the heap is empty
  if(numItems == 0){
    return;
  }
  // print the details of the highest priority element
  cout << "Priority: " << highest() -> getPriority() << ", ";
  cout << "Job Number: " << highest() -> getJobNumber() << ", ";
  cout << "Number of Pages: " << highest() -> getPages() << endl;
}

// help dequeue function to move the new root down the heap to appropriate location
void Heap::trickleDown(int index){
  int childIndex = 2 * index + 1;
  PrintJob* value = arr[index];

  while (childIndex < numItems) {
    PrintJob* maxValue = value;
    int maxIndex = -1;

    for (int i = 0; i < 2 && i + childIndex < numItems; i++) {
      // check if the priority of the child is greater than the current maximum value
      if (arr[i + childIndex]->getPriority() > maxValue->getPriority()) {
        // update the maximum value and its index
        maxValue = arr[i + childIndex];
        maxIndex = i + childIndex;
      }
    }
    // check if it already reach its appropriate position
    if (maxValue == value) {
      return;
    } 
    else {
      //swap the value in the current index and the value maxindex
      swap(arr[index], arr[maxIndex]);
      // update the index for next iteration
      index = maxIndex;
      childIndex = 2 * index + 1;
    }
  }
}
