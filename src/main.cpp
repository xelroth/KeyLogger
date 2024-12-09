#include "WebSocketClient.h"

int main() {
    try {
        WebSocketClient wsClient("ws://localhost:8989");
        wsClient.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
