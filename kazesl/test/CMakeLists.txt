set (TEST_APP_NAME "runUT")
set (TEST_MODULE_PATH "${APP_MODULE_PATH}/test")


set (TEST_SRC_PATH  "${TEST_MODULE_PATH}" )

include_directories (${LIBRARY_INCLUDE_PATH} ${TEST_THIRD_PARTY_INCLUDE_PATH})

file (GLOB_RECURSE TEST_SOURCE_FILES "${TEST_SRC_PATH}/*.cpp")
set(TEST_SOURCE_FILES ${TEST_SOURCE_FILES})

add_executable (${TEST_APP_NAME} ${TEST_SOURCE_FILES})

target_link_libraries (${TEST_APP_NAME} $<TARGET_OBJECTS:kazesl-obj-test> Threads::Threads googletest ${LIB_NAME} ${THIRD_PARTY_LIBS})

enable_testing()
target_compile_features(${TEST_APP_NAME} PRIVATE cxx_range_for)
add_test(AllTests ${TEST_APP_NAME})
add_test (NAME ${TEST_APP_NAME} COMMAND ${APP_NAME})
