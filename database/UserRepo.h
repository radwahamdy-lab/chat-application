#pragma once
#include <vector>
#include <string>
#include "User.h"

using namespace std;
class UserRepo {
public:
    UserRepo(string filename);
    vector<User> getAllUsers();
    bool validateUser(string username, string password);
    bool createUser(string username, string email, string password);
private:
    string filename;
    vector<User> loadUsers();
    void saveUser(User user);
};