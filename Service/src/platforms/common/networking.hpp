#ifndef NETWORKING_HPP
#define NETWORKING_HPP
/*
 * Intervew Service
 * Copyright (C) 2019 Symless Ltd.
 *
 */

/**
 * @file networking.hpp
 * @author Jamie Newbon
 * @date 23/09/2019
 * @brief Contains common networking functions
 * 
 */


#include <list>

#include "boost/asio/ip/address.hpp"

class networking
{
public:

    /**
    * \brief Get all local IP addresses for the current machine
    * \return List of IP's
    */
    static std::list<boost::asio::ip::address> getAllNetworkAddresses();

    /**
    * \brief Ping a host to see if it alive and responding
    * \param host The Address of the host to ping
    * \return True if the host responded to a ping request
    */
    static bool isHostAlive(const boost::asio::ip::address& host);


    static bool startServerApi();

    /**
     * \brief Add a new command to the API
     * \param command The name/uri of the command
     * \param function The function to execute when the command is called
     * \return True if the command was successfully added
     */
    static bool registerAPICommand(const std::string& command, std::function<std::string(const std::string&)> function);
    
    /**
    * \brief Removes a command from the list to be executed
    * \param command The command to be removed
    * \return True if the command was successfully removed
    */
    static bool deregisterAPICommand(const std::string& command);
};


#endif
