//
// Created by Jamie on 25/11/2019.
//

#ifndef INTERVIEW_SERVICE_SONGS_H
#define INTERVIEW_SERVICE_SONGS_H

#include <mutex>
#include <ctime>
#include <map>

#include "nlohmann/json.hpp"

class songs {

public:

    songs();

    nlohmann::json getCurrentSongDetails(const nlohmann::json&);

    nlohmann::json getCurrentSongVoteDetails(const nlohmann::json&);

    nlohmann::json setVote(const nlohmann::json&);


    void changeSong();

    void resetVotes();

    //Starts the songs background service
    void start();

    //stops the songs background service
    void stop();
private:

    struct client {
        enum Vote {
            VOTE_START = -2,
            Negative = -1,
            Neutral = 0,
            Positive = 1,
            VOTE_END = 2,

        };

        client() {
            m_vote = Neutral;
            time(&m_lastUpdate);
        }

        Vote        m_vote;         //Contains the vote of this client
        std::time_t m_lastUpdate;   //Contains time of last update
    };

    std::map<std::string, client> m_voteList;

    //This contains the main loop thread
    std::thread* m_program;

    std::mutex m_updating;

    bool m_quit = false;

    int             m_currentSong    = 0;



    //Songs
    int m_timeLeftInSong = 0;

    void mainLoop();

    void registerClient(const nlohmann::json& json);

    nlohmann::json allSongs = {};

};

#endif //INTERVIEW_SERVICE_SONGS_H
