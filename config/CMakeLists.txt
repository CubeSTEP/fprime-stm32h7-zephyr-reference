add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ComFprimeConfig")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/PlatformCfg")

register_fprime_config(
    fprime-nucleo_h723zg-zephyr-reference-config
  CONFIGURATION_OVERRIDES
    "${CMAKE_CURRENT_LIST_DIR}/TlmChanImplCfg.hpp"
    "${CMAKE_CURRENT_LIST_DIR}/CommandDispatcherImplCfg.hpp"
    "${CMAKE_CURRENT_LIST_DIR}/FpConfig.h"
  INTERFACE # No buildable files generated
)
