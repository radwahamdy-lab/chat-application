#include "MessageRepo.h"
#include <fstream>
MessageRepo::MessageRepo(string filename) {
    this->filename = filename;
}

void MessageRepo::saveMessage(string sender,
                              string receiver,
                              string time,
                              string message) {
    ofstream file(filename, ios::app);
    file << sender << ","
         << receiver << ","
         << time << ","
         << message << "\n";
    file.close();
}