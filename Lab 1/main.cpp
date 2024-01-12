#include "Playlist.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
    string title;
    char userchoice;

    Playlist list;

    //prompt user to enter title
    cout << "Enter playlist's title:" << endl;
    cout << endl;
    getline(cin, title);

    list.PrintMenu(title);
    cin >> userchoice;

    while (userchoice != 'q'){

        if(userchoice == 'a'){
            //add a new song
            list.AddSong();
        }

        else if(userchoice == 'd'){
            //remove a song
            list.RemoveSong();
        }

        else if(userchoice == 'c'){
            //change the position of a song
            list.ChangePosition();
        }

        else if(userchoice == 's'){
            //output the songs by artist name
            list.OutputByArtist();
        }

        else if(userchoice == 't'){
            //calculate the total time of the playlist
            list.Totaltime();
        }

        else if(userchoice == 'o'){
            cout << title << " - OUTPUT FULL PLAYLIST" << endl;
            //output the full playlist
            list.OutputPlaylist();
        }

        else{
            //if an invalid choice is entered, display the menu again
            cout << "Enter playlist's title:" << endl;
            getline(cin, title);
            list.PrintMenu(title);
            cin >> userchoice;
        }
        
        list.PrintMenu(title);
        cin >> userchoice;
    }
        
   
   return 0;
}


