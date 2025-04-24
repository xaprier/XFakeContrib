set(
  DIRECTORIES_TO_CHECK
  "${CMAKE_CURRENT_SOURCE_DIR}/XQCircularLoadingIndicator" # get external XQCircularLoadingIndicator
  "${CMAKE_CURRENT_SOURCE_DIR}/XQWidgetComposer" # get external XQWidgetComposer
  "${CMAKE_CURRENT_SOURCE_DIR}/XQPwdLineEdit" # get external XQPwdLineEdit
  "${CMAKE_CURRENT_SOURCE_DIR}/faker-cxx" # get external faker-cxx
  "${CMAKE_CURRENT_SOURCE_DIR}/logger" # get external logger
)


foreach(DIRECTORY ${DIRECTORIES_TO_CHECK})
# Check if the directory exists
if(NOT EXISTS ${DIRECTORY} OR NOT EXISTS ${DIRECTORY}/CMakeLists.txt)
message(FATAL_ERROR "Directory ${DIRECTORY} does not exist.\nYou should get submodules while cloning(git clone --recurse-submodules ...).\nOr you can just get modules(git submodule update --init --recursive)")
else()
add_subdirectory(${DIRECTORY})
endif()
endforeach()

# to link a static library to a shared library, we should compile it with -fPIC as below
set_target_properties(faker-cxx PROPERTIES POSITION_INDEPENDENT_CODE ON)