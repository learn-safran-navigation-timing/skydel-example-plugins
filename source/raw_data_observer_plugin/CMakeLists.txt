set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(
  Qt5
  COMPONENTS Network
  REQUIRED)

file(GLOB RAW_DATA_OBSERVER_PLUGIN_SRC *.cpp *.ui)

add_library(raw_data_observer_plugin SHARED ${RAW_DATA_OBSERVER_PLUGIN_SRC})

target_link_libraries(raw_data_observer_plugin
                      PUBLIC SkydelPlugin plugin_widgets Qt5::Network)

set_target_properties(raw_data_observer_plugin PROPERTIES CXX_STANDARD 17)

target_compile_definitions(
  raw_data_observer_plugin PRIVATE PLUGIN_IID="raw_data_observer_plugin"
                                   PLUGIN_FILE="raw_data_observer_plugin.json")

install(TARGETS raw_data_observer_plugin
        RUNTIME DESTINATION ${PLUGIN_INSTALL_DIR})
