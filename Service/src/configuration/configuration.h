#ifndef CONFIGURATION_H
#define CONFIGURATION_H
/*
 * Intervew Service
 * Copyright (C) 2019 Symless Ltd.
 *
 */

/**
 * @file configuration.h
 * @author Jamie Newbon
 * @date 17/09/2019
 * @brief The class deals with all configuration settings in the service
 * 
 */

#include <string>

#include "nlohmann/json.hpp"

class Configuration
{
public:
 
    
    enum config_target
    {
        FILE,
        CLOUD,
    };
    
    
    Configuration();
    ~Configuration();

    /**
     * \brief Save a default config file to the default location
     */
    void saveDefaultConfig();

    nlohmann::json loadDefaultConfig();

private:

    /**
     * \brief Stores the default location of the config file
     */
    const std::string m_configFileLocation = "config.json";

    /**
     * \brief Saves the configuration settings to a specified location
     * \param location The target location to save the config file.
     * \param config The json text that make up the configuration settings
     * \param fileLocation The location the the file if local was selected
     * \return true id saving was successful to the target location
     */
    bool    save(const config_target location, const std::string& config, const std::string& fileLocation);

    /**
     * \brief Saves the configuration settings to a specified location
     * \param location The target location to save the config file.
     * \param config The json text that make up the configuration settings
     * \param fileLocation The location the the file if local was selected
     * \return true id saving was successful to the target location
     */
    bool    save(const config_target location, const nlohmann::json& config, const std::string& fileLocation);

    /**
     * \brief Loads the config setting from the specified location
     * \param location The target to load the config from
     * \param config A reference to the object where the config will be placed 
     * \param fileLocation The file location if different from default
     * \return True if the config was loaded successfully
     */
    bool    load(const config_target location, nlohmann::json& config, const std::string& fileLocation);

    /**
     * \brief Loads the config setting from the specified location
     * \param location The target to load the config from
     * \param config A reference to the object where the config will be placed
     * \param fileLocation The file location if different from default
     * \return True if the config was loaded successfully
     */
    bool    load(const config_target location, std::string& config, const std::string& fileLocation);
};

#endif