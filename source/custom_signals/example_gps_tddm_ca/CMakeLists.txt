set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB EXAMPLE_TDDM_CA_SRC *.cpp)

add_library(custom_tddm_ca SHARED ${EXAMPLE_TDDM_CA_SRC})

target_link_libraries(custom_tddm_ca PUBLIC SkydelPlugin custom_signal_common)

set_target_properties(custom_tddm_ca PROPERTIES CXX_STANDARD 17)

target_compile_definitions(
  custom_tddm_ca PRIVATE PLUGIN_IID="custom_tddm_ca"
                         PLUGIN_FILE="custom_tddm_ca.json")

install(TARGETS custom_tddm_ca RUNTIME DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES custom_tddm_ca_downlink.csv custom_tddm_ca.xml
        DESTINATION ${PLUGIN_INSTALL_DIR})
