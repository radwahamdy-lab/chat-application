#include <boost/asio.hpp>
using boost::asio::ip::tcp;

#include <string>
using namespace std;

#include "../common/Serializer.h"
#include "ChatServer.h"

class ClientSession {
    public:
        tcp::socket socket;
        ChatServer* server;
        string usrname;
        array<char, 128> buf;

        ClientSession(ChatServer &serv, boost::asio::io_context &io) {
            server = &serv;
            socket(io);
        }
        void start(){
            doRead();
        }
        void doRead() {
            boost::system::error_code error;

            size_t len = socket.async_read_some(boost::asio::buffer(buf), error);

            socket.async_read_some(boost::asio::buffer(buf), [&](){
                if(!ec){
                    string msg_str = "";
                    for(int i=0; i<len; i++) msg_str += buf[i];
            
                    Msg msg = deserialize(msg_str);
                    server->handleMsg(this, msg);
                    doRead();
                } else {
                    cout << "Client Disconnected" << endl;
                }
            })

            
        }
        void send(Msg msg){
            string msg_str = serialize(msg);
            boost::system::error_code ignored_error;
            boost::asio::async_write(socket, boost::asio::buffer(msg_str), [](ignore_error){});
        }
}