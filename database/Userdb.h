#pragma once

#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "User.h"
#include "../common/Message.h"
#include "../common/Serializer.h"


class Userdb {
    public:
        Userdb(string filename);
        User creatUser(string, string, string);
        bool addUser(const User &usr);
        bool checkUser(string, string, string);
        string getFileName(string, string);
        vector<string> getMsgsForChat(string, string);
        void handleNewMsg(Msg msg);
        vector<User> getUsers();
    private:
        ofstream filestream;
        vector<User> users;
        vector<string> chat_files;
};