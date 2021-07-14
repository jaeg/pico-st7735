add_executable(st7735
        main.c
        st7735.c
        )

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(st7735 pico_stdlib hardware_spi)

# create map/bin/hex file etc.
pico_add_extra_outputs(st7735)

# add url via pico_set_program_url
example_auto_set_url(st7735)
