#pragma once
#include <string>
using namespace std;
class MessageRepo {
public:
    MessageRepo(string filename);
    void saveMessage(string sender,
                     string receiver,
                     string time,
                     string message);

private:
    string filename;
};