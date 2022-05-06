#include <song.hpp>
#include <ctime>

using namespace std;

namespace RDM {

    Song::Song(string title, string artist, string album)
        : title{ title }, artist{ artist }, album{ album } {
        id = ms_id++;
        updated_at = time(0);
    }

    uint32_t Song::ms_id = 1;

    const char* Song::keys[5]{ "id", "title", "artist", "album", "updated at" };

} // namespace RDM
