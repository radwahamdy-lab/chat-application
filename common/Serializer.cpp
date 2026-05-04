#include "Message.h"
#include "Serializer.h"
#include <nlohmann/json.hpp>
using namespace nlohmann;
#include <string>
using namespace std;

MsgType getType(string type){
    if(type == "login") return MsgType::LOGIN;
    if(type == "logout") return MsgType::LOGOUT;
    if(type == "register") return MsgType::REGISTER;
    if(type == "chat") return MsgType::CHAT;
    if(type == "status") return MsgType::STATUS;
    if(type == "error") return MsgType::ERR;
    if(type == "get users") return MsgType::GET_USERS;
    if(type == "get msgs") return MsgType::GET_MSGS;
}

string getString(MsgType type){
    string msg_type;
    switch (type){
        case MsgType::LOGIN: 
            msg_type = "login";
            break;
        case MsgType::LOGOUT: 
            msg_type = "logout";
            break;
        case MsgType::REGISTER: 
            msg_type = "register";
            break;
        case MsgType::CHAT: 
            msg_type = "chat";
            break;
        case MsgType::STATUS: 
            msg_type = "status";
            break;
        case MsgType::ERR: 
            msg_type = "error";
            break;
        case MsgType::GET_USERS:
            msg_type = "get users";
            break;
        case MsgType::GET_MSGS:
            msg_type = "get msgs";
    }

    return msg_type;
}

string serialize(Msg msg){
    json js = {
        {"type", getString(msg.type)},
        {"sender", msg.sender},
        {"receiver", msg.receiver},
        {"content", msg.content},
        {"timestamp", msg.timestamp}
    };
    return js.dump();
}


Msg deserialize(string js){
    json js2 = json::parse(js);
    
    Msg msg = {
        getType(js2.at("type")), 
        js2.at("sender"), 
        js2.at("receiver"), 
        js2.at("content"), 
        js2.at("timestamp")
    };
    return msg;
}
