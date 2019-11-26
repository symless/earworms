//
// Created by Jamie on 25/11/2019.
//

#include "songs.h"
#include <string>
#include <thread>
#include <chrono>
#include <iostream>

songs::songs() {
    int id = 0;

    allSongs[id]["name"]  = "Dance Monkey";
    allSongs[id]["artist"]  = "Tones and I";
    allSongs[id]["length"]  = 25;
    allSongs[id]["id"]      = 6590407;
    allSongs[id]["art"]      = "http://icons.iconarchive.com/icons/papirus-team/papirus-apps/512/synergy-icon.png";

    id++;
    allSongs[id]["name"]  = "ROXANNE";
    allSongs[id]["artist"]  = "Arizona Zervas";
    allSongs[id]["length"]  = 25;
    allSongs[id]["id"]      = 4352027;
    allSongs[id]["art"]      = "http://icons.iconarchive.com/icons/papirus-team/papirus-apps/512/synergy-icon.png";
    id++;

    allSongs[id]["name"]  = "Memories";
    allSongs[id]["artist"]  = "Maroon 5";
    allSongs[id]["length"]  = 120;
    allSongs[id]["id"]      = 4191138;
    allSongs[id]["art"]      = "http://icons.iconarchive.com/icons/papirus-team/papirus-apps/512/synergy-icon.png";
    id++;

    allSongs[id]["name"]  = "everything i wanted";
    allSongs[id]["artist"]  = "Billie Eilish";
    allSongs[id]["length"]  = 135;
    allSongs[id]["id"]      = 4055300;
    allSongs[id]["art"]      = "http://icons.iconarchive.com/icons/papirus-team/papirus-apps/512/synergy-icon.png";
    id++;

    allSongs[id]["name"]  = "Circles";
    allSongs[id]["artist"]  = "Post Malone";
    allSongs[id]["length"]  = 145;
    allSongs[id]["id"]      = 3777019;
    allSongs[id]["art"]      = "http://icons.iconarchive.com/icons/papirus-team/papirus-apps/512/synergy-icon.png";
    id++;

    allSongs[id]["name"]  = "Don't Start Now";
    allSongs[id]["artist"]  = "Dua Lipa";
    allSongs[id]["length"]  = 149;
    allSongs[id]["id"]      = 3493376;
    allSongs[id]["art"]      = "http://icons.iconarchive.com/icons/papirus-team/papirus-apps/512/synergy-icon.png";
    id++;

    allSongs[id]["name"]  = "RITMO (Bad Boys For Life)";
    allSongs[id]["artist"]  = "The Black Eyed Peas";
    allSongs[id]["length"]  = 135;
    allSongs[id]["id"]      = 3466034;
    allSongs[id]["art"]      = "http://icons.iconarchive.com/icons/papirus-team/papirus-apps/512/synergy-icon.png";
    id++;

    allSongs[id]["name"]  = "Lose You To Love Me";
    allSongs[id]["artist"]  = "Selena Gomez";
    allSongs[id]["length"]  = 175;
    allSongs[id]["id"]      = 3211298;
    allSongs[id]["art"]      = "http://icons.iconarchive.com/icons/papirus-team/papirus-apps/512/synergy-icon.png";
    id++;

    allSongs[id]["name"]  = "Someone You Loved";
    allSongs[id]["artist"]  = "Lewis Capaldi";
    allSongs[id]["length"]  = 1586;
    allSongs[id]["id"]      = 3141729;
    allSongs[id]["art"]      = "http://icons.iconarchive.com/icons/papirus-team/papirus-apps/512/synergy-icon.png";
    id++;

    allSongs[id]["name"]  = "Señorita";
    allSongs[id]["artist"]  = "Shawn Mendes";
    allSongs[id]["length"]  = 142;
    allSongs[id]["id"]      = 3125606;
    allSongs[id]["art"]      = "http://icons.iconarchive.com/icons/papirus-team/papirus-apps/512/synergy-icon.png";
    id++;

    allSongs[id]["name"]  = "Vete";
    allSongs[id]["artist"]  = "Bad Bunny";
    allSongs[id]["length"]  = 30;
    allSongs[id]["id"]      = 3091458;
    allSongs[id]["art"]      = "http://icons.iconarchive.com/icons/papirus-team/papirus-apps/512/synergy-icon.png";
}

void songs::start() {
    m_program = new std::thread(&songs::mainLoop, this);
}

void songs::stop() {
    m_quit = true;
    m_program->join();
}

