cmake_minimum_required(VERSION 3.16)
project(DataPersistence CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(nlohmann_json)

add_executable(DataPersistence
    main.cpp
    Model/UserModel.cpp
    View/ConsoleView.cpp
    Controller/AppController.cpp
    Repository/JsonRepository.cpp
)

target_include_directories(DataPersistence PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(DataPersistence PRIVATE nlohmann_json::nlohmann_json)

add_executable(MonitorTool
    monitor_main.cpp
    Tool/DataMonitor.cpp
    Repository/JsonRepository.cpp
)

target_include_directories(MonitorTool PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(MonitorTool PRIVATE nlohmann_json::nlohmann_json)
