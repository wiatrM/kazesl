SET_SOURCE_FILES_PROPERTIES(${PROTO_SRC} ${PROTO_INCL} PROPERTIES GENERATED TRUE)
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})

protobuf_generate_cpp(PROTO_SRC PROTO_INCL
   "${LIBRARY_MODULE_COMMON_PATH}/proto/kaze-protocol.proto"
)

set (PROTO_SRC  ${PROTO_SRC} PARENT_SCOPE)
set (PROTO_INCL ${PROTO_INCL} PARENT_SCOPE)

#set library
add_library (kaze-proto3 STATIC ${PROTO_SRC} ${PROTO_INCL})
target_link_libraries(kaze-proto3 protobuf::libprotobuf)
