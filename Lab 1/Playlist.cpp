#include "Playlist.h"
#include <iostream>
#include <string>

using namespace std;

//PlaylistNode member function definitions

void PlaylistNode::InsertAfter(PlaylistNode* value){
    PlaylistNode* cur = nextNodePtr;
    nextNodePtr = value;
    value -> SetNext(cur);
}

void PlaylistNode::SetNext(PlaylistNode* nextNode){
    nextNodePtr = nextNode;

}

void PlaylistNode::PrintPlaylistNode() const{
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}


//Playlist member function definitions

Playlist::~Playlist() {
    PlaylistNode* cur = head;
    //traversing the list and deleting each node one by one.
    while (cur != nullptr) {
        PlaylistNode* next = cur->GetNext();
        delete cur;
        cur = next;
    }
}

void Playlist::PrintMenu(string title) const{
    cout << title << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl;
    cout << endl;
    cout << "Choose an option:" << endl;

}

void Playlist::OutputPlaylist() const{

    //check if the playlist is empty
    if(head == nullptr){
        cout << "Playlist is empty" << endl;
        cout << endl;
    }

    //if the playlist is not empty, run a loop through the playlist and output the detail of each song
    else{
        PlaylistNode* cur = head;
        //index number of each song in the playlist
        int playListNum = 1;

        while(cur != nullptr){
            cout << playListNum << "." << endl;
            cur -> PrintPlaylistNode();
            cout << endl;

            //move on to next node
            cur = cur -> GetNext();
            playListNum++;
        }
    }
}

void Playlist::AddSong(){
    string id;
    string name;
    string artist;
    int length;

    cout << "ADD SONG" << endl;
    cout << "Enter song's unique ID:" << endl;

    cin.ignore(); //ignore any newline characters left in the buffer
    getline(cin, id);

    cout << "Enter song's name:" << endl;
    getline(cin, name);

    cout << "Enter artist's name:" << endl;
    getline(cin, artist);

    cout << "Enter song's length (in seconds):" << endl;
    cin >> length;
    cout << endl;
    
    //create a new PlaylistNode object with the song information user entered
    PlaylistNode* newSong = new PlaylistNode(id, name, artist, length);

    //check the list is empty or not
    if(head == nullptr){
        //if so, set both the head and tail to the new song
        head = newSong;
        tail = newSong;
    }

    else{
        //if not, add the new song to the end of the playlist and change the tail
        tail -> SetNext(newSong);
        tail = newSong;
    }
    
}

void Playlist::RemoveSong(){
    string id;
    string name;

    cout << "REMOVE SONG" << endl;
    cout << "Enter song's unique ID:" << endl;

    cin.ignore();

    getline(cin, id);

    //check the list is empty or not
    if(head == nullptr){
        cout << "Playlist is empty" << endl;
    }

    else{
        PlaylistNode* pre = nullptr;
        PlaylistNode* cur = head;

        while(cur != nullptr){

            //check if the current song's id match
            if(cur -> GetID() == id){
                name = cur -> GetSongName();

                //check if the user want to remove the head
                if(head == cur){
                    if(head == tail){
                        head = nullptr;
                        tail = nullptr;
                    }

                    head = cur -> GetNext();
                    delete cur;
                    cur = head;
                    
                    cout << "\"" << name << "\" removed" << endl;
                    cout << endl;
                }

                //check if the user want to remove the tail
                else if(tail == cur){
                    tail = pre;
                }

                //normal case(remove the node between head and tail)
                else{
                    pre -> SetNext(cur -> GetNext());
                    delete cur;
                    cur =   pre -> GetNext();
                    
                    cout << "\"" << name << "\" removed." << endl;
                    cout << endl;
                }
            
            }
            
            //move on to the next node
            else{
                pre = cur;
                cur = cur -> GetNext();
            }
        }
        
    }
        
}

//helper function of ChangePosition, it can check how long is the list(find where is the tail)
int Playlist::GetListLength(PlaylistNode* head) const{
    int length = 0;
    PlaylistNode* cur = head;

    while(cur != nullptr){
        //increment the length counter for each node
        length ++;
        cur = cur -> GetNext();
    }

    return length;
}

