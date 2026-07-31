file(GLOB PLUGIN_WIDGETS_SRC *.cpp *.ui)

qt5_add_resources(PLUGIN_WIDGETS_SRC resources/resources.qrc)

add_library(plugin_widgets STATIC ${PLUGIN_WIDGETS_SRC})

target_include_directories(plugin_widgets PUBLIC ${PLUGIN_LIBRARIES_DIR})

target_link_libraries(plugin_widgets PRIVATE plugin_dialogs Qt5::Core
                                             Qt5::Network Qt5::Widgets)
