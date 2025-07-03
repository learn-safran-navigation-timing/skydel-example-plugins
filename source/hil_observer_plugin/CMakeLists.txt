set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB HIL_OBSERVER_PLUGIN_SRC *.cpp *.ui)

add_library(hil_observer_plugin SHARED
    ${HIL_OBSERVER_PLUGIN_SRC}
    )

target_link_libraries(hil_observer_plugin PUBLIC
    SkydelPlugin
    )

target_compile_definitions(hil_observer_plugin PRIVATE PLUGIN_IID="hil_observer_plugin"
                                                       PLUGIN_FILE="hil_observer_plugin.json")

install(TARGETS hil_observer_plugin RUNTIME DESTINATION ${PLUGIN_INSTALL_DIR})
