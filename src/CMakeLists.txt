cmake_minimum_required(VERSION 3.25)
project(crow_x_ngingx_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
	set(CMAKE_PREFIX_PATH "C:/dev/vcpkg/installed/x64-windows")
	set(CMAKE_TOOLCHAIN_FILE "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")
else()
	set(CMAKE_C_COMPILER "/usr/bin/gcc" CACHE PATH "" FORCE)
	set(CMAKE_CXX_COMPILER "/usr/bin/g++" CACHE PATH "" FORCE)
endif()

add_executable(app main.cpp)

find_package(Crow CONFIG REQUIRED)

include(FetchContent)
FetchContent_Declare(
	fmt
	GIT_REPOSITORY https://github.com/fmtlib/fmt
	GIT_TAG	e69e5f977d458f2650bb346dadf2ad30c5320281
)
FetchContent_MakeAvailable(fmt)

target_link_libraries(app PRIVATE Crow::Crow asio::asio fmt::fmt)

if (WIN32)
	add_custom_command( 
	TARGET app 
	COMMAND ${CMAKE_COMMAND} ARGS -E copy_directory "${CMAKE_SOURCE_DIR}/templates" "${CMAKE_CURRENT_BINARY_DIR}/templates")

	add_custom_command( 
	TARGET app 
	COMMAND ${CMAKE_COMMAND} ARGS -E copy_directory "${CMAKE_SOURCE_DIR}/static" "${CMAKE_CURRENT_BINARY_DIR}/static")
endif()
