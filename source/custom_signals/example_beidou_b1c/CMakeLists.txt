set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB EXAMPLE_B1C_SRC *.cpp)

add_library(custom_b1c SHARED ${EXAMPLE_B1C_SRC})

target_link_libraries(custom_b1c PUBLIC SkydelPlugin custom_signal_common)

set_target_properties(custom_b1c PROPERTIES CXX_STANDARD 17)

target_compile_definitions(custom_b1c PRIVATE PLUGIN_IID="custom_b1c"
                                              PLUGIN_FILE="custom_b1c.json")

install(TARGETS custom_b1c RUNTIME DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES custom_b1c_downlink.csv custom_b1c.xml
        DESTINATION ${PLUGIN_INSTALL_DIR})
