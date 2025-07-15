cmake_minimum_required(VERSION 3.31)
project(BinaryTree)

set(CMAKE_CXX_STANDARD 23)
# Указываем путь к заголовочным файлам
include_directories(include)

# Добавляем исполняемый файл
add_executable(binary_tree src/main.cpp)
