#include "../common/Message.h"
#include "../common/Protocol.h"
#include "../common/Serializer.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    Msg msg;
    msg.type = MsgType::LOGIN;
    msg.sender = "me";
    msg.receiver = "you";
    msg.content = "hi";
    msg.timestamp = "today";

    string msg_str = serialize(msg);
    cout << msg_str << endl;
    Msg msg2 = deserialize(msg_str);
    cout << getString(msg.type) << " " << msg.sender << " " << msg.receiver << " " << msg.content << " " << msg.timestamp << endl;
    return 0;
}