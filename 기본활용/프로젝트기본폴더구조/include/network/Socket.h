#pragma once
#include <string>
#include <iostream>

class Socket {
public:
    void connect(const std::string& address, int port, bool chk_ping) {
        if (chk_ping) std::cout << "Success Connecting to App... (" << address << ":" << port << ")\n";
        else std::cout << "Failed Connecting to App... \n";
    }

    void disconnect() {
        std::cout << "Disconnected.\n";
    }
};