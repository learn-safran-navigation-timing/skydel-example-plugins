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

set_target_properties(hil_observer_plugin PROPERTIES CXX_STANDARD 17)

install(TARGETS hil_observer_plugin RUNTIME DESTINATION ${PLUGIN_INSTALL_DIR})
