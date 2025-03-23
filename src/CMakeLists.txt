cmake_minimum_required(VERSION 3.28)
project(crow_x_ngingx_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:/dev/vcpkg/installed/x64-windows")
set(CMAKE_TOOLCHAIN_FILE "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")

add_executable(app main.cpp)

find_package(Crow CONFIG REQUIRED)

target_link_libraries(app PRIVATE Crow::Crow asio::asio)

add_custom_command( 
TARGET app 
COMMAND ${CMAKE_COMMAND} ARGS -E copy_directory "${CMAKE_SOURCE_DIR}/templates" "${CMAKE_CURRENT_BINARY_DIR}/templates")

add_custom_command( 
TARGET app 
COMMAND ${CMAKE_COMMAND} ARGS -E copy_directory "${CMAKE_SOURCE_DIR}/static" "${CMAKE_CURRENT_BINARY_DIR}/static")