set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB EXAMPLE_QZSS_CA_SRC *.cpp)

add_library(custom_qzss_ca SHARED ${EXAMPLE_QZSS_CA_SRC})

target_link_libraries(custom_qzss_ca PUBLIC SkydelPlugin custom_signal_common)

target_compile_definitions(
  custom_qzss_ca PRIVATE PLUGIN_IID="custom_qzss_ca"
                         PLUGIN_FILE="custom_qzss_ca.json")

install(TARGETS custom_qzss_ca RUNTIME DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES custom_qzss_ca_downlink.csv custom_qzss_ca.xml
        DESTINATION ${PLUGIN_INSTALL_DIR})
