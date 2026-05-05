cmake_minimum_required(VERSION 3.21)
project(myapp)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
add_subdirectory(external/libbcrypt)
add_executable(app 
    main.cpp
    gui/LoginScreen.h
    gui/LoginScreen.cpp
    gui/SignupScreen.h
    gui/SignupScreen.cpp
    gui/MainScreen.h
    gui/MainScreen.cpp
    gui/ChatScreen.h
    gui/ChatScreen.cpp

    database/User.h
    database/Userdb.h
    database/Userdb.cpp

    server/ChatServer.h
    server/ChatServer.cpp
    server/ClientSession.h
    server/ClientSession.cpp

    common/Message.h
    common/Serializer.h
    common/Serializer.cpp
)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
target_link_libraries(app PRIVATE Qt6::Widgets bcrypt)
target_include_directories(app PRIVATE external)

add_executable(server 
server.cpp 
server/ChatServer.h 
server/ChatServer.cpp 
database/User.h 
database/Userdb.h 
database/Userdb.cpp 
common/Message.h
common/Serializer.h
common/Serializer.cpp
)
target_link_libraries(server PRIVATE bcrypt)
target_include_directories(server PRIVATE external)