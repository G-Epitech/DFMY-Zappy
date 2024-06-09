include_directories(../../includes)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../libs)

enable_testing()

add_executable(zappy_server_tests)

add_subdirectory(types)

add_library(clcc STATIC IMPORTED)
set_property(TARGET clcc
        PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/../libs/clcc/libclcc.a
)

target_link_libraries(zappy_server_tests
        clcc
        criterion
        zappy_server_core
)
