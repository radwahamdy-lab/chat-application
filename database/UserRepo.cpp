#include "UserRepo.h"

#include <fstream>
#include <sstream>
#include "User.h"
using namespace std;
UserRepo::UserRepo(string filename) {
    this->filename = filename;
}
vector<User> UserRepo::loadUsers() {
    vector<User> users;

    ifstream file(filename);
    string line;
    getline(file, line);

    while (getline(file, line)) {
        string username, email, password;
        stringstream ss(line);

        getline(ss, username, ',');
        getline(ss, email, ',');
        getline(ss, password, ',');

        User u;
        u.username = username;
        u.email = email;
        u.password = password;

        users.push_back(u);
    }

    file.close();
    return users;
}
vector<User> UserRepo::getAllUsers() {
    return loadUsers();
}
bool UserRepo::validateUser(string username, string password) {
    vector<User> users = loadUsers();

    for (int i = 0; i < users.size(); i++) {
        if (users[i].username == username &&
            users[i].password == password) {
            return true;
        }
    }
    return false;
}
bool UserRepo::createUser(string username, string email, string password) {
    vector<User> users = loadUsers();
    for (int i = 0; i < users.size(); i++) {
        if (users[i].username == username) {
            return false;
        }
    }

    saveUser({username, email, password});
    return true;
}
void UserRepo::saveUser(User user) {
    ofstream file(filename, ios::app);
    file << user.username << ","
         << user.email << ","
         << user.password << "\n";
    file.close();
}