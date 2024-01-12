#include<iostream>
#include<vector>
#include<stdexcept>

using namespace std;

// define a template for genertic type T
template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index){
    // initialize min to given index
    unsigned min = index;
    for(unsigned i = index + 1; i < vals.size(); i++){
        // if the current element is smaller than the minimum
        if(vals.at(i) < vals.at(min)){
            // update the minimum index
            min = i;
        }
    }
    // return minimum index
    return min;
}

template<typename T>
void selection_sort(vector<T> &vals){
    for(unsigned i = 0; i < vals.size(); i++){
        // set the minimum index to the current index
        unsigned min = i;
        for(unsigned j = i + 1; j < vals.size(); j++){
            // if the current element is smaller than minimum
            if(vals.at(j) < vals.at(min)){
                // update the minimum index
                min = j;
            }
        }
        // if the minimum index has changed
        if(min != i){
            // swap the minimum element with the current element
            swap(vals.at(min), vals.at(i));
        }
    }
}

template<typename T>
T getElement(vector<T> vals, unsigned index){
    // if the index is smaller than 0 or greater than size
    if(index < 0 || index >= vals.size()){
        // throw an out of range expection with an error message
        throw out_of_range("out of range exception occured");
    }
    // return the element at given index
    return vals.at(index);
}

vector<char> createVector(){
    // generate a random vector size between 0 and 25
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++){
        // add the current character to the vector
        vals.push_back(c);
        // increment the character
        c++;
    }
    return vals;
}

int main(){
    // Part B

    // seed the random number generator
    srand(time(0));

    vector<char> vals = createVector();
    char curChar;
    int index;
    int numOfRuns = 10;

    while(--numOfRuns >= 0){
        cout << "Enter a number: " << endl;
        cin >> index;

        // start a try block to catch out of range expections
        try{
            // set curChar to element at the given index
            curChar = getElement(vals,index);
        }
        // if an out of range expection occurs
        catch(out_of_range& excpt){
            // output error message
            cout << excpt.what() << endl;
        }
         
        cout << "Element located at " << index << ": is " << curChar << endl;
    }

    // test harness for selection_sort function

    // test case 1 sort integers
    vector<int> nums1 = {3, 6, 2, 8, 4};
    selection_sort(nums1);

    // test case 2 sort doubles
    vector<double> nums2 = {3.12, 1.72, 2.90, 8.12, 4.23};
    selection_sort(nums2);

    // test case 3 sort string
    vector<string> nums3 = {"dog", "bird", "cat", "ant"};
    selection_sort(nums3);

    // output each element in vector check if they art sorted
    for(unsigned i = 0; i < nums1.size(); i++){
        cout << nums1.at(i) << " ";
    }
    cout << endl;

    for(unsigned i = 0; i < nums2.size(); i++){
        cout << nums2.at(i) << " ";
    }
    cout << endl;

    for(unsigned i = 0; i < nums3.size(); i++){
        cout << nums3.at(i) << " ";
    }
    cout << endl;

    return 0;
}

