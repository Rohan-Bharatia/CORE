include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(Sensor STATIC
    IMU.c
    Encoder.c
    Distance.c
    Force.c
    Power.c
    Color.c
    GPS.c
)

target_link_directories(Sensor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
