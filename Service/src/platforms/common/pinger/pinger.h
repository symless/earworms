//
// ping.cpp
// ~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/asio.hpp>
#include <boost/asio/ip/icmp.hpp>

using boost::asio::ip::icmp;
using boost::asio::steady_timer;
namespace chrono = boost::asio::chrono;

class pinger
{
public:
    pinger(boost::asio::io_context& io_context, const boost::asio::ip::address& host);

    bool alive = false;

private:
    void start_send();

    void handle_timeout();

    void start_receive();

    void handle_receive(std::size_t length);

    static unsigned short get_identifier();

    icmp::resolver resolver_;
    icmp::endpoint destination_;
    icmp::socket socket_;
    steady_timer timer_;
    unsigned short sequence_number_;
    chrono::steady_clock::time_point time_sent_;
    boost::asio::streambuf reply_buffer_;
    std::size_t num_replies_;

    bool ipv4;

};

