#pragma once
#include <list.hpp>
#include <song.hpp>
#include <cstdint>
#include <iomanip>

namespace RDM {

    class Reproducer {
    public:
        void add_song(const Song& new_song);
        void add_song_to_favorites(const uint32_t id);

        void list_songs() const;
        void list_favorite_songs() const;
        void show_playing_songs() const;
        Song& get_song(const uint32_t id) const;

        void play_song(const uint32_t id);
        void play_favorites();
        void play_next();
        void play_prev();
        void play_random();

        void remove_favorite(const uint32_t id);
        void remove_song(const uint32_t id);
        
        void sort_by_id();
        void sort_by_artist();
        void sort_by_title();
        void sort_by_album();
        void sort_by_updated_at();

        bool has_favorites() const;
        bool has_songs() const;

    private:
        list<Song> m_songs;
        list<Song>::node* m_playing_song{ nullptr };
        bool only_favorites{ false };

        list<Song>::node* get_node_by_id(const uint32_t id) const;
        uint32_t get_index_by_id(const uint32_t id) const;
        static void m_print_keys();
        static void m_print_song(const Song& song);
        static const std::_Setw WIDTH;
        static const std::_Setw INITIAL_WIDTH;
        static const char* NoReproducingError;
        static const char* NoFavoritesSong;
    };

}