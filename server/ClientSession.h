#include <boost/asio.hpp>
using boost::asio::ip::tcp;
#include <string>
using namespace std;
#include "../common/Serializer.h"
#include "ChatServer.h"

class ClientSession {
    public:
        tcp::socket socket;
        ChatServer server;
        string usrname;
        ClientSession(ChatServer serv, boost::asio::io_context io, string usr="default") {
            usrname = usr;
            server = serv;
            socket(io);
            start();
        }
        void start(){
            boost::asio::connect(socket, tcp::endpoint(tcp::v4(), 13));
            doRead();
        }
        void doRead() {
            std::array<char, 128> buf;
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            string msg_str = "";
            for(int i=0; i<len; i++) msg_str += buf[i];
            
            Msg msg = deserialize(msg_str);
            server.handleMsg(this, msg, usrname);

            if (error != boost::asio::error::eof){
                doRead();
                throw boost::system::system_error(error);
            }
        }
        void send(Msg msg){
            string msg_str = serialize(msg);
            boost::system::error_code ignore_error;
            boost::asio::write(socket, boost::asio::buffer(msg_str), ignored_error);
        }
}