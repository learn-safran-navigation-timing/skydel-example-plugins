set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(
  Qt5
  COMPONENTS Network
  REQUIRED)

file(GLOB PLUGIN_DIALOGS_SRC *.cpp *.ui)

add_library(plugin_dialogs STATIC ${PLUGIN_DIALOGS_SRC})

target_include_directories(plugin_dialogs PUBLIC ${PLUGIN_LIBRARIES_DIR})

target_link_libraries(plugin_dialogs PRIVATE Qt5::Core Qt5::Network
                                             Qt5::Widgets)
