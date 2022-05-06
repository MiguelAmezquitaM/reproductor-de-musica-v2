#pragma once
#include <string>

namespace RDM {

    struct Song {
    public:
        Song(std::string title, std::string artist, std::string album);
        Song() = default;

        static const char* keys[5];
    public:
        std::string title;
        std::string artist;
        std::string album;
        time_t updated_at;
        uint32_t id;
        bool is_favorite{ false };
    public:
        static uint32_t ms_id;
    };

}