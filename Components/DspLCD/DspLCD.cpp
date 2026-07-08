// ======================================================================
// \title  DspLCD.cpp
// \author thakkar
// \brief  cpp file for DspLCD component implementation class
// ======================================================================

#include "Components/DspLCD/DspLCD.hpp"

namespace ReferenceDeployment {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

DspLCD ::DspLCD(const char* const compName) : DspLCDComponentBase(compName) {}

DspLCD ::~DspLCD() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void DspLCD ::run_handler(FwIndexType portNum, U32 context) {
    // TODO
}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void DspLCD ::LCDI2CBusWrite_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, U32 data) {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace ReferenceDeployment
