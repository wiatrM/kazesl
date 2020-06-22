# CMake build : externals

#configure directories
set (THIRD_PARTY_MODULE_PATH "${PROJECT_SOURCE_DIR}/external")

# -------------------------------------------------------------------------
# GoogleTest

set(GOOGLETEST_ROOT ${THIRD_PARTY_MODULE_PATH}/googletest/googletest CACHE STRING "Google Test source root")
set(GOOGLEMOCK_ROOT ${THIRD_PARTY_MODULE_PATH}/googletest/googlemock CACHE STRING "Google Mock source root")

set(GOOGLETEST_SOURCES
  ${GOOGLETEST_ROOT}/src/gtest-all.cc
  ${GOOGLEMOCK_ROOT}/src/gmock-all.cc
  ${GOOGLEMOCK_ROOT}/src/gmock_main.cc
)

include_directories(
  ${GOOGLETEST_ROOT}
  ${GOOGLETEST_ROOT}/include
  ${GOOGLEMOCK_ROOT}
  ${GOOGLEMOCK_ROOT}/include
)

add_library(googletest ${GOOGLETEST_SOURCES})

# -------------------------------------------------------------------------
# spdlog

#configure directories
set (SPDLOG_MODULE_PATH "${THIRD_PARTY_MODULE_PATH}/spdlog")
set (SPDLOG_INCLUDE_PATH "${SPDLOG_MODULE_PATH}/include")

# -------------------------------------------------------------------------
# ZeroMQ

#configure directories
set (ZEROMQ_ROOT "${THIRD_PARTY_MODULE_PATH}/zeromq")
set (ZEROMQ_INCLUDE_PATH "${ZEROMQ_ROOT}/include")

# -------------------------------------------------------------------------
# JSON

#configure directories
set (JSON_ROOT "${THIRD_PARTY_MODULE_PATH}/json")
set (JSON_INCLUDE_PATH "${JSON_ROOT}")


# -------------------------------------------------------------------------
# boost

find_package( Boost 1.60.0 COMPONENTS program_options system REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )

# -------------------------------------------------------------------------
# boost-beast

set (BEAST_ROOT "${THIRD_PARTY_MODULE_PATH}/beast")
set (BEAST_INCLUDE_PATH "${BEAST_ROOT}/include")

# -------------------------------------------------------------------------
# rocksdb

# -------------------------------------------------------------------------
# gRPC

include(FetchContent)
FetchContent_Declare(
    grpc
    GIT_REPOSITORY https://github.com/grpc/grpc.git
    GIT_TAG        v1.29.1
    GIT_PROGRESS   TRUE
)
set(FETCHCONTENT_QUIET OFF)

FetchContent_MakeAvailable(grpc)


# -------------------------------------------------------------------------
#set variables
set (THIRD_PARTY_INCLUDE_PATH
   ${SPDLOG_INCLUDE_PATH}
   ${ZEROMQ_INCLUDE_PATH}
   ${PROTOBUF_INCLUDE_PATH}
   ${Boost_INCLUDE_DIR}
   ${JSON_INCLUDE_PATH}
   ${BEAST_INCLUDE_PATH}
)

#set variables for tests
set (TEST_THIRD_PARTY_INCLUDE_PATH
   ${GOOGLETEST_ROOT}/include
   ${GOOGLEMOCK_ROOT}/include
)

#set third party libs
set (THIRD_PARTY_LIBS
   ${Boost_LIBRARIES}
   grpc++
)

#export vars
set (THIRD_PARTY_INCLUDE_PATH  ${THIRD_PARTY_INCLUDE_PATH} PARENT_SCOPE)
set (TEST_THIRD_PARTY_INCLUDE_PATH  ${TEST_THIRD_PARTY_INCLUDE_PATH} PARENT_SCOPE)
set (THIRD_PARTY_LIBS  ${THIRD_PARTY_LIBS} PARENT_SCOPE)
