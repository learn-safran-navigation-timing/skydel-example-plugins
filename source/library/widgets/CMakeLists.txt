set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(
  Qt5
  COMPONENTS Network
  REQUIRED)

file(GLOB PLUGIN_WIDGETS_SRC *.cpp *.ui)

add_library(plugin_widgets STATIC ${PLUGIN_WIDGETS_SRC})

target_include_directories(plugin_widgets PUBLIC ${PLUGIN_LIBRARIES_DIR})

target_link_libraries(plugin_widgets PRIVATE plugin_dialogs Qt5::Core
                                             Qt5::Network Qt5::Widgets)
