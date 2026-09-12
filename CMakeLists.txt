cmake_minimum_required(VERSION 3.16)
project(DouyinSessionTool VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED CEF_ROOT)
    set(CEF_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/cef_binary")
endif()

set(CEF_INCLUDE_DIR "${CEF_ROOT}/include")
set(CEF_LIB_DIR "${CEF_ROOT}/Release")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CEF_INCLUDE_DIR}
)

add_library(cef_dll_wrapper STATIC
    "${CEF_ROOT}/libcef_dll/wrapper/cef_util_win.cc"
)

add_executable(DouyinSessionTool WIN32
    src/main.cc
    src/app.cc
    src/client.cc
)

target_link_libraries(DouyinSessionTool
    cef_dll_wrapper
    "${CEF_LIB_DIR}/libcef.lib"
    comctl32 shlwapi
)

add_custom_command(TARGET DouyinSessionTool POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CEF_LIB_DIR}" "$<TARGET_FILE_DIR:DouyinSessionTool>"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CEF_ROOT}/Resources" "$<TARGET_FILE_DIR:DouyinSessionTool>"
)
