#pragma once

#include "Protocol.h"
#include "../nlohmann/json.hpp"
using namespace nlohmann;
#include <string>
using namespace std;


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

