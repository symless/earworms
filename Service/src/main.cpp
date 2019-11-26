#include <iostream>

#include "configuration/configuration.h"
#include "platforms/common/networking.hpp"
#include "platforms/common/songs.h"

int main()
{
    std::cout << "Starting Service...";

    auto* songService = new songs();

    //Initilkize everything
    std::cout << " Done." << std::endl;
    //Main loop

    auto* conf = new Configuration();
    
    conf->saveDefaultConfig();

    nlohmann::json config = conf->loadDefaultConfig();

    std::cout << "Starting web interface..." << std::endl;

    networking::registerAPICommand("/songs/current", [songService](const std::string& json)->std::string
    {
        try {
            nlohmann::json _json = nlohmann::json::parse(json.c_str());
            return songService->getCurrentSongDetails(_json).dump(4);
        }
        catch (...)
        {
            throw std::string("Bad json");
        }

    });

    networking::registerAPICommand("/songs/votes", [songService](const std::string& json)->std::string
    {
        try {
            nlohmann::json _json = nlohmann::json::parse(json.c_str());
            return songService->getCurrentSongVoteDetails(_json).dump(4);
        }
        catch (...)
        {
            throw std::string("Bad json");
        }
    });



    networking::registerAPICommand("/vote", [songService](const std::string& json)->std::string
    {
        try {
            nlohmann::json _json = nlohmann::json::parse(json.c_str());
            return songService->setVote(_json).dump(4);
        }
        catch (...)
        {
            throw std::string("Bad json");
        }
    });

    songService->start();

    networking::startServerApi();

    std::cout << "Stopping Service...";
    //Cleanup everything
    std::cout << " Done." << std::endl;
    //Exit
    return 0;

}
