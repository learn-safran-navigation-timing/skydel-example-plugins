file(GLOB CUSTOM_SIGNAL_COMMON_SRC *.cpp)

add_library(custom_signal_common STATIC ${CUSTOM_SIGNAL_COMMON_SRC})

target_include_directories(custom_signal_common
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(UNIX)
  target_compile_options(custom_signal_common PUBLIC -fPIC)
endif()