void Playlist::ChangePosition(){
    int curPos;
    int newPos;
    string name;
    int count;

    // declare pointers to store previous and current nodes for current position
    PlaylistNode* preCurPos = nullptr;
    PlaylistNode* curCurPos = head;

    // declare pointers to store previous and current nodes for new position
    PlaylistNode* preNewPos = nullptr;
    PlaylistNode* curNewPos = head;

    //check if the list is empty
    if (head == nullptr) {
        cout << "Playlist is empty." << endl;
        return;
    }

    cout << "CHANGE POSITION OF SONG" << endl;
    cout << "Enter song's current position:" << endl;

    cin.ignore();

    cin >> curPos;

    //check if current position is within valid range
    if (curPos < 1 || curPos > GetListLength(head)) {
        cout << "Invalid position." << endl;
        return;
    }

    cout << "Enter new position for song:" << endl;
    cin >> newPos;

    //check if new position is within valid range
    if(newPos < 1){
        newPos = 1;
    }
    else if(newPos > GetListLength(head)){
        newPos = GetListLength(head);
    }

    //check if the song is already at that position
    if(newPos == curPos){
        return;
    }

    //find current position node 
    count = 1;
    while(curCurPos != nullptr && count < curPos){
        preCurPos = curCurPos;
        curCurPos = curCurPos -> GetNext();
        count++;
    }

    //find new position node
    count = 1;
    while(curNewPos != nullptr && count < newPos){
        preNewPos = curNewPos;
        curNewPos = curNewPos -> GetNext();
        count++;
    }

    //test case 1: Moving the head node
    if(curPos == 1){
        head = curCurPos->GetNext();
        curCurPos -> SetNext(curNewPos -> GetNext());
        curNewPos -> SetNext(curCurPos);

        //check if the tail node is affected
        if(curCurPos == tail){
            tail = preCurPos;
        }
    }

    //test case 2: Moving the tail node
    else if(curCurPos == tail){
        preNewPos -> SetNext(curCurPos);
        curCurPos -> SetNext(curNewPos);
        preCurPos -> SetNext(nullptr);
        tail = preCurPos;
        
    }
    //test case 3: Moving a node to the head
    else if(newPos == 1){
        preCurPos -> SetNext(curCurPos -> GetNext());
        curCurPos -> SetNext(head);
        head = curCurPos;
       
    }

    //test case 4: Moving a node to the tail
    else if(curNewPos == tail){
        preCurPos -> SetNext(preNewPos);
        curNewPos -> SetNext(curCurPos);
        curCurPos -> SetNext(nullptr);
        tail = curCurPos;
    }

    //test case 5: Moving a node down the list 
    else if(curPos < newPos){
        preCurPos -> SetNext(curCurPos -> GetNext());
        curCurPos -> SetNext(curNewPos -> GetNext());
        curNewPos -> SetNext(curCurPos);
        
    }

    //test case 6: Moving a node up the list
    else{
        preCurPos -> SetNext(curCurPos -> GetNext());
        curCurPos -> SetNext(curNewPos);
        preNewPos -> SetNext(curCurPos);
        
    }

    name = curCurPos -> GetSongName();
    cout << "\"" << name << "\" moved to position " << newPos << endl;
    cout << endl;
}


void Playlist::OutputByArtist() const{
    string name;
    
    cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
    cout << "Enter artist's name:" << endl;

    cin.ignore();

    getline(cin, name);
    cout << endl;

    PlaylistNode* cur = head;
    int playListNum = 1;

    while(cur != nullptr){
        //check if the current song's artist match
        if(cur -> GetArtistName() == name){
            cout << playListNum << "." << endl;
            cur -> PrintPlaylistNode();
            cout << endl;
        }

        //move on to the next node
        cur = cur -> GetNext();
        playListNum++;
    }
}

void Playlist::Totaltime() const{
    int time = 0;
    PlaylistNode* cur = head;

    cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;

    for(cur = head; cur != nullptr; cur = cur -> GetNext()){
        // add the length of each song in the playlist together
        time += cur -> GetSongLength();
    }

    cout << "Total time: " << time  << " seconds" << endl;
    cout << endl;
}