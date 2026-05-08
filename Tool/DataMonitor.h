#pragma once
#include "../Repository/JsonRepository.h"
#include "../Model/User.h"
#include <string>
#include <vector>

class DataMonitor {
public:
    DataMonitor(const std::string& filePath, int refreshSeconds = 2);
    void run();

private:
    std::string filePath_;
    int         refreshSeconds_;

    void        display(const std::vector<User>& users) const;
    std::string getFileModifiedTime() const;
};
