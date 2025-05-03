cmake_minimum_required(VERSION 3.0...3.20)

project(XFakeContribWidgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Svg Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Svg Concurrent)

# Specify the directory to check
set(
  DIRECTORIES_TO_CHECK
  "${CMAKE_CURRENT_SOURCE_DIR}/export" # get export
  "${CMAKE_CURRENT_SOURCE_DIR}/Card" # get Card
  "${CMAKE_CURRENT_SOURCE_DIR}/ContribCard" # get ContribCard
  "${CMAKE_CURRENT_SOURCE_DIR}/RepositoryCard" # get RepositoryCard
  "${CMAKE_CURRENT_SOURCE_DIR}/RepositoryManagerCard" # get RepositoryManagerCard
  "${CMAKE_CURRENT_SOURCE_DIR}/UserManagerCard" # get UserManagerCard
  "${CMAKE_CURRENT_SOURCE_DIR}/CardManager" # get CardManager
  "${CMAKE_CURRENT_SOURCE_DIR}/ThemeSelectorCard" # get ThemeSelectorCard
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

    list(APPEND ALL_FILES ${CPP_FILES} ${HPP_FILES} ${UI_FILES})
    list(APPEND INCLUDE_DIRS ${DIRECTORY}/include)
    include_directories(${DIRECTORY}/include)
  endif()
endforeach()

add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

set(INTERNAL_LIBRARIES
    XFakeContribGit
    XFakeContribUtils
)

set(EXTERNAL_LIBRARIES
    Qt${QT_VERSION_MAJOR}::Core 
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Svg
    Qt${QT_VERSION_MAJOR}::Concurrent
    XQPwdLineEdit
    XQWidgetComposer
    XQCircularLoadingIndicator
    Logger
    faker-cxx
)

set(LIBRARIES
    ${EXTERNAL_LIBRARIES}
    ${INTERNAL_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PRIVATE WIDGETS_LIBRARY)

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

