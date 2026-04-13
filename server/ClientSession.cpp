#include <boost/asio.hpp>
using boost::asio::ip::tcp;

#include <string>
using namespace std;

#include "../common/Serializer.h"
#include "ChatServer.h"
#include "ClientSession.h"

ClientSession::ClientSession(ChatServer &serv, boost::asio::io_context &io) : socket(io){
    server = &serv;
}

void ClientSession::start(){
    doRead();
}

void ClientSession::doRead() {
    socket.async_read_some(boost::asio::buffer(buf), [&](boost::system::error_code error, size_t len){
        if(!error){
            string msg_str = "";
            for(size_t i=0; i<len; i++) msg_str += buf[i];
    
            Msg msg = deserialize(msg_str);
            server->handleMsg(*this, msg);
            doRead();
        } else {
            cout << "Client Disconnected" << endl;
        }
    });
}

void ClientSession::send(Msg msg){
    msg_str = serialize(msg);
    boost::system::error_code ignored_error;
    boost::asio::async_write(socket, boost::asio::buffer(msg_str), [&](boost::system::error_code ignored_error, size_t len){});
}