nlohmann::json songs::getCurrentSongDetails(const nlohmann::json& json) {

    registerClient(json);

    m_updating.lock();

    nlohmann::json details = allSongs[m_currentSong];

    details["position"] = int(allSongs[m_currentSong]["length"]) - m_timeLeftInSong;
    details["skipping"] = m_currentSkip;


    m_updating.unlock();
    return details;
}

nlohmann::json songs::getCurrentSongVoteDetails(const nlohmann::json& json) {
    nlohmann::json details = {};

    details["songid"] = allSongs[m_currentSong]["id"];


    auto results = countVotes();

    details["good"]     = results["good"];
    details["bad"]      = results["bad"];
    details["neutral"]  = results["neutral"];

    return details;

}

void songs::changeSong()
{
    m_updating.lock();
    resetVotes();
    if(m_currentSong < allSongs.size()-1)
    {
        m_currentSong++;
    }
    else
    {
        m_currentSong = 0;
    }
    m_skipTimer = 3;
    m_currentSkip = false;

    std::cout << "Changing song to " << allSongs[m_currentSong]["name"];
    m_timeLeftInSong = allSongs[m_currentSong]["length"];
    m_updating.unlock();
}

void songs::resetVotes() {
    m_voteList.clear();
}

void songs::mainLoop() {

    //keep running till quit is signaled
    while (!m_quit)
    {
        shouldSkip();

        if (m_timeLeftInSong <= 0)
        {
            changeSong();
        }
        else if (m_currentSkip && m_skipTimer <= 0)
        {
            changeSong();
        }
        else if (m_currentSkip && m_skipTimer > 0)
        {
            m_skipTimer--;
            m_timeLeftInSong--;
        }
        else
        {
            m_timeLeftInSong--;
        }
        std::cout << "Song: " << allSongs[m_currentSong]["name"] << " Time left: " << m_timeLeftInSong << " seconds" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

}

void songs::registerClient(const nlohmann::json& json) {
    if (!json.contains("cid"))
    {
        throw std::string("Bad Request: cid not provided.");
    }
    if(m_voteList.find(json["cid"]) == m_voteList.end())
    {
        m_voteList[json["cid"]] = (client());
    }
  
    if (json.contains("vote"))
    {
        m_voteList[json["cid"]].m_vote = json["vote"];
    }
}

nlohmann::json songs::setVote(const nlohmann::json & json ) {
    nlohmann::json response = {};

    if (!json.contains("cid")) {
        response["response"] = "failed";
        response["message"] = "Request did not contain a cid";
    }
    else if (!json.contains("vote")) {
        response["response"] = "failed";
        response["message"] = "Request did not contain a vote";
    }
    else
    {
        registerClient(json);
        if (json["vote"] <= client::VOTE_START || json["vote"] >= client::VOTE_END)
        {
            response["response"] = "failed";
            response["message"] = "the vote value was not between " + std::to_string(client::VOTE_START + 1) + " and " +  std::to_string(client::VOTE_END - 1);
        }
        m_voteList[json["cid"]].m_vote = json["vote"];
        response["response"] = "success";

    }
    return response;

}

void songs::shouldSkip() {
    auto results = countVotes();

    int    m_votes_positive = results["good"];
    int    m_votes_negative = results["bad"];
    int    m_votes_neutral  = results["neutral"];

    //Count the total sentiment of the room
    int    m_votes_total    = (m_votes_positive) +
                              (m_votes_negative) +
                              (m_votes_neutral);

    //count the negative votes over positive
    float negtiveThresh = float(m_votes_negative - m_votes_positive);

    if ( m_votes_total > 0 && negtiveThresh > (m_votes_total * 0.25))

    {
        std::cout << "Skip threshold met" << std::endl;
        m_currentSkip = true;
    }

}

std::map<std::string, unsigned int> songs::countVotes() {


    unsigned int    m_votes_positive = 0;
    unsigned int    m_votes_negative = 0;
    unsigned int    m_votes_neutral  = 0;

    for (auto i = m_voteList.begin(); i != m_voteList.end(); ++i) {
        i->second.m_vote;
        switch(i->second.m_vote){
            case client::Neutral:
                m_votes_neutral += 1;
                break;
            case client::Positive:
                m_votes_positive += 1;
                break;
            case client::Negative:
                m_votes_negative += 1;
                break;
        }
    }
    std::map<std::string, unsigned int> count;
    count["good"] = m_votes_positive;
    count["neutral"] = m_votes_neutral;
    count["bad"] = m_votes_negative;
    return count;
}
