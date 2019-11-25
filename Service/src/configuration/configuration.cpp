/*
 * Intervew Service
 * Copyright (C) 2019 Symless Ltd.
 *
 */

/**
 * @file configuration.cpp
 * @author Jamie Newbon
 * @date 17/09/2019
 * @brief The class deals with all configuration settings in the service
 * 
 */
#include <fstream>

#include "configuration.h"
#include "nlohmann/json.hpp"



Configuration::Configuration()
{
}

Configuration::~Configuration()
{
}

void Configuration::saveDefaultConfig()
{
    const nlohmann::json json = R"(
  {
    "happy": true,
    "pi": 3.141
  }
)"_json;

    save(FILE, 
        json,
        "");
}

nlohmann::json Configuration::loadDefaultConfig()
{
    nlohmann::json config;

    load(FILE, config, "");

    return config;
}

bool Configuration::save(const config_target location, const std::string& config, const std::string& fileLocation = "")
{
    bool result = true;
    switch (location)
    {
    case FILE:
        {
            //if there is no custom file location use the default location
            const std::string saveLocation(fileLocation.empty() ? m_configFileLocation : fileLocation);

            //TODO Add cross-platform support

            std::ofstream configFileStream;
            configFileStream.open(saveLocation, std::ios::trunc);
            configFileStream << config;
            configFileStream.close();

        break;
        }
    case CLOUD:
        {
        result = false;
            //TODO Add Cloud Support
        break;
        }
    }


    return result;
}

bool Configuration::save(const config_target location, const nlohmann::json& config, const std::string& fileLocation)
{
    //When dumping the json to file we want it to be formatted so it's human readable
    if (location == FILE)
    {
        return save(location, config.dump(4), fileLocation);
    }
    else
    {
        return save(location, config.dump(), fileLocation);
    }
}

bool Configuration::load(const config_target location, nlohmann::json& config, const std::string& fileLocation)
{
    std::string configSettings;

    bool result = load(location, configSettings, fileLocation);

    if (result)
    {
        try
        {
            config = configSettings;
        }
        catch (...)
        {
            result = false;
        }
        config = configSettings;
    }

    return result;
}

bool Configuration::load(const config_target location, std::string& config, const std::string& fileLocation)
{
    bool result = true;
    switch (location)
    {
    case FILE:
    {
        //if there is no custom file location use the default location
        const std::string saveLocation(fileLocation.empty() ? m_configFileLocation : fileLocation);
        //TODO Add cross-platform support

        std::ifstream configFileStream;
        configFileStream.open(saveLocation, std::ios::in);
        while (!configFileStream.eof()) 
        {
            std::string line;
            configFileStream >> line;
            config += line;

        }
        configFileStream.close();

        break;
    }
    case CLOUD:
    {
        result = false;
        //TODO Add Cloud Support
        break;
    }
    }
    return result;
  
}
