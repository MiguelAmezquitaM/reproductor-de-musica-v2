#include <reproducer.hpp>
#include <stdexcept>
#include <iostream>
#include <ctime>

using namespace std;

namespace RDM {

    static inline string DontExistSongError(uint32_t id) {
        return "Don't exist a song with id = " + to_string(id);
    }

    void Reproducer::add_song(const Song& new_song) {
        m_songs.push_back(new_song);
    }

    void Reproducer::add_song_to_favorites(const uint32_t id) {
        get_song(id).is_favorite = true;
    }

    void Reproducer::list_songs() const {
        if (m_songs.is_empty()) {
            cout << "No Songs\n"; return;
        }

        m_print_keys();
        for (const auto& song : m_songs) {
            m_print_song(song);
        }
    }

    void Reproducer::list_favorite_songs() const {
        if (!has_favorites()) {
            cout << "No favorite songs\n";
            return;
        }

        m_print_keys();
        for (const auto& song : m_songs) {
            if (song.is_favorite)
                m_print_song(song);
        }
    }

    Song& Reproducer::get_song(const uint32_t id) const {
        auto song = get_node_by_id(id);
        if (!song) throw logic_error(DontExistSongError(id));
        return song->value;
    }

    void Reproducer::play_song(const uint32_t id) {
        m_playing_song = get_node_by_id(id);
        only_favorites = false;
        if (!m_playing_song) throw logic_error(DontExistSongError(id));
    }

    void Reproducer::play_favorites() {
        if (!has_favorites()) throw logic_error(NoFavoritesSong);
        for (auto song : m_songs) {
            if (song.is_favorite) {
                m_playing_song = get_node_by_id(song.id);
                only_favorites = true;
            }
        }
    }

    void Reproducer::play_next() {
        if (!m_playing_song) throw logic_error(NoReproducingError);

        if (only_favorites) {
            do {
                m_playing_song = m_playing_song->next;
            } while (!m_playing_song->value.is_favorite);
        }
        else m_playing_song = (m_playing_song->next == m_songs.end().get_node() ? m_playing_song->next->next : m_playing_song->next);
    }

    void Reproducer::play_prev() {
        if (!m_playing_song) throw logic_error(NoReproducingError);

        if (only_favorites) {
            do {
                m_playing_song = m_playing_song->prev;
            } while (!m_playing_song->value.is_favorite);
        }
        else m_playing_song = (m_playing_song->prev == m_songs.end().get_node() ? m_playing_song->prev->prev : m_playing_song->prev);
    }

    void Reproducer::play_random() {
        only_favorites = false;

        srand(time(0));
        m_playing_song = m_songs.get_node(rand() % m_songs.size());
    }

    void Reproducer::remove_favorite(const uint32_t id) {
        auto song_node = get_node_by_id(id);
        if (!song_node or !song_node->value.is_favorite)
            throw logic_error(DontExistSongError(id));

        song_node->value.is_favorite = false;
        if (only_favorites and m_playing_song->value.id == id) { m_playing_song = nullptr; }
    }

    void Reproducer::remove_song(const uint32_t id) {
        if (m_playing_song and m_playing_song->value.id == id)
            m_playing_song = nullptr;

        auto index = get_index_by_id(id);

        if (index == uint32_t(-1)) throw logic_error(DontExistSongError(id));

        m_songs.remove_at(index);
    }

    bool Reproducer::has_favorites() const {
        bool has_favorites = false;

        for (const auto& song : m_songs)
            if (song.is_favorite) { has_favorites = true; break; }

        return has_favorites;
    }

    bool Reproducer::has_songs() const {
        return !m_songs.is_empty();
    }


    void Reproducer::sort_by_updated_at() {
        for (auto i = m_songs.begin(); i != m_songs.end(); i++) {
            for (auto j = m_songs.begin(); j != --m_songs.end(); j++) {
                if ((*j).updated_at < j.get_node()->next->value.updated_at) {
                    swap((*j), j.get_node()->next->value);
                }
            }
        }
    }

    void Reproducer::sort_by_artist() {
        for (auto i = m_songs.begin(); i != m_songs.end(); i++) {
            for (auto j = m_songs.begin(); j != --m_songs.end(); j++) {
                if ((*j).artist > j.get_node()->next->value.artist) {
                    swap((*j), j.get_node()->next->value);
                }
            }
        }
    }
    void Reproducer::sort_by_title() {
        for (auto i = m_songs.begin(); i != m_songs.end(); i++) {
            for (auto j = m_songs.begin(); j != --m_songs.end(); j++) {
                if ((*j).title > j.get_node()->next->value.title) {
                    swap((*j), j.get_node()->next->value);
                }
            }
        }
    }

    void Reproducer::sort_by_id() {
        for (auto i = m_songs.begin(); i != m_songs.end(); i++) {
            for (auto j = m_songs.begin(); j != --m_songs.end(); j++) {
                if ((*j).id > j.get_node()->next->value.id) {
                    swap((*j), j.get_node()->next->value);
                }
            }
        }
    }

    void Reproducer::sort_by_album() {
        for (auto i = m_songs.begin(); i != m_songs.end(); i++) {
            for (auto j = m_songs.begin(); j != --m_songs.end(); j++) {
                if ((*j).album > j.get_node()->next->value.album) {
                    swap((*j), j.get_node()->next->value);
                }
            }
        }
    }

    list<Song>::node* Reproducer::get_node_by_id(const uint32_t id) const {
        for (auto i = m_songs.begin(); i != m_songs.end(); i++) {
            if (i.get_node()->value.id == id) {
                return i.get_node();
            }
        }
        return nullptr;
    }

    uint32_t Reproducer::get_index_by_id(const uint32_t id) const {
        int j = 0;
        for (auto i = m_songs.begin(); i != m_songs.end(); i++, j++) {
            if (i.get_node()->value.id == id) {
                return j;
            }
        }
        return -1;
    }

    void Reproducer::show_playing_songs() const {
        if (m_playing_song)
            cout << "Playing '" << m_playing_song->value.title << "' of '" << m_playing_song->value.artist << "'\n";
        else
            cout << "No playing songs\n";
    }

    void Reproducer::m_print_keys() {
        cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << INITIAL_WIDTH;
        for (auto& key : Song::keys) {
            cout << key << WIDTH;
        }
        cout << "\n-------------------------------------------------------------------------------------------------------------------------------------\n";
    }

    string format_time(const time_t& timer) {
        string time_passed;
        time_t time_past = time(0) - timer;
        if (time_past > 3600) time_passed = to_string(time_past / 3600) + " hours left";
        else if (time_past > 60) time_passed = to_string(time_past / 60) + " minutes left";
        else time_passed = to_string(time_past) + " seconds left";
        return time_passed;
    }

    void Reproducer::m_print_song(const Song& song) {
        cout << INITIAL_WIDTH << song.id << WIDTH << song.title << WIDTH << song.artist << WIDTH << song.album << WIDTH << format_time(song.updated_at) << endl;
    }

    const _Setw Reproducer::INITIAL_WIDTH = setw(5);
    const _Setw Reproducer::WIDTH = setw(32);
    const char* Reproducer::NoReproducingError = "No song is playing";
    const char* Reproducer::NoFavoritesSong = "No favorites songs";
}
