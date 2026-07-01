// ======================================================================
// \title  Main.cpp
// \brief main program for the F' application. Intended for CLI-based systems (Linux, macOS)
//
// ======================================================================
// Used to access topology functions
#include <ReferenceDeployment/Top/ReferenceDeploymentTopology.hpp>
#include <ReferenceDeployment/Top/ReferenceDeploymentTopologyAc.hpp>
// OSAL initialization
#include <Os/Os.hpp>
// Used for atoi
#include <cstdlib>
// Used for logging to the console
#include <Fw/Logger/Logger.hpp>
#include <Fw/Types/Assert.hpp>

#define FPRIME_UART_NODE DT_CHOSEN(zephyr_console)
const struct device *uart_device = DEVICE_DT_GET(FPRIME_UART_NODE);

/**
 * \brief execute the program
 *
 * This F´ program is designed to run in standard environments (e.g. Linux/macOs running on a laptop). Thus it uses
 * command line inputs to specify how to connect.
 *
 * @param argc: argument count supplied to program
 * @param argv: argument values supplied to program
 * @return: 0 on success, something else on failure
 */
int main(int argc, char* argv[]) {
    Os::init();
    // Setup, cycle, and teardown topology
     // Object for communicating state to the topology
    ReferenceDeployment::TopologyState inputs;
    
    U32 baud_rate = 115200;
    inputs.uartDevice = uart_device;
    inputs.uartBaud = baud_rate;
    
    Fw::Logger::log("[F Prime] Initializing topology\n");
    ReferenceDeployment::setupTopology(inputs);
    Fw::Logger::log("[F Prime] Entering main loop\n");
    
    while(true) {
        ReferenceDeployment::rateDriver.cycle();  // Program loop cycling rate groups at 1Hz
    }
    Fw::Logger::log("[F Prime] Resetting main loop\n");
    ReferenceDeployment::teardownTopology(inputs);
    return 0;
}