cmake_minimum_required(VERSION 3.10...3.20)

project(
    XFakeContrib
    VERSION 0.1.0
    DESCRIPTION "Fake Contribution maker for Github"
    HOMEPAGE_URL "https://github.com/SFENX/XFakeContrib"
    LANGUAGES CXX)

set(PROJECT_ORGANIZATION "SFENX")

add_subdirectory(lib) # build external/internal libs

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1) # required for clangd analyzes

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Svg Concurrent LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Svg Concurrent LinguistTools)

file(GLOB_RECURSE CPP_FILES src/*.cpp)
file(GLOB_RECURSE HPP_FILES include/*.hpp)
file(GLOB_RECURSE UI_FILES  design/*.ui)

set(PROJECT_SOURCES
    ${CPP_FILES}
    ${HPP_FILES}
    ${UI_FILES}
)

set(LANGS tr)

# 1 - first create an translation file to translate texts.
set(QM_FILES "")

foreach(LANG ${LANGS})
    qt_create_translation(QM_FILE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/translations/translation_${LANG}.ts)
    list(APPEND QM_FILES ${QM_FILE})
endforeach()

# 2 - translate files using linguist

# 3 - after translate and build we should configure file to get file to correct directory
foreach(QM_FILE ${QM_FILES})
    if(EXISTS ${QM_FILE})
        configure_file(${QM_FILE} ${CMAKE_SOURCE_DIR}/translations COPYONLY)
    else()
        list(APPEND PROJECT_SOURCES ${TS_FILES} ${QM_FILES})
    endif()
endforeach()

if(WIN32)
    set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/res/icon.rc")
    list(APPEND PROJECT_SOURCES ${app_icon_resource_windows})
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

set(INTERNAL_LIBRARIES
    XFakeContribAdapter
    XFakeContribConfig
    XFakeContribData 
    XFakeContribGit
    XFakeContribGithub
    XFakeContribSettings
    XFakeContribResources
    XFakeContribCardManager
    XFakeContribCard
    XFakeContribStyle
    XFakeContribRepositoryCard
    XFakeContribRepositoryManagerCard
    XFakeContribThemeSelectorCard
    XFakeContribUserManagerCard
)

set(EXTERNAL_LIBRARIES
    Qt${QT_VERSION_MAJOR}::Core 
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Concurrent
    Qt${QT_VERSION_MAJOR}::Svg
    Logger
    XQWidgetComposer
    XQPwdLineEdit
    XQCircularLoadingIndicator
)

set(LIBRARIES
    ${EXTERNAL_LIBRARIES}
    ${INTERNAL_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE "include")

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER https://xaprier.dev
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()