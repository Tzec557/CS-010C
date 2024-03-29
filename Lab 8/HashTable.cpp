#include "HashTable.h"
#include "WordEntry.h"

/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable (int s) {
	// set the input to be size
	size = s;
	// initialize array of lists of WordEntry
    hashTable = new list<WordEntry>[size];
}

HashTable::~HashTable(){
	// deallocate the dynamically allocated array
	delete[] hashTable;
}


/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to 
*  ensure array index doesn't go out of bounds
*/
int HashTable::computeHash(const string &str) const{
	// compute the hash value based on the size of the string and the size of the array
    return str.size() % size;
}

/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
void HashTable::put(const string &str, int score) {
	// compute the hash value for the given string
	int index = computeHash(str);
	// check if the string already exists in the hash table
    if(contains(str)) {
		// iterate over the WordEntry objects in the list at the computed index
	 	for(auto i = hashTable[index].begin(); i != hashTable[index].end(); i++) {
			// check if the current WordEntry object has a matching word
	 		if(i->getWord() == str) {
				// add a new appearance with the given score to the WordEntry
	 			i->addNewAppearance(score);
	 		}
	 	}
	}
	else {
		// create a new WordEntry object with the given string and score
	 	WordEntry newEntry(str, score);
		// insert the new WordEntry at the back of the list at the computed index
	 	hashTable[index].push_back(newEntry);
	}
}

/* getAverage
*  input: string word 
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/
double HashTable::getAverage(const string &str) const{
	// compute the hash value for the given string
    int index = computeHash(str);
	// iterate over the WordEntry objects in the list at the computed index
	for (auto i = hashTable[index].begin(); i != hashTable[index].end(); i++) {
		// check if the current WordEntry object has a matching word
		if (i->getWord() == str) {
			// return the average score from the matching WordEntry
			return i->getAverage();
		}
	}
	// return a default value of 2.0 (neutral result) if the string is not found
	return 2.0;
}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
bool HashTable::contains(const string &str) const{
	// compute the hash value for the given string
    int index = computeHash(str);
	// iterate over the WordEntry objects in the list at the computed index
	for (auto i = hashTable[index].begin(); i != hashTable[index].end(); i++) {
		// check if the current WordEntry object has a matching word
		if (i->getWord() == str) {
			return true;
		}
	}
	return false;
}


int main() {
	// declare a few needed variables for inputing the data
	string line;    
	int score;
	string message = " ";
	
	// open input file
	ifstream myfile("movieReviews.txt");
	if (myfile.fail()) {
	    cout << "could not open file" << endl;
	    exit(1);
	}
	
	//create hash table
	HashTable table(20071);
	
	while (!myfile.eof()) {
	    myfile >> score;     // get score
	    myfile.get();        // get blank space
	    getline(myfile, line);
	    int len = line.size();
	    while(len > 0) {     // identify all individual strings
	        string sub;
	        len = line.find(" ");
	        if (len > 0) {
	            sub = line.substr(0, len);
	            line = line.substr(len + 1, line.size());
	        }
	        else {
	            sub = line.substr(0, line.size() - 1);
	        }
	        table.put(sub, score); // insert string with the score
	    }
	}
	
	// after data is entered in hash function
	// prompt user for a new movie review
	while(message.length() > 0) {
	    cout << "enter a review -- Press return to exit: " << endl;
	    getline(cin, message);
	
	    // used for calculating the average
	    double sum = 0;
	    int count = 0;
	    
	    double sentiment = 0.0;
	    
	    size_t len = message.size();
	    // get each individual word from the input
	    while(len != string::npos) {
	        string sub;
	        len = message.find(" ");
	        if (len != string::npos) {
	            sub = message.substr(0, len);
	            message = message.substr(len + 1, message.size());
	        }
	        else {
	            sub = message;
	        }
	        // calculate the score of each word
	        sum += table.getAverage(sub);
	        ++count;
	    }
	
	    if (message.size() > 0) {
			// calculate the average sentiment value
	    	sentiment = sum / count;
			// display the average sentiment value
	        cout << "The review has an average value of " << sentiment << endl;
			// determine the sentiment label based on the average value
	        if (sentiment >= 3.0) {
	        	cout << "Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 2.0) {
	        	cout << "Somewhat Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 1.0) {
	        	cout << "Somewhat Negative Sentiment" << endl;
	        }
	        else {
	        	cout << "Negative Sentiment" << endl;
	        }
	        cout << endl;
	    }
	}
	
	return 0;
}