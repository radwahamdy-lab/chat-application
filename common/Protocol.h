#pragma once

#include "Message.h"
#include <string>
using namespace std;

MsgType getType(string type){
    if(type == "login") return MsgType::LOGIN;
    if(type == "register") return MsgType::REGISTER;
    if(type == "chat") return MsgType::CHAT;
    if(type == "status") return MsgType::STATUS;
    else return MsgType::ERROR;
}

string getString(MsgType type){
    switch (type){
        case MsgType::LOGIN: return "login";
        case MsgType::REGISTER: return "register";
        case MsgType::CHAT: return "chat";
        case MsgType::STATUS: return "status";
        case MsgType::ERROR: return "error";
    }
}