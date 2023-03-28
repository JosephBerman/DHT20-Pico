file(GLOB FILES *.cpp *.h)

add_library(dht STATIC
        ${FILES}
        )

target_link_libraries(dht pico_stdlib hardware_i2c)

# Link with the pico stdlib


target_include_directories(dht PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        )

