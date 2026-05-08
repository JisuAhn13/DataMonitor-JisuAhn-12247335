#include "Tool/DataMonitor.h"
#include <iostream>
#include <stdexcept>
#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char* argv[]) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    std::string filePath      = "users.json";
    int         refreshSeconds = 2;

    if (argc >= 2) filePath = argv[1];
    if (argc >= 3) {
        try { refreshSeconds = std::stoi(argv[2]); }
        catch (...) { refreshSeconds = 2; }
    }

    std::cout << "[Monitor] 파일: " << filePath
              << "  |  갱신 주기: " << refreshSeconds << "초\n";
    std::cout << "[Monitor] 시작합니다...\n";

    DataMonitor monitor(filePath, refreshSeconds);
    monitor.run();
    return 0;
}
