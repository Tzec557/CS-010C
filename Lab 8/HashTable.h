#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <list>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include "WordEntry.h"


using namespace std;

class HashTable {

 private:
	list <WordEntry> *hashTable;
	int size;

 public:
	HashTable(int);
	~HashTable();
	bool contains(const string &) const;
	double getAverage(const string &) const;
	void put(const string &, int);
 
 private:
	int computeHash(const string &) const;

	// Copy constructor is private to prevent accidental copying of the list
    HashTable(const HashTable &);
    // Disabling the copy assignment operator
    HashTable& operator=(const HashTable&);
};

#endif