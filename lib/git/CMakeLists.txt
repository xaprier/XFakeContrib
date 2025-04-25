cmake_minimum_required(VERSION 3.0...3.20)

project(XFakeContribGit)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Network)

file(GLOB CPP_FILES "src/*.cpp")
file(GLOB HPP_FILES "include/*.hpp")
file(GLOB TEST_FILES "tests/*")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(${PROJECT_NAME} SHARED ${CPP_FILES} ${HPP_FILES})

set(LIBRARIES
  Qt${QT_VERSION_MAJOR}::Core 
  Qt${QT_VERSION_MAJOR}::Widgets 
  Qt${QT_VERSION_MAJOR}::Network
  XFakeContribUtils
  Logger
  faker-cxx
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tests>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)

enable_testing()
add_executable(${PROJECT_NAME}_TEST 
  main.cpp 
  ${TEST_FILES}
)

target_link_libraries(${PROJECT_NAME}_TEST ${PROJECT_NAME} ${LIBRARIES})
add_test(NAME ${PROJECT_NAME}_TEST COMMAND ${PROJECT_NAME}_TEST)

# Installation rules
install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION .
)

if (NOT WIN32)
    install(FILES ${HPP_FILES} DESTINATION include/${PROJECT_NAME})
    install(EXPORT ${PROJECT_NAME}Targets
      FILE ${PROJECT_NAME}Config.cmake
      NAMESPACE ${PROJECT_NAME}::
      DESTINATION lib/cmake/${PROJECT_NAME}
    )
endif()
