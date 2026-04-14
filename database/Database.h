#pragma once
#include <sqlite3.h>
#include <string>

class Database {
public:
    Database(const std::string& dbFile);
    ~Database();

    sqlite3* getConnection();

private:
    sqlite3* db;
    void initialize();
};