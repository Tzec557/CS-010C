#ifndef __PRINTJOB_H
#define __PRINTJOB_H

using namespace std;

class PrintJob {
  private:
    int priority;
    int jobNumber;
    int numPages;

  public:
    PrintJob ( int, int, int);

    // accessor function
    int getPriority ( ) const;
    int getJobNumber ( ) const;
    int getPages ( ) const;
    
};
#endif