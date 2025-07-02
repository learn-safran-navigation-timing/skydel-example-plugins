set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB RAPI_PLUGIN_SRC *.cpp *.ui)

add_library(rapi_plugin SHARED
    ${RAPI_PLUGIN_SRC}
    )

target_link_libraries(rapi_plugin PUBLIC
    SkydelPlugin
    skydel_rapi
    )

target_compile_definitions(rapi_plugin PRIVATE PLUGIN_IID="rapi_plugin"
                                               PLUGIN_FILE="rapi_plugin.json")

install(TARGETS rapi_plugin RUNTIME DESTINATION ${PLUGIN_INSTALL_DIR})
