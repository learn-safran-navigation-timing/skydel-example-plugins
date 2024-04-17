set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB SIMPLE_PLUGIN_SRC *.cpp *.ui)

add_library(simple_plugin SHARED
    ${SIMPLE_PLUGIN_SRC}
    )

target_link_libraries(simple_plugin PUBLIC
    SkydelPlugin
    )

set_target_properties(simple_plugin PROPERTIES CXX_STANDARD 17)

target_compile_definitions(simple_plugin PRIVATE PLUGIN_IID="simple_plugin"
                                                 PLUGIN_FILE="simple_plugin.json")

install(TARGETS simple_plugin RUNTIME DESTINATION ${PLUGIN_INSTALL_DIR})
