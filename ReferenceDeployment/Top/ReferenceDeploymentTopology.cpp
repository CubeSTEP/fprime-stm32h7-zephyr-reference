// ======================================================================
// \title  ReferenceDeploymentTopology.cpp
// \brief cpp file containing the topology instantiation code
//
// ======================================================================
// Provides access to autocoded functions
#include <ReferenceDeployment/Top/ReferenceDeploymentTopologyAc.hpp>
// Note: Uncomment when using Svc:TlmPacketizer
//#include <ReferenceDeployment/Top/ReferenceDeploymentPacketsAc.hpp>

// Necessary project-specified types
#include <Fw/Types/MallocAllocator.hpp>
#include <Os/Mutex.hpp>
#include <Fw/Logger/Logger.hpp>

// Public functions for use in main program are namespaced with deployment module ReferenceDeployment
// This is also the namespace where the topology components are instantiated by FPP.
namespace ReferenceDeployment {

// Instantiate a malloc allocator for cmdSeq buffer allocation
Fw::MallocAllocator mallocator;

// The reference topology divides the incoming clock signal (1Hz) into sub-signals: 1Hz, 1/2Hz, and 1/4Hz with 0 offset
Svc::RateGroupDriver::DividerSet rateGroupDivisorsSet{{{1, 0}, {2, 0}, {4, 0}}};

// Rate groups may supply a context token to each of the attached children whose purpose is set by the project. The
// reference topology sets each token to zero as these contexts are unused in this project.
U32 rateGroup1Context[Svc::ActiveRateGroup::CONNECTION_COUNT_MAX] = {};
U32 rateGroup2Context[Svc::ActiveRateGroup::CONNECTION_COUNT_MAX] = {};
U32 rateGroup3Context[Svc::ActiveRateGroup::CONNECTION_COUNT_MAX] = {};

enum TopologyConstants {
    COMM_PRIORITY = 34,
};

#ifdef STM32H753I_EVAL
    // Constants for ADC Potentiometer Configuration
    U16 potentiometerBuffer[1] = {0};
#endif

/**
 * \brief configure/setup components in project-specific way
 *
 * This is a *helper* function which configures/sets up each component requiring project specific input. This includes
 * allocating resources, passing-in arguments, etc. This function may be inlined into the topology setup function if
 * desired, but is extracted here for clarity.
 */
void configureTopology() {
    // The rate driver period is in milliseconds; rate groups are driven at 1Hz.
    rateDriver.configure(1000);

    // Rate group driver needs a divisor list
    rateGroupDriver.configure(rateGroupDivisorsSet);

    // Rate groups require context arrays.
    rateGroup1.configure(rateGroup1Context, FW_NUM_ARRAY_ELEMENTS(rateGroup1Context));
    rateGroup2.configure(rateGroup2Context, FW_NUM_ARRAY_ELEMENTS(rateGroup2Context));
    rateGroup3.configure(rateGroup3Context, FW_NUM_ARRAY_ELEMENTS(rateGroup3Context));
}

void setupTopology(const TopologyState& state) {
    // Autocoded initialization. Function provided by autocoder.
    initComponents(state);
    // Autocoded id setup. Function provided by autocoder.
    setBaseIds();
    // Autocoded connection wiring. Function provided by autocoder.
    connectComponents();
    // Autocoded command registration. Function provided by autocoder.
    regCommands();
    // Autocoded configuration. Function provided by autocoder.
    configComponents(state);
    // Project-specific component configuration. Function provided above. May be inlined, if desired.
    configureTopology();
    // Autocoded parameter loading. Function provided by autocoder.
    loadParameters();
    // Autocoded task kick-off (active components). Function provided by autocoder.
    startTasks(state);
    // Uplink is configured for receive so a socket task is started
#ifdef NO_GDS
    static Svc::BufferManager::BufferBins bins;
    memset(&bins, 0, sizeof(bins));
    bins.bins[0].bufferSize = ComFprimeConfig::BuffMgr::commsBuffSize;
    bins.bins[0].numBuffers = ComFprimeConfig::BuffMgr::commsBuffCount;

    bufferManager.setup(
        ComFprimeConfig::BuffMgr::commsBuffMgrId,
        0,
        ComFprime::Allocation::memAllocator,
        bins
    );

    uartDriver.configure(state.uartDevice, state.uartBaud);
#else
    comDriver.configure(state.uartDevice, state.uartBaud);
    #ifdef STM32H753I_EVAL
        i2cDriver.open(state.i2cDevice);
        potentiometer.configure(state.adcDeviceSpec, potentiometerBuffer, sizeof(potentiometerBuffer));
        adcDriver.configure(state.adcDeviceSpec);
    #endif
#endif
    
    Os::File::Status status =
        gpioDriver.open(*state.led, Zephyr::ZephyrGpioDriver::GpioConfiguration::OUT);
    if (status != Os::File::Status::OP_OK) {
        Fw::Logger::log("[ERROR] Failed to open GPIO pin\n");
    }
    
    // Start rate groups
    rateDriver.start();
}

void teardownTopology(const TopologyState& state) {
    // Autocoded (active component) task clean-up. Functions provided by topology autocoder.
    stopTasks(state);
    freeThreads(state);
};  
}// namespace ReferenceDeployment