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
    Fw::LogStringArg portErrorMsg("Port confg error");
    Fw::LogStringArg bufferErrorMsg("Buffer error");
    Fw::LogStringArg uartSendErrorMsg("Uart send error");

    // Verifying port connections
    if (!this->isConnected_uartSend_OutputPort(0) || !this->isConnected_allocate_OutputPort(0) || !this->isConnected_deallocate_OutputPort(0)) {
        this->log_WARNING_HI_errorMessage(portErrorMsg);
        return;
    }

    // Allocating for uart buffer
    Fw::Buffer uartBuffer = this->allocate_out(0, bufferSize);

    // Verifying uart buffer data
    if (uartBuffer.getData() == nullptr || uartBuffer.getSize() < bufferSize) {
        if (uartBuffer.getData() != nullptr && this->isConnected_deallocate_OutputPort(0)) {
            this->deallocate_out(0, uartBuffer);
        }
        this->log_WARNING_HI_errorMessage(bufferErrorMsg);
        return;
    }

    // Populating buffer with string log
    std::memcpy(uartBuffer.getData(), stringLog, bufferSize);
    uartBuffer.setSize(bufferSize);

    // Send string to uart driver
    Drv::ByteStreamStatus status = this->uartSend_out(0, uartBuffer);

    // Log error if the data to the uart driver is invalid
    if (status.e != Drv::ByteStreamStatus::OP_OK) {
        // enter log stating something is wrong
        this->log_WARNING_HI_errorMessage(uartSendErrorMsg);
        if (this->isConnected_deallocate_OutputPort(0)) {
            this->deallocate_out(0, uartBuffer);
        }
        return;
    }

    // Deallocate uart buffer
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
