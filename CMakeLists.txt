cmake_minimum_required(VERSION 3.10)

project(CORE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Base)

file(GLOB CORE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Base/*.c)

if (CORE_SOURCES)
    add_library(${PROJECT_NAME} STATIC ${CORE_SOURCES})
    target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Base
    )

    target_link_libraries(${PROJECT_NAME} PUBLIC Base)
endif()
