#include "networking.hpp"
#include <boost/asio.hpp>
#include "pinger/pinger.h"
#include "server/apiServer.h"

std::list<boost::asio::ip::address> networking::getAllNetworkAddresses()
{
    using boost::asio::ip::tcp;
    boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
    tcp::resolver::query query(boost::asio::ip::host_name(), "");
    tcp::resolver::iterator it = resolver.resolve(query);

    std::list<boost::asio::ip::address> result;

    while (it != tcp::resolver::iterator())
    {
        boost::asio::ip::address addr = (it++)->endpoint().address();
        
        result.push_back(addr);

    }
    return result;
}

bool networking::isHostAlive(const boost::asio::ip::address& host)
{
    boost::asio::io_service io_service;
    bool alive = false;
    try
    {
        pinger p(io_service, host);

        //run for 200 miliseconds
        io_service.run_until(steady_timer::clock_type::now() + chrono::milliseconds(200));

        alive = p.alive;
    }
    catch (...)
    {
        return false;
    }
    return alive;
}

bool networking::startServerApi() {

    ;
    return apiServer::startApi("0.0.0.0", 24825) == 0;
}

bool networking::registerAPICommand(const std::string& command, std::function<std::string(const std::string&)> function)
{
    const auto result = apiServer::registerCommand(command, function);
    std::cout << "Registering: '" << command << "' " << (result ? "Success" : "Failed") << std::endl;

    return result;
}

bool networking::deregisterAPICommand(const std::string& command)
{
    const auto result = apiServer::deregisterCommand(command);
    std::cout << "Unregistering: '" << command << "' " << (result ? "Success" : "Failed") << std::endl;

    return result;
}
