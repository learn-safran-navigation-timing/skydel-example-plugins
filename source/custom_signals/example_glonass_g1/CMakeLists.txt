set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB EXAMPLE_G1_SRC *.cpp)

add_library(custom_g1 SHARED ${EXAMPLE_G1_SRC})

target_link_libraries(custom_g1 PUBLIC SkydelPlugin custom_signal_common)

set_target_properties(custom_g1 PROPERTIES CXX_STANDARD 17)

target_compile_definitions(custom_g1 PRIVATE PLUGIN_IID="custom_g1"
                                             PLUGIN_FILE="custom_g1.json")

install(TARGETS custom_g1 RUNTIME DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES custom_g1_downlink.csv custom_g1.xml
        DESTINATION ${PLUGIN_INSTALL_DIR})
