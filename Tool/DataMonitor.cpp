#include "DataMonitor.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <ctime>
#include <sys/stat.h>
#include <conio.h>

DataMonitor::DataMonitor(const std::string& filePath, int refreshSeconds)
    : filePath_(filePath), refreshSeconds_(refreshSeconds) {}

void DataMonitor::run() {
    while (true) {
        int nextId = 1;
        JsonRepository repo(filePath_);
        auto users = repo.load(nextId);

        display(users);

        for (int i = 0; i < refreshSeconds_ * 10; ++i) {
            if (_kbhit()) {
                char c = _getch();
                if (c == 'q' || c == 'Q') {
                    std::cout << "\n모니터링을 종료합니다.\n";
                    return;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

void DataMonitor::display(const std::vector<User>& users) const {
    system("cls");

    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    char timeBuf[64];
    ctime_s(timeBuf, sizeof(timeBuf), &t);
    std::string timeStr(timeBuf);
    if (!timeStr.empty() && timeStr.back() == '\n') timeStr.pop_back();

    std::cout << "+==============================================+\n";
    std::cout << "|      DataPersistence   Monitor  Tool        |\n";
    std::cout << "+==============================================+\n";
    std::cout << "  현재 시각  : " << timeStr << "\n";
    std::cout << "  파일 경로  : " << filePath_ << "\n";
    std::cout << "  파일 수정  : " << getFileModifiedTime() << "\n";
    std::cout << "  총 레코드  : " << users.size() << " 건\n";
    std::cout << "  갱신 주기  : " << refreshSeconds_ << "초  |  종료: q\n";
    std::cout << "----------------------------------------------\n";
    std::cout << std::left
              << std::setw(6)  << "ID"
              << std::setw(22) << "Name"
              << "Email"
              << "\n";
    std::cout << "----------------------------------------------\n";

    if (users.empty()) {
        std::cout << "  (저장된 데이터 없음)\n";
    } else {
        for (const auto& u : users) {
            std::cout << std::left
                      << std::setw(6)  << u.id
                      << std::setw(22) << u.name
                      << u.email
                      << "\n";
        }
    }
    std::cout << "==============================================\n";
}

std::string DataMonitor::getFileModifiedTime() const {
    struct _stat st;
    if (_stat(filePath_.c_str(), &st) != 0) return "(파일 없음)";
    std::time_t t = st.st_mtime;
    char buf[64];
    ctime_s(buf, sizeof(buf), &t);
    std::string s(buf);
    if (!s.empty() && s.back() == '\n') s.pop_back();
    return s;
}
