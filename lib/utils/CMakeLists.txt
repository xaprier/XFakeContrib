cmake_minimum_required(VERSION 3.0...3.20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Svg Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Svg Widgets)

# Specify the directory to check
set(
  DIRECTORIES_TO_CHECK
  "${CMAKE_CURRENT_SOURCE_DIR}/adapters" # get adapters
  "${CMAKE_CURRENT_SOURCE_DIR}/settings" # get settings
  "${CMAKE_CURRENT_SOURCE_DIR}/data" # get data
  "${CMAKE_CURRENT_SOURCE_DIR}/helpers" # get helpers
  "${CMAKE_CURRENT_SOURCE_DIR}/style" # get style
  "${CMAKE_CURRENT_SOURCE_DIR}/faker" # get faker
)

set(ALL_FILES "")
set(INCLUDE_DIRS "")
# getting all files for this module
foreach(DIRECTORY ${DIRECTORIES_TO_CHECK})
  if(NOT EXISTS ${DIRECTORY})
    message(FATAL_ERROR "Directory ${DIRECTORY} does not exist or no CMake script for this directory.")
  else()
    message(STATUS "Appending all files for ${DIRECTORY}")
    # get necessary files for each directory
    file(GLOB_RECURSE CPP_FILES ${DIRECTORY}/src/*.cpp)
    file(GLOB_RECURSE HPP_FILES ${DIRECTORY}/include/*.hpp)
    file(GLOB_RECURSE UI_FILES  ${DIRECTORY}/design/*.ui)
    file(GLOB_RECURSE CONFIG_FILES ${DIRECTORY}/include/*.hpp.cmake)

    foreach(file ${CONFIG_FILES})
      message(STATUS "Configuring file: ${file}")
      get_filename_component(FILE_NAME ${file} NAME)
      string(REPLACE ".hpp.cmake" ".hpp" FILE_NAME ${FILE_NAME})
      configure_file(
        ${file}
        ${CMAKE_CURRENT_BINARY_DIR}/include/${FILE_NAME}
      )
      include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)
      list(APPEND INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/include)
    endforeach()

    list(APPEND ALL_FILES ${CPP_FILES} ${HPP_FILES} ${UI_FILES})
    list(APPEND INCLUDE_DIRS ${DIRECTORY}/include)
    include_directories(${DIRECTORY}/include)
  endif()
endforeach()

project(XFakeContribUtils) # we define this project name later to get the main project name in configure_file

add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

set(INTERNAL_LIBRARIES
)

set(EXTERNAL_LIBRARIES
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Svg
  Qt${QT_VERSION_MAJOR}::Widgets
  Logger
  faker-cxx
)

set(LIBRARIES
    ${EXTERNAL_LIBRARIES}
    ${INTERNAL_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARIES})

foreach(dir IN LISTS INCLUDE_DIRS)
  target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${dir}>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
  )
endforeach()

add_executable(${PROJECT_NAME}_TEST main.cpp)
target_link_libraries(${PROJECT_NAME}_TEST PRIVATE ${PROJECT_NAME} ${LIBRARIES})

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

