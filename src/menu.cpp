// funciones del menu
#include <menu.hpp>
#include <iostream>
#include <iomanip>

using namespace std;

namespace RDM {

    void mainMenu() {
        int option;
        Reproducer unimagMusic;

        unimagMusic.add_song({ "Lost in Paradise", "Eve", "Kaikai kitan" });
        unimagMusic.add_song({ "Despacito", "Luis Fonsi", "Singles" });
        unimagMusic.add_song({ "Bad guy", "Billie Ellish", "When we're fall sleep" });

        do {
        clearConsole();
        cout << "=====================================\n";
        cout << "           Select a Option\n";
        cout << "=====================================\n\n";

        unimagMusic.show_playing_songs();
        cout << "\n";

        cout << " 1. Add a song\n";
        cout << " 2. Add a song to favorites\n";
        cout << " 3. Play a song\n";
        cout << " 4. Play songs favorites\n";
        cout << " 5. Show songs\n";
        cout << " 6. Show songs favorites\n";
        cout << " 7. Play next\n";
        cout << " 8. Play previous\n";
        cout << " 9. Play a random song\n";
        cout << "10. Edit data of a song\n";
        cout << "11. Remove a song\n";
        cout << "12. Remove a song from favorites\n";
        cout << "13. Sort list\n";
        cout << "14. Exit\n";

        cout << "\nYour Option: ";
        cin >> option;
        cin.ignore();

        switch (option) {
        case 1:
            addSong(unimagMusic);
            break;
        case 2:
            addSongToFavorites(unimagMusic);
            break;
        case 3:
            playSong(unimagMusic);
            break;
        case 4:
            playFavoriteSongs(unimagMusic);
            break;
        case 5:
            showSongs(unimagMusic);
            break;
        case 6:
            showFavoriteSongs(unimagMusic);
            break;
        case 7:
            try { unimagMusic.play_next(); }
            catch (logic_error e) { clearConsole(); cout << e.what() << endl; pause(); }
            break;
        case 8:
            try { unimagMusic.play_prev(); }
            catch (logic_error e) { clearConsole(); cout << e.what() << endl; pause(); }
            break;
        case 9:
            try { unimagMusic.play_random(); }
            catch (logic_error e) { clearConsole(); cout << e.what() << endl; pause(); }
            break;
        case 10:
            editSong(unimagMusic);
            break;
        case 11:
            removeSongs(unimagMusic);
            break;
        case 12:
            removeSongFromFavorites(unimagMusic);
            break;
        case 13:
            sortSongList(unimagMusic);
            break;
        case 14:
            return; // Exit success
        default:
            break;
        }
        } while (true); // Infinite loop
        
    }

    void clearConsole() {
#ifdef _WIN32  
        system("cls"); // Pa windows
#else
        system("clear"); // Pa linux
#endif
    }

    void pause() {
        string temp;
        cout << "\nPress Enter to Continue...";
        getline(cin, temp, '\n');
    }

    bool printSongs(Reproducer& mr) {
        try {
            mr.list_songs();
        }
        catch (logic_error& e) {
            cout << e.what() << endl;
            pause();
            return false;
        }
        return true;
    }

    void addSong(Reproducer& mr) {
        string title;
        string artist;
        string album;
        clearConsole();
        cout << "Title: ";
        getline(cin, title, '\n');

        cout << "Artist: ";
        getline(cin, artist, '\n');

        cout << "Album: ";
        getline(cin, album, '\n');

        mr.add_song(Song(title, artist, album));
        cout << "\nSong added!\n";
        pause();
    }

    void addSongToFavorites(Reproducer& mr) {
        int id;
        clearConsole();

        if (!printSongs(mr)) {
            return;
        }

        cout << "Input ID of song: ";
        cin >> id;
        cin.ignore();

        try {
            mr.add_song_to_favorites(id);
        }
        catch (logic_error& e) {
            cout << e.what() << endl;
            pause();
        }
    }

    void playSong(Reproducer& mr) {
        int id;
        clearConsole();
        if (!printSongs(mr)) {
            return;
        }

        cout << "Input ID if song: ";
        cin >> id;

        try {
            mr.play_song(id);
        }
        catch (logic_error& e) {
            cout << e.what() << endl;
        }

        pause();
    }

    void playFavoriteSongs(Reproducer& mr) {
        clearConsole();
        try {
            mr.play_favorites();
        }
        catch (logic_error& e) {
            cout << e.what() << "\n";
            pause();
        }
    }

    void showSongs(Reproducer& mr) {
        clearConsole();

        try {
            mr.list_songs();
        }
        catch (logic_error& e) {
            cout << e.what() << "\n";
        }

        pause();
    }

    void showFavoriteSongs(Reproducer& mr) {
        clearConsole();

        try {
            mr.list_favorite_songs();
        }
        catch (logic_error& e) {
            cout << e.what() << "\n";
        }

        pause();
    }

    void editSong(Reproducer& mr) {
        int id;
        Song* song;
        clearConsole();

        if (!printSongs(mr)) {
            return;
        }

        cout << "Input ID of song: ";
        cin >> id;
        cin.ignore();
        cout << "\n\n";

        try {
            song = &mr.get_song(id);
        }
        catch (logic_error& e) {
            cout << e.what() << endl;
            pause();
            return;
        }

        cout << "Olg title: " << song->title << "\n";
        cout << "New title: ";
        getline(cin, song->title, '\n');

        cout << "\nOld artist: " << song->artist << "\n";
        cout << "New artist: ";
        getline(cin, song->artist, '\n');

        cout << "\nOld album: " << song->album << "\n";
        cout << "New album: ";
        getline(cin, song->album, '\n');

        song->updated_at = time(0);

        cout << "\nModified sucessfully!\n";
        pause();
    }

    void sortSongList(Reproducer& mr) {
        int option;
        clearConsole();
        cout << "=============================\n";
        cout << "          Sort by\n";
        cout << "=============================\n\n";

        cout << "1. Title\n";
        cout << "2. Artist\n";
        cout << "3. Updated at\n";
        cout << "4. Back to menu\n\n";

        cout << "Your option: ";
        cin >> option;
        cin.ignore();

        switch (option) {
        case 1:
            mr.sort_by_title();
            break;
        case 2:
            mr.sort_by_artist();
            break;
        case 3:
            mr.sort_by_updated_at();
            break;
        default:
            return;
        }

        cout << "\nSorted Sucessfully!\n";
        pause();
    }


    void removeSongs(Reproducer& mr) {
        int id;
        clearConsole();
        if (!printSongs(mr)) {
            return;
        }

        cout << "\nInput the ID: ";
        cin >> id;

        try {
            mr.remove_song(id);
        }
        catch (logic_error& e) {
            cout << e.what() << endl;
        }
    }

    void removeSongFromFavorites(Reproducer& mr) {
        int id;
        clearConsole();

        try {
            mr.list_favorite_songs();
        }
        catch (logic_error& e) {
            cout << e.what() << endl;
            pause();
            return;
        }

        cout << "\nInput the ID: ";
        cin >> id;

        try {
            mr.remove_favorite(id);
        }
        catch (logic_error& e) {
            cout << e.what() << endl;
        }
    }

}