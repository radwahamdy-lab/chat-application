#pragma once
#include "Database.h"
#include <string>

class UserRepo {
public:
    UserRepo(Database& db);

    bool createUser(const std::string& username, const std::string& password);
    bool validateUser(const std::string& username, const std::string& password);
    bool userExists(const std::string& username);

private:
    Database& database;
};