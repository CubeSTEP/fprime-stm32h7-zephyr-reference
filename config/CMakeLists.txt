add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ComFprimeConfig")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/PlatformCfg")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/AcConstants")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/FpConstants")

register_fprime_config(
    fprime-nucleo_h723zg-zephyr-reference-config
  CONFIGURATION_OVERRIDES
    "${CMAKE_CURRENT_LIST_DIR}/TlmChanImplCfg.hpp"
    "${CMAKE_CURRENT_LIST_DIR}/CommandDispatcherImplCfg.hpp"
    "${CMAKE_CURRENT_LIST_DIR}/FpConfig.h" 
    "${CMAKE_CURRENT_LIST_DIR}/PrmDbImplCfg.hpp"
  INTERFACE # No buildable files generated
)
