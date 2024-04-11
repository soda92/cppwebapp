#include <boost/asio.hpp>
#include <iostream>
#include <string>


using boost::asio::ip::tcp;

std::string make_response()
{
    std::string response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Length: 13\r\n";
    response += "\r\n";
    response += "Hello, world!";
    return response;
}

void handle_client(tcp::socket& socket)
{
    boost::asio::streambuf request;
    boost::asio::read_until(socket, request, "\r\n\r\n");
    std::string response = make_response();
    boost::asio::write(socket, boost::asio::buffer(response));
}

int main()
{
    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));

    for (;;)
    {
        tcp::socket socket(io_context);
        acceptor.accept(socket);
        handle_client(socket);
    }

    return 0;
}