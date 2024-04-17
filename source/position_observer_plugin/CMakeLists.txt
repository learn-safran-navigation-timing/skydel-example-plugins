set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Network REQUIRED)

add_library(position_observer_plugin SHARED
    position_logger.cpp
    position_observer_plugin.cpp
    position_observer_view.cpp
    position_observer_view.ui
    )

target_link_libraries(position_observer_plugin PUBLIC
    SkydelPlugin
    Qt5::Network
    )

set_target_properties(position_observer_plugin PROPERTIES CXX_STANDARD 17)

target_compile_definitions(position_observer_plugin PRIVATE PLUGIN_IID="position_observer_plugin"
                                                            PLUGIN_FILE="position_observer_plugin.json")

install(TARGETS position_observer_plugin RUNTIME DESTINATION ${PLUGIN_INSTALL_DIR})
