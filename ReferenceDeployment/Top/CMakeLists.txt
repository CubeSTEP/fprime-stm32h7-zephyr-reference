####
# F Prime CMakeLists.txt:
#
# SOURCES: list of source files (to be compiled)
# AUTOCODER_INPUTS: list of files to be passed to the autocoders
# DEPENDS: list of libraries that this module depends on
#
# More information in the F´ CMake API documentation:
# https://fprime.jpl.nasa.gov/latest/docs/reference/api/cmake/API/
#
####

if (NO_GDS)
    register_fprime_module(
        AUTOCODER_INPUTS
            "${CMAKE_CURRENT_LIST_DIR}/instances-no_gds.fpp"
            "${CMAKE_CURRENT_LIST_DIR}/topology-no_gds.fpp"
        SOURCES
            "${CMAKE_CURRENT_LIST_DIR}/ReferenceDeploymentTopology.cpp"
        DEPENDS
            Components_Led
            Components_TextLogger
            Fw_Logger
            Svc_Subtopologies_ComFprime
    )
elseif (BOARD STREQUAL "stm32h753i_eval")
    register_fprime_module(
        AUTOCODER_INPUTS
            "${CMAKE_CURRENT_LIST_DIR}/instances-stm32h753i_eval.fpp"
            "${CMAKE_CURRENT_LIST_DIR}/topology-stm32h753i_eval.fpp"
        SOURCES
            "${CMAKE_CURRENT_LIST_DIR}/ReferenceDeploymentTopology.cpp"
        DEPENDS
            Components_DspLCD
            Components_Led
            Components_Potentiometer
            Fw_Logger
    )
elseif (BOARD STREQUAL "nucleo_h723zg")
    register_fprime_module(
        AUTOCODER_INPUTS
            "${CMAKE_CURRENT_LIST_DIR}/instances-nucleo_h723zg.fpp"
            "${CMAKE_CURRENT_LIST_DIR}/topology-nucleo_h723zg.fpp"
        SOURCES
            "${CMAKE_CURRENT_LIST_DIR}/ReferenceDeploymentTopology.cpp"
         DEPENDS
            Fw_Logger
            Svc_Subtopologies_ComFprime
    )
endif()
