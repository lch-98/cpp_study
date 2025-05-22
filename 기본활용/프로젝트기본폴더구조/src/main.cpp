#include <iostream>
#include "app/App.h"
#include "utils/Logger.h"

int main() {
    App app;
    Logger::info("Starting the app...");
    app.run();
    
    std::cout << "\nutf-8 한국어도 잘 나와요" << std::endl;
    return 0;
}