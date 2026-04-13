#pragma once
#include <iostream>
#include <ctime>
using namespace std;

enum class MsgType {LOGIN, REGISTER, STATUS, CHAT, ERROR};

struct Msg {
    MsgType type;
    string sender;
    string receiver;
    string content; 
    //LOGIN/REGISTER: email + password 
    //STATUS: Online/Offline
    //CHAT: message
    //ERROR: error
    time_t timestamp = time(NULL);
};
