cmake_minimum_required(VERSION 3.28)
project(SnakeGame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 使用系统安装的 SFML
find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system)

# 添加所有源文件
add_executable(snake
    src/main.cpp
    src/board.cpp
    src/snake.cpp
    src/food.cpp
    src/UI.cpp
)

target_compile_features(snake PRIVATE cxx_std_17)

# 链接到系统安装的 SFML 库
target_link_libraries(snake PRIVATE sfml-graphics sfml-window sfml-system)