# Specify the directory to check
set(
  DIRECTORIES_TO_CHECK
  "${CMAKE_CURRENT_SOURCE_DIR}/XQCircularLoadingIndicator" # get external XQCircularLoadingIndicator
  "${CMAKE_CURRENT_SOURCE_DIR}/XQWidgetComposer" # get external XQWidgetComposer
  "${CMAKE_CURRENT_SOURCE_DIR}/XQPwdLineEdit" # get external XQPwdLineEdit
  "${CMAKE_CURRENT_SOURCE_DIR}/ContribCard" # get ContribCard
  "${CMAKE_CURRENT_SOURCE_DIR}/RepositoryCard" # get RepositoryCard
  "${CMAKE_CURRENT_SOURCE_DIR}/RepositoryManagerCard" # get RepositoryManagerCard
  "${CMAKE_CURRENT_SOURCE_DIR}/UserManagerCard" # get UserManagerCard
)

foreach(DIRECTORY ${DIRECTORIES_TO_CHECK})
  # Check if the directory exists
  if(NOT EXISTS ${DIRECTORY} OR NOT EXISTS ${DIRECTORY}/CMakeLists.txt)
    message(FATAL_ERROR "Directory ${DIRECTORY} does not exist.\nYou should get submodules while cloning(git clone --recurse-submodules ...).\nOr you can just get modules(git submodule update --init --recursive)")
  else()
    add_subdirectory(${DIRECTORY})
  endif()
endforeach()