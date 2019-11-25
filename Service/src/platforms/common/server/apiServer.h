#ifndef SERVICE_APISERVER_H
#define SERVICE_APISERVER_H

//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//
// Original Source: https://www.boost.org/doc/libs/1_71_0/libs/beast/example/http/server/sync/http_server_sync.cpp
//
// Implemented in interview by Jamie Newbon on 27/09/2019
//------------------------------------------------------------------------------
//
// Example: HTTP server, synchronous
//
//------------------------------------------------------------------------------

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/config.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <map>
#include <functional>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class apiServer {

public:
    static int startApi(std::string address, unsigned short port);

    /**
     * \brief Add a new command to the API
     * \param command The name/uri of the command
     * \param function The function to execute when the command is called
     * \return True if the command was successfully added
     */
    static bool registerCommand(const std::string& command, std::function<std::string(const std::string&)> function);

    /**
     * \brief Removes a command from the list to be executed
     * \param command The command to be removed
     * \return True if the command was successfully removed
     */
    static bool deregisterCommand(const std::string& command);
private:

    /**
    * \brief Contain a map of commands with a function to execute when the command is received
     *          The function takes a parameter as a string and returns a parameter as a string to
     *          echo back to the requester
    */
    static std::map<std::string, std::function<std::string(const std::string&)>> m_commandMap;



// This function produces an HTTP response for the given
// request. The type of the response object depends on the
// contents of the request, so the interface requires the
// caller to pass a generic lambda for receiving the response.
    template<class Body, class Allocator, class Send>
    static void handle_request(
        beast::string_view doc_root,
        http::request<Body, http::basic_fields<Allocator>>&& req,
        Send&& send);

//------------------------------------------------------------------------------

// Report a failure
    static void
    fail(beast::error_code ec, char const* what);

// This is the C++11 equivalent of a generic lambda.
// The function object is used to send an HTTP message.
    template<class Stream>
    struct send_lambda
    {
        Stream& stream_;
        bool& close_;
        beast::error_code& ec_;

        explicit
        send_lambda(
                Stream& stream,
                bool& close,
                beast::error_code& ec)
                : stream_(stream)
                , close_(close)
                , ec_(ec)
        {
        }

        template<bool isRequest, class Body, class Fields>
        void
        operator()(http::message<isRequest, Body, Fields>&& msg) const
        {
            // Determine if we should close the connection after
            close_ = msg.need_eof();

            // We need the serializer here because the serializer requires
            // a non-const file_body, and the message oriented version of
            // http::write only works with const messages.
            http::serializer<isRequest, Body, Fields> sr{msg};
            http::write(stream_, sr, ec_);
        }
    };

// Handles an HTTP server connection
    static void
    do_session(
        tcp::socket& socket,
        std::shared_ptr<std::string const> const& doc_root);

//------------------------------------------------------------------------------

};


#endif //SERVICE_APISERVER_H
