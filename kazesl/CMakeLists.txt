#configure variables
set (APP_NAME "kazesl")

#configure modules
set (APP_MODULE_PATH "${PROJECT_SOURCE_DIR}/kazesl")

#set includes
include_directories (${LIBRARY_INCLUDE_PATH} ${THIRD_PARTY_INCLUDE_PATH} ${APP_MODULE_PATH})

#get kazesl-version
message(STATUS "Resolving GIT Version")

set(_build_version "unknown")

find_package(Git)
if(GIT_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --tags
    WORKING_DIRECTORY "${local_dir}"
    OUTPUT_VARIABLE _build_version
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  message( STATUS "GIT hash: ${_build_version}")

  execute_process(
    COMMAND git rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY "${local_dir}"
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  message( STATUS "GIT branch: ${GIT_BRANCH}")
else()
  message(STATUS "GIT not found")
endif()

configure_file(${PROJECT_SOURCE_DIR}/kazesl/app/gitversion.hpp.in ${APP_MODULE_PATH}/app/gitversion.hpp @ONLY)

#add executables
file(GLOB_RECURSE PROJECT_SOURCE_FILES
  ${APP_MODULE_PATH}/app/*.cpp
  ${APP_MODULE_PATH}/core/*.cpp
  ${APP_MODULE_PATH}/network/*.cpp
  ${APP_MODULE_PATH}/node/*.cpp
  ${APP_MODULE_PATH}/server/*.cpp
)

set(PROJECT_SOURCE_FILES ${PROJECT_SOURCE_FILES})

#set testing sources without main.cpp
set(TESTING_SOURCES ${PROJECT_SOURCE_FILES})
list(REMOVE_ITEM TESTING_SOURCES ${APP_MODULE_PATH}/app/impl/main.cpp)

#objects for testing
add_library(kazesl-obj-test OBJECT ${TESTING_SOURCES})

#objects for main
add_library(kazesl-obj OBJECT ${PROJECT_SOURCE_FILES})

#set target executable
add_executable ("${APP_NAME}" $<TARGET_OBJECTS:kazesl-obj>)

#add the library
target_link_libraries ("${APP_NAME}" kazesl-lib Threads::Threads ${THIRD_PARTY_LIBS})


#test
enable_testing()
add_subdirectory (test)
