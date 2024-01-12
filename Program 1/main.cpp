#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//2.28: PROGRAM 1: Josephus Problem

struct Node {
    string payload;
    Node* next;
};

// Create a new node with given payload
Node* newNode(string payload) {
    Node* newPlayer = new Node;
    newPlayer -> payload = payload;
    newPlayer -> next = nullptr;
    return newPlayer;
}

// Load the game by creating a circular linked list of players
Node* loadGame(int n, vector<string> names) {
    Node* head = nullptr;
    Node* prev = nullptr;
    string name;

    for (int i = 0; i < n; ++i) {
        name = names.at(i);
        // Check if the list is empty
        if (head == nullptr) {
            // Initialize head specially
            head = newNode(name); 
            prev = head;
        } 
        else {
            // Set newnode and set it as the next node
            prev->next = newNode(name);
            // Update prev to point to the new node
            prev = prev -> next;
        }
    }

    if (prev != nullptr) {
        // Make the list circular by setting the next pointer of the last node to the head
        prev -> next = head; 
    }

    return head;
}

void print(Node* start) { 
    Node* curr = start;
    while (curr != nullptr) {
        cout << curr->payload << endl;
        curr = curr->next;

        if (curr == start) {
            // exit circular list
            break; 
        }
    }
}

// Run the Josephus game on a circular linked list with k skips
Node* runGame(Node* start, int k) { 
    Node* curr = start;
    Node* prev = curr;
    // Exit condition, last person standing
    while (curr -> next != curr) { 
        // Find kth node
        for (int i = 0; i < k; ++i) { 
          prev = curr;   
          curr = curr -> next;
        }

        // Delete kth node
        prev -> next = curr -> next;
        delete curr;
        curr = prev -> next;
    }

    // Last person standing
    return curr; 
}

/* Driver program to test above functions */
int main() {
    // n = num names; k = num skips (minus 1)
    int n = 1, k = 1; 
    string name;
    vector<string> names;

    // Get inputs
    cin >> n >> k;

    // EOF or . ends input
    while (cin >> name && name != ".") { 
        names.push_back(name); 
    } 

    // Initialize and run game
    Node* startPerson = loadGame(n, names);
    Node* lastPerson = runGame(startPerson, k);

    if (lastPerson != nullptr) {
        cout << lastPerson->payload << " wins!" << endl;
    } 
    else {
        cout << "error: null game" << endl;
    }

    return 0;
}

