####
# This sets up the build system for the 'fprime-nucleo_h723zg-zephyr-reference' project, including
# components and deployments from project.cmake. In addition, it imports the core F Prime components.
####

cmake_minimum_required(VERSION 3.24.2)

list(APPEND BOARD_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/lib/fprime-stm32h7-zephyr")
find_package(Zephyr HINTS "${CMAKE_CURRENT_LIST_DIR}/lib/zephyr-workspace")
project(fprime-nucleo_h723zg-zephyr-reference C CXX)

# We need to reduce the ram and flash usage to allow for more components.
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -ffunction-sections -fdata-sections -flto")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -ffunction-sections -fdata-sections -flto")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections -Wl,-s -flto")
endif()

# Put in an option to force the device back into programable state for automated testing
option(FPRIME_CI_FAILSAFE_ENABLED "Cycle count before a forced reset to programable state" OFF)
if (FPRIME_CI_FAILSAFE_ENABLED)
    set(FPRIME_CI_FAILSAFE_CYCLE_COUNT 6000 CACHE STRING "Cycles before a forced reset")
    add_compile_definitions(FPRIME_CI_FAILSAFE_CYCLE_COUNT=${FPRIME_CI_FAILSAFE_CYCLE_COUNT})
endif()

###
# F' Core Setup
# This includes all of the F prime core components, and imports the make-system.
###
include("${CMAKE_CURRENT_LIST_DIR}/lib/fprime/cmake/FPrime.cmake")
# NOTE: register custom targets between these two lines
fprime_setup_included_code()


# This includes project-wide objects
include("${CMAKE_CURRENT_LIST_DIR}/project.cmake")

# Move deployment-owned static data into DTCM. These files hold the topology
# objects and context arrays, not driver DMA buffers.
if(CONFIG_CODE_DATA_RELOCATION)
    if(TARGET ReferenceDeployment_Top)
        target_compile_options(ReferenceDeployment_Top PRIVATE -fno-lto)
    endif()
    zephyr_code_relocate(
        FILES
            "${CMAKE_CURRENT_BINARY_DIR}/ReferenceDeployment/Top/ReferenceDeploymentTopologyAc.cpp"
            "${CMAKE_CURRENT_LIST_DIR}/ReferenceDeployment/Top/ReferenceDeploymentTopology.cpp"
        LOCATION DTCM_DATA_BSS
        NOKEEP
    )
endif()

set_target_properties(Svc_FatalHandler PROPERTIES EXCLUDE_FROM_ALL TRUE)
