# Lab 3: Function Template and Exception Handling

In part one, you are going to implement the selection sort function that is capable of sorting vectors of int, double or string. In part two you will be writing a try catch block to catch the out-of-range exception.

You are to write three functions and manipulate main() function for this lab all of which should be written in one main.cpp file:

## Part one:

**`unsigned min_index(const vector<T> &vals, unsigned index):`** Passes in an index of type int and a vector of type T (T could be string, double or int). The function returns the index of the min value starting from "index" to the end of the "vector".

**`selection_sort(vector<T> &vals):`** Passes in a vector of type T and sorts them based on the selection sort method. This function should utilize the min_index function to find the index of the min value in the unsorted portion of the vector.

## Part two:

**`T getElement(vector<T> vals, int index):`** Passes in a vector of type T (T could be string, double or int) and an index of type int. The function returns the element located at the index of the vals. You should write up a try catch block in main function so that when the index is out of the range of the vector, the "std::out*of*range" exception will be caught by the catch (const std::out*of*range& excpt). Once the exception is caught, it should output "out of range exception occured" followed by a new line.

You are given a function that creates a vector of characters with random size. You just need to put the following piece of code in your main.cpp file as is:

```
vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

```

Here is the main function you can use. You should add try/catch block to this function so that if index is out of range in calling getElement function, it should output "out of range exception occured" followed by a new line. You should include **`<stdexcept>`** library in your program which contains definitions for a set of standard exceptions.

```
int main(){

    //Part B
     srand(time(0));
     vector<char> vals = createVector();
     char curChar;
     int index;
     int numOfRuns = 10;
     while(--numOfRuns >= 0){
         cout << "Enter a number: " << endl;
         cin >> index;
         curChar = getElement(vals,index);
         cout << "Element located at " << index << ": is " << curChar << endl;
    }
    return 0;
}

```

You should come up with test harnesses to test your selection_sort function.

In this lab, you are going to write a template function that is capable of sorting vectors of characters, intgeres and strings
