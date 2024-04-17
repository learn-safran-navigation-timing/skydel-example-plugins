set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Network REQUIRED)

file(GLOB TRANSMITTTER_OBSERVER_PLUGIN_SRC *.cpp *.ui)

add_library(transmitter_observer_plugin SHARED
    ${TRANSMITTTER_OBSERVER_PLUGIN_SRC}
    )

target_link_libraries(transmitter_observer_plugin PUBLIC
    SkydelPlugin
    Qt5::Network
    )

set_target_properties(transmitter_observer_plugin PROPERTIES CXX_STANDARD 17)

target_compile_definitions(transmitter_observer_plugin PRIVATE PLUGIN_IID="transmitter_observer_plugin"
                                                               PLUGIN_FILE="transmitter_observer_plugin.json")

install(TARGETS transmitter_observer_plugin RUNTIME DESTINATION ${PLUGIN_INSTALL_DIR})
