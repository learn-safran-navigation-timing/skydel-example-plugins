set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Network REQUIRED)

file(GLOB RADIO_TIME_OBSERVER_PLUGIN_SRC *.cpp *.ui)

add_library(radio_time_observer_plugin SHARED
    ${RADIO_TIME_OBSERVER_PLUGIN_SRC}
	runtime_objects.h
    )

target_link_libraries(radio_time_observer_plugin PUBLIC
    SkydelPlugin
    Qt5::Network
    )

target_compile_definitions(radio_time_observer_plugin PRIVATE PLUGIN_IID="radio_time_observer_plugin"
                                                              PLUGIN_FILE="radio_time_observer_plugin.json")

install(TARGETS radio_time_observer_plugin RUNTIME DESTINATION ${PLUGIN_INSTALL_DIR})
