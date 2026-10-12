cmake_minimum_required(VERSION 3.16)

project(VyshKat LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Исходники и строки в UTF-8. MSVC без этого флага читает файлы в системной
# кодировке, и русские строки превращаются в мусор.
if(MSVC)
    add_compile_options(/utf-8 /W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Вся логика приложения лежит в библиотеке: её используют и программа, и тесты.
file(GLOB_RECURSE VYSHKAT_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
list(FILTER VYSHKAT_SOURCES EXCLUDE REGEX ".*/src/main\\.cpp$")

add_library(vyshkat_core STATIC ${VYSHKAT_SOURCES}
        src/factory/TransportFactory.h
        src/app/AppContainer.cpp
        src/app/AppContainer.h
        src/app/DemoData.cpp
        src/app/DemoData.h)
target_include_directories(vyshkat_core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Консольное приложение.
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
    add_executable(vyshkat src/main.cpp
            src/interfaces/InspectionService.h
            src/inspection/Inspection.cpp
            src/inspection/Inspection.h
            src/inspection/ServiceCenter.cpp
            src/inspection/ServiceCenter.h
            src/park/Park.cpp
            src/park/Park.h
            src/park/ParkService.cpp
            src/park/ParkService.h
            src/park/ParkReport.cpp
            src/park/ParkReport.h)
    target_link_libraries(vyshkat PRIVATE vyshkat_core)
endif()

# Юнит-тесты: подключаются, когда появится tests/CMakeLists.txt.
option(VYSHKAT_BUILD_TESTS "Build unit tests" ON)

if(VYSHKAT_BUILD_TESTS AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
    enable_testing()
    add_subdirectory(tests)
endif()