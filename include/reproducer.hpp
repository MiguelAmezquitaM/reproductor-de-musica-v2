#pragma once
#include <list.hpp>
#include <song.hpp>
#include <cstdint>
#include <iomanip>

namespace RDM {
    /*
     * class Reproducer is the manager of
     * a list of songs concrete
     */
    class Reproducer {
    public:
        // Insertion functions
        void add_song(const Song& new_song);
        void add_song_to_favorites(const uint32_t id);

        // Fetching data functions
        void list_songs()                   const;
        void list_favorite_songs()          const;
        void show_playing_songs()           const;
        Song& get_song(const uint32_t id)   const;

        // Player functions
        void play_song(const uint32_t id);
        void play_favorites();
        void play_next();
        void play_prev();
        void play_random();

        // Remove song functions
        void remove_favorite(const uint32_t id);
        void remove_song(const uint32_t id);

        // Sorting functions
        void sort_by_id();
        void sort_by_artist();
        void sort_by_title();
        void sort_by_album();
        void sort_by_updated_at();

        // Comprobating functions
        bool has_favorites() const;
        bool has_songs()     const;

    private:
        list<Song>::node* m_playing_song{ nullptr };
        list<Song> m_songs;
        bool only_favorites{ false };

        // utils functions
        list<Song>::node*   get_node_by_id(const uint32_t id)   const;
        uint32_t            get_index_by_id(const uint32_t id)  const;
        
        static void         m_print_song(const Song& song);
        static void         m_print_keys();

        // Spacing in console
        static const std::_Setw WIDTH;
        static const std::_Setw INITIAL_WIDTH;

        // Error messages
        static const char* NoReproducingError;
        static const char* NoFavoritesSong;
    };

}