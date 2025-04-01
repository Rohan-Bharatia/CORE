include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(Motor STATIC
    DC.c
    Servo.c
    Stepper.c
    BLDC.c
    LinearActuator.c
)

target_link_directories(Motor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
