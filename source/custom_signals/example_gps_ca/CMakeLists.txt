set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB EXAMPLE_CA_SRC *.cpp)

add_library(custom_ca SHARED ${EXAMPLE_CA_SRC})

target_link_libraries(custom_ca PUBLIC SkydelPlugin custom_signal_common)

set_target_properties(custom_ca PROPERTIES CXX_STANDARD 17)

target_compile_definitions(custom_ca PRIVATE PLUGIN_IID="custom_ca"
                                             PLUGIN_FILE="custom_ca.json")

install(TARGETS custom_ca RUNTIME DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES custom_ca_downlink.csv custom_ca.xml
        DESTINATION ${PLUGIN_INSTALL_DIR})
