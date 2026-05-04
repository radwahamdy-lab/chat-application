#pragma once

#include "Message.h"
#include "../nlohmann/json.hpp"
using namespace nlohmann;
#include <string>
using namespace std;

MsgType getType(string type);
string getString(MsgType type);
string serialize(Msg msg);
Msg deserialize(string js);
