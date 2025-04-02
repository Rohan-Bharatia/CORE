include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(Navigation STATIC
    PathPlanning.c
    SLAM.c
    Mapping.c
)

target_link_directories(Navigation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
