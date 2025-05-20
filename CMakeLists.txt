cmake_minimum_required(VERSION 3.10...3.20)

project(
    XFakeContrib
    VERSION 1.0.1
    DESCRIPTION "Fake Contribution maker for Github"
    HOMEPAGE_URL "https://github.com/xaprier/XFakeContrib"
    LANGUAGES CXX)

set(PROJECT_ORGANIZATION "xaprier")

add_subdirectory(resources)
add_subdirectory(lib) # build external/internal libs

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1) # required for clangd analyzes

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Svg Concurrent LinguistTools Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Svg Concurrent LinguistTools Network)

file(GLOB_RECURSE CPP_FILES src/*.cpp)
file(GLOB_RECURSE HPP_FILES include/*.hpp)
file(GLOB_RECURSE UI_FILES  design/*.ui)
file(GLOB_RECURSE QRC_FILES resources/*.qrc)

set(PROJECT_SOURCES
    ${CPP_FILES}
    ${HPP_FILES}
    ${UI_FILES}
    ${QRC_FILES}
)

set(LANGS tr_TR)

# 1 - first create an translation file to translate texts.
set(QM_FILES "")

foreach(LANG ${LANGS})
    qt_create_translation(QM_FILE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/resources/translations/translation_${LANG}.ts)
    list(APPEND QM_FILES ${QM_FILE})
endforeach()

# 2 - translate files using linguist
# 3 - after translate and build we should configure file to get file to correct directory
foreach(QM_FILE ${QM_FILES})
    if(EXISTS ${QM_FILE})
        configure_file(${QM_FILE} ${CMAKE_SOURCE_DIR}/resources/translations COPYONLY)
    else()
        list(APPEND PROJECT_SOURCES ${TS_FILES} ${QM_FILES})
    endif()
endforeach()

if(WIN32)
    set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/resources/icon.rc")
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
    XFakeContribGit
    XFakeContribWidgets
    XFakeContribUtils
)

set(EXTERNAL_LIBRARIES
    Qt${QT_VERSION_MAJOR}::Core 
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Concurrent
    Qt${QT_VERSION_MAJOR}::Network
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

if(WIN32)
    install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION .
        RUNTIME DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
else()
    install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION .
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:${PROJECT_NAME}Widgets>
        $<TARGET_FILE:${PROJECT_NAME}Utils>
        $<TARGET_FILE:${PROJECT_NAME}Git>
        $<TARGET_FILE:XQPwdLineEdit>
        $<TARGET_FILE:XQWidgetComposer>
        $<TARGET_FILE:XQCircularLoadingIndicator>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()
