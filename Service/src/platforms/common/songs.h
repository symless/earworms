//
// Created by Jamie on 25/11/2019.
//

#ifndef INTERVIEW_SERVICE_SONGS_H
#define INTERVIEW_SERVICE_SONGS_H

#include <mutex>

#include "nlohmann/json.hpp"


class songs {

public:

    songs();

    nlohmann::json getCurrentSongDetails();

    nlohmann::json getCurrentSongVoteDetails();

    void changeSong();

    void resetVotes();

private:

    std::mutex m_updating;

    int m_currentSong             = 0;
    unsigned int m_votes_positive = 0;
    unsigned int m_votes_negative = 0;
    unsigned int m_votes_neutral  = 0;


    //Starts the songs background service
    void start();

    //stops the songs background service
    void stop();


    nlohmann::json allSongs = {};




};

#endif //INTERVIEW_SERVICE_SONGS_H
