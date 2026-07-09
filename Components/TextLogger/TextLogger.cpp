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
    // TODO
    const char* stringLog = "Hello serial monitor\n";
    const FwSizeType bufferSize = static_cast<FwSizeType>(std::strlen(stringLog));
    if (!this->isConnected_uartSend_OutputPort(0) || !this->isConnected_allocate_OutputPort(0) || !this->isConnected_deallocate_OutputPort(0)) {
        // Add log event if something breaks
        this->log_wa
        return;
    }
    Fw::Buffer uartBuffer = this->allocate_out(0, bufferSize);
    if (uartBuffer.getData() == nullptr || uartBuffer.getSize() < bufferSize) {
        if (uartBuffer.getData() != nullptr && this->isConnected_deallocate_OutputPort(0)) {
            this->deallocate_out(0, uartBuffer);
        }
        // Add log events indicating breaking
        return;
    }

    // Filling buffer and setting buffer size
    std::memcpy(uartBuffer.getData(), stringLog, bufferSize);
    uartBuffer.setSize(bufferSize);

    Drv::ByteStreamStatus status = this->uartSend_out(0, uartBuffer);
    if (status.e != Drv::ByteStreamStatus::OP_OK) {
        // enter log stating something is wrong
        if (this->isConnected_deallocate_OutputPort(0)) {
            this->deallocate_out(0, uartBuffer);
        }
        return;
    }

    if (this->isConnected_deallocate_OutputPort(0)) {
        this->deallocate_out(0, uartBuffer);
    }
}

void TextLogger ::uartReady_handler(FwIndexType portNum) {
    // TODO
}

void TextLogger ::uartRecv_handler(FwIndexType portNum, Fw::Buffer& buffer, const Drv::ByteStreamStatus& status) {
    // TODO
}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void TextLogger ::TODO_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace Components
