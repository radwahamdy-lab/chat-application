#pragma once
#include <iostream>
#include <ctime>
using namespace std;

enum class MsgType {LOGIN, REGISTER, STATUS, CHAT, ERR, GET_USERS, GET_MSGS, LOGOUT};

struct Msg {
    MsgType type;
    string sender;
    string receiver;
    string content; 
    time_t timestamp = time(NULL);
};