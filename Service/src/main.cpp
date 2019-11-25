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

    networking::registerAPICommand("/songs/current", [songService](const std::string&)->std::string
    {
        return songService->getCurrentSongDetails().dump(4);
    });

    networking::registerAPICommand("/songs/votes", [songService](const std::string&)->std::string
    {
        return songService->getCurrentSongVoteDetails().dump(4);
    });

    networking::startServerApi();

    std::cout << "Stopping Service...";
    //Cleanup everything
    std::cout << " Done." << std::endl;
    //Exit
    return 0;

}
