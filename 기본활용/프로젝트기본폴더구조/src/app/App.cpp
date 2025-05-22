#include "App.h"
#include "network/Socket.h"
#include <iostream>

void App::run() {
    std::cout << "Wait for 5 seconds." << std::endl;

    Socket socket;
    socket.connect("127.0.0.1", 8080, true);
    socket.disconnect();
}