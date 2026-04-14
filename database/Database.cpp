#include "Database.h"
#include <iostream>

Database::Database(const std::string& dbFile) : db(nullptr) {
    if (sqlite3_open(dbFile.c_str(), &db)) {
        std::cerr << "Cannot open database\n";
    } else {
        initialize();
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
    }
}

sqlite3* Database::getConnection() {
    return db;
}

void Database::initialize() {
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE,
            password TEXT
        );
    )";

    char* errMsg = nullptr;

    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error creating table: " << errMsg << "\n";
        sqlite3_free(errMsg);
    }
}