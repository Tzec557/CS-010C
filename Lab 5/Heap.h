#ifndef __HEAP_H
#define __HEAP_H

#include "PrintJob.h"

const int MAX_HEAP_SIZE = 10;

class Heap {
  private:
    PrintJob* arr[MAX_HEAP_SIZE]; // array of PrintJob pointer
    int numItems;  //current number of items in heap

  public:
    Heap();
    void enqueue ( PrintJob* );
    void dequeue ( );
    PrintJob* highest ( ) const;
    void print ( ) const;

  private:
    void trickleDown(int);
};
#endif
