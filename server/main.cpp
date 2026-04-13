#include <boost/asio.hpp>
using boost::asio::ip::tcp;
#include "ChatServer.h"

int main() {
    boost::asio::io_context io;
    ChatServer server(io, 13);
    io.run();
    return 0;
}