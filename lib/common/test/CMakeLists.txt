set (TEST_APP_NAME "${LIB_NAME}-Common-ut")
set (TEST_MODULE_PATH "${LIBRARY_MODULE_COMMON_PATH}/test")

enable_testing()
set (TEST_SRC_PATH  "${TEST_MODULE_PATH}/impl" )

file (GLOB TEST_SOURCE_FILES "${TEST_SRC_PATH}/*.cpp")
include_directories (${LIBRARY_INCLUDE_PATH} ${TEST_THIRD_PARTY_INCLUDE_PATH})
include_directories (${LIBRARY_MODULE_COMMON_PATH}/proto/gen)

add_executable (${TEST_APP_NAME} ${TEST_SOURCE_FILES})
target_link_libraries (${TEST_APP_NAME} ${LIB_NAME} Threads::Threads googletest)

add_test(AllTestLibCommon ${TEST_APP_NAME})
