// ======================================================================
// \title  TextLogger.cpp
// \author howardl
// \brief  cpp file for TextLogger component implementation class
// ======================================================================

#include "Components/TextLogger/TextLogger.hpp"
#include "Fw/Logger/Logger.hpp"

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
    // TODO
    while (true) {
        Fw::Logger::log("Hello serial monitor");
    }
}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void TextLogger ::TODO_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace Components
