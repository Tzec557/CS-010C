#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <string>

using namespace std;

class PlaylistNode {
    public:
        //constructor
        PlaylistNode(): uniqueID("none"), songName("none"), artistName("none"), songLength(0), nextNodePtr(nullptr) {}
        PlaylistNode(string id, string name, string artist, int length): uniqueID(id), songName(name), artistName(artist), songLength(length), nextNodePtr(nullptr) {}
        
        //accessor
        const string& GetID() const{
            return uniqueID;
        }

        const string& GetSongName() const{
            return songName;
        }

        const string& GetArtistName() const{
            return artistName;
        }

        int GetSongLength() const{
            return songLength;
        }

        PlaylistNode* GetNext() const{
            return nextNodePtr;
        }

        //mutator
        void SetNext(PlaylistNode*);

        void InsertAfter(PlaylistNode*);
        void PrintPlaylistNode() const;
       
    private:
        string uniqueID;
        string songName;
        string artistName;
        int songLength;
        PlaylistNode* nextNodePtr;
};

class Playlist {
    public:
        //constructor and destructor
        Playlist() : head(nullptr), tail(nullptr) {}
        ~Playlist();

        void PrintMenu(string title) const;
        void OutputPlaylist() const;

        void AddSong();
        void RemoveSong();
        int GetListLength(PlaylistNode* head) const;
        void ChangePosition();

        void OutputByArtist() const;
        void Totaltime() const;
    
    private:
        //copy constructor
        Playlist(const Playlist&);
        
        PlaylistNode* head;
        PlaylistNode* tail;
};

#endif