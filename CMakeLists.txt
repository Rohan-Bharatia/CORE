cmake_minimum_required(VERSION 3.10)

project(CORE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Base)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Motor)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Controller)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Sensor)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Navigation)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vision)

file(GLOB CORE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Base/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Motor/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Sensor/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Navigation/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Vision/*.c
)

if (CORE_SOURCES)
    add_library(${PROJECT_NAME} STATIC ${CORE_SOURCES})
    target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Base
        ${CMAKE_CURRENT_SOURCE_DIR}/Motor
        ${CMAKE_CURRENT_SOURCE_DIR}/Controller
        ${CMAKE_CURRENT_SOURCE_DIR}/Sensor
        ${CMAKE_CURRENT_SOURCE_DIR}/Navigation
        ${CMAKE_CURRENT_SOURCE_DIR}/Vision
    )

    target_link_libraries(${PROJECT_NAME} PUBLIC Base Motor Controller Sensor Navigation Vision)
endif()
