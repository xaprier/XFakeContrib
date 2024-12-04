cmake_minimum_required(VERSION 3.0...3.20)

set(PROJECT_NAME "XFakeContrib")
set(VERSION 0.1.0)
set(DESCRIPTION "Fake Contribution maker for Github")
set(HOMEPAGE_URL "https://github.com/SFENX/XFakeContrib")
set(ORGANIZATION "SFENX")
    
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Config.hpp.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/include/Config.hpp
)

project(XFakeContribConfig)

set(HPP_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/include/Config.hpp
)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)

if (NOT WIN32)
    install(FILES ${HPP_FILES} DESTINATION include/${PROJECT_NAME})
endif()
