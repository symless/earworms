#include "pinger.h"

#include <boost/bind.hpp>

#include "icmp_header.hpp"
#include "ipv4_header.hpp"

pinger::pinger(boost::asio::io_context& io_context, const boost::asio::ip::address& destination)
: resolver_(io_context)
, socket_(io_context, destination.is_v4() ? icmp::v4() : icmp::v6())
, timer_(io_context), sequence_number_(0)
, num_replies_(0)
, ipv4(destination.is_v4())
{
    if (!ipv4)
    {
        //TODO Add ipv6 support
        throw "IPv6 currently unsupported";
    }

    destination_ = *resolver_.resolve(destination.is_v4() ? icmp::v4() : icmp::v6(), destination.to_string().c_str(), "").begin();
    
    start_send();
    start_receive();
}

void pinger::start_send()
{
    std::string body("\"Hello!\" from the interview service. Are you alive? I need to know I'm not alone.");

    // Create an ICMP header for an echo request.
    icmp_header echo_request;
    echo_request.type(icmp_header::echo_request);
    echo_request.code(0);
    echo_request.identifier(get_identifier());
    echo_request.sequence_number(++sequence_number_);
    compute_checksum(echo_request, body.begin(), body.end());

    // Encode the request packet.
    boost::asio::streambuf request_buffer;
    std::ostream os(&request_buffer);
    os << echo_request << body;

    // Send the request.
    time_sent_ = steady_timer::clock_type::now();
    socket_.send_to(request_buffer.data(), destination_);

    // Wait up to five seconds for a reply.
    num_replies_ = 0;
    timer_.expires_at(time_sent_ + chrono::milliseconds(200));
    timer_.async_wait(boost::bind(&pinger::handle_timeout, this));
}

void pinger::handle_timeout()
{
  /*  if (num_replies_ == 0)
        std::cout << "Request timed out" << std::endl;*/

    // Requests must be sent no less than one second apart.
    timer_.expires_at(time_sent_ + chrono::seconds(1));
    timer_.async_wait(boost::bind(&pinger::start_send, this));
}

void pinger::start_receive()
{
    // Discard any data already in the buffer.
    reply_buffer_.consume(reply_buffer_.size());

    // Wait for a reply. We prepare the buffer to receive up to 64KB.
    socket_.async_receive(reply_buffer_.prepare(65536),
                          boost::bind(&pinger::handle_receive, this, _2));
}

void pinger::handle_receive(std::size_t length)
{
    // The actual number of bytes received is committed to the buffer so that we
    // can extract it using a std::istream object.
    reply_buffer_.commit(length);

    // Decode the reply packet.
    std::istream is(&reply_buffer_);
    ipv4_header ipv4_hdr;
    icmp_header icmp_hdr;
    is >> ipv4_hdr >> icmp_hdr;

    // We can receive all ICMP packets received by the host, so we need to
    // filter out only the echo replies that match the our identifier and
    // expected sequence number.
    if (is && icmp_hdr.type() == icmp_header::echo_reply
        && icmp_hdr.identifier() == get_identifier()
        && icmp_hdr.sequence_number() == sequence_number_)
    {
        //// If this is the first reply, interrupt the five second timeout.
        //if (num_replies_++ == 0)
        //    timer_.cancel();

        //// Print out some information about the reply packet.
        //chrono::steady_clock::time_point now = chrono::steady_clock::now();
        //chrono::steady_clock::duration elapsed = now - time_sent_;
        //std::cout << length - ipv4_hdr.header_length()
        //    << " bytes from " << ipv4_hdr.source_address()
        //    << ": icmp_seq=" << icmp_hdr.sequence_number()
        //    << ", ttl=" << ipv4_hdr.time_to_live()
        //    << ", time="
        //    << chrono::duration_cast<chrono::milliseconds>(elapsed).count()
        //    << std::endl;
        alive = true;
    }

    start_receive();
}

unsigned short pinger::get_identifier()
{
#if defined(BOOST_ASIO_WINDOWS)
    return static_cast<unsigned short>(::GetCurrentProcessId());
#else
        return static_cast<unsigned short>(::getpid());
#endif
}
