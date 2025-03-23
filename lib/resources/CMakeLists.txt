cmake_minimum_required(VERSION 3.0...3.20)

project(XFakeContribResources)

set(CMAKE_AUTORCC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

file(GLOB QRC_FILES "*.qrc")

if (QT_VERSION_MAJOR EQUAL 6)
    qt6_add_resources(QT_RESOURCES ${QRC_FILES})
else()
    qt5_add_resources(QT_RESOURCES ${QRC_FILES})
endif()

add_library(${PROJECT_NAME} SHARED ${QT_RESOURCES})

target_sources(${PROJECT_NAME} PRIVATE ${QT_RESOURCES})

# Installation rules
install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION .
)

if (NOT WIN32)
    install(EXPORT ${PROJECT_NAME}Targets
      FILE ${PROJECT_NAME}Config.cmake
      NAMESPACE ${PROJECT_NAME}::
      DESTINATION lib/cmake/${PROJECT_NAME}
    )
    execute_process(COMMAND ${CMAKE_COMMAND} -E remove "$ENV{DESTDIR}/share/applications/XFakeContrib.desktop")
    execute_process(COMMAND ${CMAKE_COMMAND} -E remove "$ENV{DESTDIR}/share/icons/hicolor/256x256/apps/XFakeContrib.png")
    install(FILES XFakeContrib.desktop DESTINATION share/applications/ COMPONENT desktop)
    install(FILES XFakeContrib.png DESTINATION share/icons/hicolor/256x256/apps COMPONENT desktop)
else()
    install(FILES XFakeContrib.png DESTINATION . COMPONENT desktop)
    install(FILES XFakeContrib.ico DESTINATION . COMPONENT desktop)
endif()
