#include "Model/UserModel.h"
#include "View/ConsoleView.h"
#include "Controller/AppController.h"
#include "Repository/JsonRepository.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    const std::string filePath = "users.json";

    JsonRepository repo(filePath);
    UserModel      model(repo);

    std::cout << "[INFO] Data file : " << filePath << "\n";
    std::cout << "[INFO] Loaded    : " << model.getUsers().size() << " record(s)\n";

    ConsoleView   view(model);
    AppController controller(model, view);

    controller.run();
    return 0;
}
