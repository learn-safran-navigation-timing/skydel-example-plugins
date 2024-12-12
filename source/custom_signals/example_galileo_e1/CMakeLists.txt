set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB EXAMPLE_E1_SRC *.cpp)

add_library(custom_e1 SHARED ${EXAMPLE_E1_SRC})

target_link_libraries(custom_e1 PUBLIC SkydelPlugin custom_signal_common)

set_target_properties(custom_e1 PROPERTIES CXX_STANDARD 17)

target_compile_definitions(custom_e1 PRIVATE PLUGIN_IID="custom_e1"
                                             PLUGIN_FILE="custom_e1.json")

install(TARGETS custom_e1 RUNTIME DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES custom_e1_downlink.csv custom_e1.xml
        DESTINATION ${PLUGIN_INSTALL_DIR})
