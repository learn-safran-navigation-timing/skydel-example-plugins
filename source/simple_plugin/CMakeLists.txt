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

install(TARGETS simple_plugin RUNTIME DESTINATION ${PLUGIN_INSTALL_DIR})
