#include <iostream>
#include <cstdlib>

using namespace std;

const int NUMBERS_SIZE = 50000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds

int genRandInt(int low, int high);
void fillArrays(int arr1[], int arr2[],int arr3[]);
void Quicksort_midpoint(int numbers[], int i, int k);
int Partition_midpoint(int numbers[], int lowIndex, int highIndex);
void Quicksort_medianOfThree(int numbers[], int i, int k);
int median(int left, int mid, int right);
int Partition_medianOfThree(int numbers[], int lowIndex, int highIndex);
void InsertionSort(int numbers[], int numbersSize);

int main(){
    srand(time(nullptr));
	
	int arr1[NUMBERS_SIZE];
	int arr2[NUMBERS_SIZE];
	int arr3[NUMBERS_SIZE];
	
	fillArrays(arr1, arr2, arr3);

    // measure the elapsed time for Quicksort with midpoint pivot
    clock_t start = clock();
    Quicksort_midpoint(arr1, 0, NUMBERS_SIZE);
    clock_t end = clock();
    int elapsedTime = (end - start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "elapsedTime: " << elapsedTime << " ms" << endl;

    // measure the elapsed time for Quicksort with median-of-three pivot
    start = clock();
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE);
    end = clock();
    elapsedTime = (end - start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "elapsedTime: " << elapsedTime << " ms" << endl;

    // measure the elapsed time for Insertion Sort
    start = clock();
    InsertionSort(arr3, NUMBERS_SIZE);
    end = clock();
    elapsedTime = (end - start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "elapsedTime: " << elapsedTime << " ms" << endl;

    return 0;
}

// generates a random integer between the low and high values
int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}
// fills three arrays with random integers
void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; i++){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

void Quicksort_midpoint(int numbers[], int i, int k){
    // if the range is empty or has only one element, return
    if(i >= k){
        return;
    }
    // partition the array using the midpoint as the pivot
    int lowEndIndex = Partition_midpoint(numbers, i, k);
    // recursively sort the two partitions
    Quicksort_midpoint(numbers, i, lowEndIndex);
    Quicksort_midpoint(numbers, lowEndIndex + 1, k);
}

int Partition_midpoint(int numbers[], int lowIndex, int highIndex) {
    // pick middle element as pivot
    int midpoint = (lowIndex + highIndex)/2;
    int pivot = numbers[midpoint];
   
    bool done = false;
    while (!done) {
        // increment lowIndex while numbers[lowIndex] < pivot
        while (numbers[lowIndex] < pivot) {
            lowIndex += 1;
        }
    
        // decrement highIndex while pivot < numbers[highIndex]
        while (pivot < numbers[highIndex]) {
            highIndex -= 1;
        }
      
        // if zero or one elements remain, then all numbers are 
        // partitioned. Return highIndex.
        if (lowIndex >= highIndex) {
            done = true;
        }
        else {
            // swap numbers[lowIndex] and numbers[highIndex]
            int storeValue = numbers[lowIndex];
            numbers[lowIndex] = numbers[highIndex];
            numbers[highIndex] = storeValue;
         
            // update lowIndex and highIndex
            lowIndex += 1;
            highIndex -= 1;
        }
    }
    return highIndex;
}

void Quicksort_medianOfThree(int numbers[], int i, int k){
    // if the range is empty or has only one element, return
    if(i >= k){
        return;
    }
    // partition the array using the median of three as the pivot
    int lowEndIndex = Partition_medianOfThree(numbers, i, k);
    // recursively sort the two partitions
    Quicksort_medianOfThree(numbers, i, lowEndIndex);
    Quicksort_medianOfThree(numbers, lowEndIndex + 1, k);
}

// retrun the median value among the left, middle and right elememts
int median(int left, int mid, int right) {
	if (left > mid) {
		if (mid > right) {
			return mid;
		}
		else if (left > right) {
			return right;
		}
		else {
			return left;
		}
	}
	else {
		if (left > right) {
			return left;
		}
		else if (mid > right) {
			return right;
		}
		else {
			return mid;
		}
	}
}

int Partition_medianOfThree(int numbers[], int lowIndex, int highIndex) {
    // Pick median element as pivot
    int midpoint = (lowIndex + highIndex)/2;
    int pivot = median(numbers[lowIndex], numbers[midpoint], numbers[highIndex]);

    bool done = false;
    while (!done) {
        // increment lowIndex while numbers[lowIndex] < pivot
        while (numbers[lowIndex] < pivot) {
            lowIndex += 1;
        }
      
        // decrement highIndex while pivot < numbers[highIndex]
        while (pivot < numbers[highIndex]) {
            highIndex -= 1;
        }
      
        // if zero or one elements remain, then all numbers are 
        // partitioned. Return highIndex.
        if (lowIndex >= highIndex) {
            done = true;
        }
        else {
            // swap numbers[lowIndex] and numbers[highIndex]
            int storeValue = numbers[lowIndex];
            numbers[lowIndex] = numbers[highIndex];
            numbers[highIndex] = storeValue;
         
            // update lowIndex and highIndex
            lowIndex += 1;
            highIndex -= 1;
        }
    }
    return highIndex;
}

void InsertionSort(int numbers[], int numbersSize){
    int i = 0;
    int j = 0;
    int storeValue = 0;  // temporary variable for swap
   
    for (i = 1; i < numbersSize; i++) {
        j = i;
        // insert numbers[i] into sorted part
        // stopping once numbers[i] in correct position
        while (j > 0 && numbers[j] < numbers[j - 1]) {
            // swap numbers[j] and numbers[j - 1]
            storeValue = numbers[j];
            numbers[j] = numbers[j - 1];
            numbers[j - 1] = storeValue;
            j--;
      }
    }
}