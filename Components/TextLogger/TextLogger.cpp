// ======================================================================
// \title  TextLogger.cpp
// \author howardl
// \brief  cpp file for TextLogger component implementation class
// ======================================================================

#include "Components/TextLogger/TextLogger.hpp"

namespace Components {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

TextLogger ::TextLogger(const char* const compName) : TextLoggerComponentBase(compName) {}

TextLogger ::~TextLogger() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void TextLogger ::run_handler(FwIndexType portNum, U32 context) {
    // if (!this->isConnected_uartSend_OutputPort(0) || !this->isConnected_allocate_OutputPort(0))
};

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void TextLogger ::TODO_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace Components
