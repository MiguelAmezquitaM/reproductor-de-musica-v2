#pragma once

#include <reproducer.hpp>

namespace RDM {

    void mainMenu();

    void addSong(Reproducer& mr);
    void addSongToFavorites(Reproducer& mr);
    void showSongs(Reproducer& mr);
    void showFavoriteSongs(Reproducer& mr);
    void playSong(Reproducer& mr);
    void playFavoriteSongs(Reproducer& mr);
    void removeSongs(Reproducer& mr);
    void removeSongFromFavorites(Reproducer& mr);
    void editSong(Reproducer& mr);
    void sortSongList(Reproducer& mr);

    bool printSongs(Reproducer& mr);

    void clearConsole();
    void pause();
}