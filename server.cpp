#include <string>
using namespace std;
#include "server/ChatServer.h"

int main() {
    string filename = "database/users_db.txt"; 
    int port = 1234;
    ChatServer* chatserver = new ChatServer(filename, port);
    chatserver->run();
}