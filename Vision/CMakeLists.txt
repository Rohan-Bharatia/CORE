include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(Vision STATIC
    ImageProcessing.c
    ObjectDetection.c
    FeatureTracking.c
    Camera.c
)

target_link_directories(Vision PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
