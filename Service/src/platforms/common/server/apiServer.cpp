#include "apiServer.h"
#include <string>

int apiServer::startApi(std::string address, unsigned short port)
{
    try
    {
        auto const _address = net::ip::make_address(address);
        auto const doc_root = std::make_shared<std::string>("");

        std::cout << "Listening on " << address << ":" << port << std::endl;

        // The io_context is required for all I/O
        net::io_context ioc{1};

        // The acceptor receives incoming connections
        tcp::acceptor acceptor{ioc, {_address, port}};
        for (;;)
        {
            // This will receive the new connection
            tcp::socket socket{ioc};

            // Block until we get a connection
            acceptor.accept(socket);

            // Launch the session, transferring ownership of the socket
            std::thread{
                std::bind(
                    &do_session,
                    std::move(socket),
                    doc_root)
            }.detach();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

bool apiServer::registerCommand(const std::string& command, std::function<std::string(const std::string&)> function)
{
    if (m_commandMap.find(command) == m_commandMap.end())
    {
        m_commandMap.insert(std::make_pair(command, function));
        return true;
    }
    else
    {
        return false;
    }
}

bool apiServer::deregisterCommand(const std::string& command)
{
    auto itor = m_commandMap.find(command);
    if (itor != m_commandMap.end())
    {
        m_commandMap.erase(itor);
        return true;
    }
    else
    {
        return false;
    }
}

void apiServer::fail(beast::error_code ec, char const* what)
{
    //TODO Implement a centralized logging feature
    std::cerr << what << ": " << ec.message() << "\n";
}

void apiServer::do_session(tcp::socket& socket, std::shared_ptr<std::string const> const& doc_root)
{
    bool close = false;
    beast::error_code ec;

    // This buffer is required to persist across reads
    beast::flat_buffer buffer;

    // This lambda is used to send messages
    send_lambda<tcp::socket> lambda{socket, close, ec};

    for (;;)
    {
        // Read a request
        http::request<http::string_body> req;
        http::read(socket, buffer, req, ec);
        if (ec == http::error::end_of_stream)
            break;
        if (ec)
            return fail(ec, "read");

        // Send the response
        handle_request(*doc_root, std::move(req), lambda);
        if (ec)
            return fail(ec, "write");
        if (close)
        {
            // This means we should close the connection, usually because
            // the response indicated the "Connection: close" semantic.
            break;
        }
    }

    // Send a TCP shutdown
    socket.shutdown(tcp::socket::shutdown_send, ec);

    // At this point the connection is closed gracefully
}

template <class Body, class Allocator, class Send>
void apiServer::handle_request(beast::string_view doc_root, http::request<Body, http::basic_fields<Allocator>>&& req,
    Send&& send)
{
    // Returns a bad request response
    auto const bad_request =
        [&req](beast::string_view why)
    {
        http::response<http::string_body> res{ http::status::bad_request, req.version() };
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = std::string(why);
        res.prepare_payload();
        return res;
    };

    // Returns a not found response
    auto const not_found =
        [&req](beast::string_view target)
    {
        http::response<http::string_body> res{ http::status::not_found, req.version() };
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = "The resource '" + std::string(target) + "' was not found.";
        res.prepare_payload();
        return res;
    };

    // Returns a server error response
    auto const server_error =
        [&req](beast::string_view what)
    {
        http::response<http::string_body> res{ http::status::internal_server_error, req.version() };
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = "An error occurred: '" + std::string(what) + "'";
        res.prepare_payload();
        return res;
    };

    // Make sure we can handle the method
    if (req.method() != http::verb::get &&
        req.method() != http::verb::head &&
        req.method() != http::verb::post)
        return send(bad_request("Unknown HTTP-method"));


    // Request path must be absolute and not contain "..".
    if (req.target().empty() ||
        req.target()[0] != '/' ||
        req.target().find("..") != beast::string_view::npos)
        return send(bad_request("Illegal request-target"));

    const std::string command(req.target());
    const auto params = req.body();

    std::cout << "Request Path: " << command << std::endl;
    std::cout << "Request Body: " << params << std::endl;


    const auto itor = m_commandMap.find(command);

    std::function<std::string(std::string)> fnc;

    //If the command is found in the map use that otherwise return an error
    if (itor != m_commandMap.end())
    {
        fnc = itor->second;
    }
    else
    {
        fnc = [command](const std::string&)
        {
            return "Sorry that command(" + command + ") was not found";
        };
    }
    try{

        http::response<http::string_body> res{ http::status::ok, req.version() };
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "application/json");
        res.keep_alive(req.keep_alive());

        //Return the response from the found function with the received parameters
        res.body() = fnc(params);
        res.prepare_payload();
        return send(std::move(res));
    }
    catch(std::string error)
    {
        return send(bad_request(error));
    }
}

std::map<std::string, std::function<std::string(const std::string&)>> apiServer::m_commandMap;
