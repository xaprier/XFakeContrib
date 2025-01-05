cmake_minimum_required(VERSION 3.0...3.20)

project(XFakeContribFaker)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_subdirectory(lib) # build external/internal libs

option(USE_SYSTEM_DEPENDENCIES "Use fmt and GTest from system" OFF)
option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_TESTING "Build tests" OFF)
option(CODE_COVERAGE "Build faker-cxx with coverage support" OFF)

file(GLOB CPP_FILES "src/*.cpp")
file(GLOB HPP_FILES "include/*.hpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(${PROJECT_NAME} SHARED ${CPP_FILES} ${HPP_FILES})

set(LIBRARIES
  faker-cxx
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)

add_executable(${PROJECT_NAME}_TEST main.cpp)
target_link_libraries(${PROJECT_NAME}_TEST ${PROJECT_NAME} ${LIBRARIES})

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
