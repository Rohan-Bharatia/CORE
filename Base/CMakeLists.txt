include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(Base STATIC
    Analog.c
    Digital.c
    Time.c
    Interrupts.c
    Mempool.c
    Serial.c
    I2C.c
    SPI.c
    CAN.c
    Server.c
)

target_link_directories(Base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
