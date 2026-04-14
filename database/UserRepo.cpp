#include "UserRepo.h"
#include <sqlite3.h>

UserRepo::UserRepo(Database& db) : database(db) {}

bool UserRepo::createUser(const std::string& username, const std::string& password) {
    if (userExists(username)) return false;

    const char* sql = "INSERT INTO users (username, password) VALUES (?, ?);";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(database.getConnection(), sql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);
    return success;
}

bool UserRepo::validateUser(const std::string& username, const std::string& password) {
    const char* sql = "SELECT password FROM users WHERE username = ?;";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(database.getConnection(), sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    bool valid = false;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string storedPassword = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        valid = (storedPassword == password);
    }

    sqlite3_finalize(stmt);
    return valid;
}

bool UserRepo::userExists(const std::string& username) {
    const char* sql = "SELECT 1 FROM users WHERE username = ?;";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(database.getConnection(), sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    bool exists = (sqlite3_step(stmt) == SQLITE_ROW);

    sqlite3_finalize(stmt);
    return exists;
}