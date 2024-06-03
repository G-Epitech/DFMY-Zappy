set(SOURCE_FILES
        foo.c
)

add_library(${PROJECT_NAME}_core STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME}_core PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME}_core PUBLIC ${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_core)

if (COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
    target_link_libraries(${PROJECT_NAME}_core gcov)
endif()
