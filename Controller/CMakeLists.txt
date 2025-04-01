include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(Controller STATIC
    PID.c
    StateMachine.c
    KalmanFilter.c
    Kinematics.c
    Trajectory.c
)

target_link_directories(Controller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
