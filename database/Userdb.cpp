#include "Userdb.h"
#include "User.h"
#include "../common/Message.h"
#include "../common/Serializer.h"
#include <bcrypt/BCrypt.hpp>

#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

Userdb::Userdb(string filename) : filestream(filename, std::ios::out | std::ios::app) {
    ifstream in(filename);
    string usrname;
    string email;
    string password;
    User usr;

    while(getline(in, usrname, ',') && getline(in, email, ',') && getline(in, password)){
        usr = creatUser(usrname, email, password.substr(0,password.length()));
        users.push_back(usr);
    }

    in.close();
}


User Userdb::creatUser(string usrname, string email, string password){
    User usr;
    usr.usrname = usrname;
    usr.email = email;
    usr.password = password;
    return usr;
}

bool Userdb::addUser(const User& usr){
    users.push_back(usr);
    filestream << usr.usrname << "," << usr.email << "," << usr.password << endl;
    return true;
}

bool Userdb::checkUser(string usrname, string email, string password){
    int index = -1;
    for(int i=0; i<users.size(); i++)
        if(users[i].usrname == usrname)
            index = i;
    if(index != -1 && (users[index].email == email && BCrypt::validatePassword(password,users[index].password)))
        return true;
    return false;
}

// when receiving a new msg check if the two sides have a file or not if not cretae a file and add msg else add msg directly

void Userdb::handleNewMsg(Msg msg){
    string filename = getFileName(msg.sender, msg.receiver);
    ofstream out(filename, std::ios::out | std::ios::app);
    out << serialize(msg) << endl;
    out.close();
}


string Userdb::getFileName(string sender, string receiver){
    string filename = "database/";
    if(sender[0] < receiver[0]) filename += sender + "_" + receiver + ".txt";
    else filename += receiver + "_" + sender + ".txt";
    return filename;
}

vector<string> Userdb::getMsgsForChat(string sender, string receiver){
    string chat_file = getFileName(sender, receiver);
    ifstream in(chat_file);
    vector<string> msgs;
    if(in.good()){
        string msg;
        while(getline(in, msg)){
            msgs.push_back(msg);
        }
    }
    return msgs;
}

vector<User> Userdb::getUsers(){
    return users;
}
