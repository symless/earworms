//
// Created by Jamie on 25/11/2019.
//

#include "songs.h"
#include<string>

songs::songs() {
    int id = 0;

    allSongs[id]["name"]  = "Dance Monkey";
    allSongs[id]["artist"]  = "Tones and I";
    allSongs[id]["length"]  = 253;
    allSongs[id]["id"]      = 6590407;
    id++;
    allSongs[id]["name"]  = "ROXANNE";
    allSongs[id]["artist"]  = "Arizona Zervas";
    allSongs[id]["length"]  = 253;
    allSongs[id]["id"]      = 4352027;
    id++;

    allSongs[id]["name"]  = "Memories";
    allSongs[id]["artist"]  = "Maroon 5";
    allSongs[id]["length"]  = 253;
    allSongs[id]["id"]      = 4191138;
    id++;

    allSongs[id]["name"]  = "everything i wanted";
    allSongs[id]["artist"]  = "Billie Eilish";
    allSongs[id]["length"]  = 253;
    allSongs[id]["id"]      = 4055300;
    id++;

    allSongs[id]["name"]  = "Circles";
    allSongs[id]["artist"]  = "Post Malone";
    allSongs[id]["length"]  = 253;
    allSongs[id]["id"]      = 3777019;
    id++;

    allSongs[id]["name"]  = "Don't Start Now";
    allSongs[id]["artist"]  = "Dua Lipa";
    allSongs[id]["length"]  = 253;
    allSongs[id]["id"]      = 3493376;
    id++;

    allSongs[id]["name"]  = "RITMO (Bad Boys For Life)";
    allSongs[id]["artist"]  = "The Black Eyed Peas";
    allSongs[id]["length"]  = 253;
    allSongs[id]["id"]      = 3466034;
    id++;

    allSongs[id]["name"]  = "Lose You To Love Me";
    allSongs[id]["artist"]  = "Selena Gomez";
    allSongs[id]["length"]  = 253;
    allSongs[id]["id"]      = 3211298;
    id++;

    allSongs[id]["name"]  = "Someone You Loved";
    allSongs[id]["artist"]  = "Lewis Capaldi";
    allSongs[id]["length"]  = 253;
    allSongs[id]["id"]      = 3141729;
    id++;

    allSongs[id]["name"]  = "Señorita";
    allSongs[id]["artist"]  = "Shawn Mendes";
    allSongs[id]["length"]  = 253;
    allSongs[id]["id"]      = 3125606;
    id++;

    allSongs[id]["name"]  = "Vete";
    allSongs[id]["artist"]  = "Bad Bunny";
    allSongs[id]["length"]  = 253;
    allSongs[id]["id"]      = 3091458;
}

void songs::start() {

}

void songs::stop() {

}

nlohmann::json songs::getCurrentSongDetails() {

    m_updating.lock();

    nlohmann::json details = allSongs[1];

    details["position"] = 53;

    m_updating.unlock();
    return details;
}

nlohmann::json songs::getCurrentSongVoteDetails() {
    nlohmann::json details = {};

    details["songid"] = 27376;
    details["good"] = 3;
    details["neutral"] = 4;
    details["bad"] = 2;

    return details;

}

void songs::changeSong() {

    resetVotes();

    if(true)
    {
        m_currentSong++;
    }
    else
    {
        m_currentSong = 0;
    }

}

void songs::resetVotes() {

    m_votes_negative = 0;
    m_votes_neutral = 0;
    m_votes_positive = 0;

}

void songs::mainLoop() {

    w

}
