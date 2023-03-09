
add_executable(dht
    dht20.cpp
    )

target_link_libraries(dht pico_stdlib hardware_i2c pico_cyw43_arch_lwip_threadsafe_background )

pico_add_extra_outputs(dht)

pico_enable_stdio_usb(dht 1)
pico_enable_stdio_uart(dht 0)
# add url via pico_set_program_url
example_auto_set_url(dht)

