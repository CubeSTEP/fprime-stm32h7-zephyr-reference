// ======================================================================
// \title  DspLCD.cpp
// \author thakkar
// \brief  cpp file for DspLCD component implementation class
// ======================================================================

#include "Components/DspLCD/DspLCD.hpp"

namespace {
    static constexpr U32 EXC7200_I2C_ADDRESS = 0x04;
    static constexpr U8 EXC7200_READ_REG = 0x09;
    static constexpr FwSizeType EXC7200_READ_RESPONSE_SIZE = 1;
}  // namespace


namespace Components {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

DspLCD ::DspLCD(const char* const compName) : DspLCDComponentBase(compName) {}

DspLCD ::~DspLCD() {}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void DspLCD ::LCDI2CTransmit_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, Fw::On transmit) {
    if (transmit != Fw::On::ON) {
        this->log_ACTIVITY_HI_I2cTransmitSkipped();
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
        return;
    }

    if (!this->isConnected_busWriteRead_OutputPort(0)) {
        this->log_WARNING_HI_I2cError(EXC7200_I2C_ADDRESS, Drv::I2cStatus::I2C_OTHER_ERR);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    U8 readRegister[] = {EXC7200_READ_REG};
    U8 responseBytes[EXC7200_READ_RESPONSE_SIZE] = {};
    Fw::Buffer readRegisterBuffer(readRegister, sizeof(readRegister));
    Fw::Buffer responseBuffer(responseBytes, sizeof(responseBytes));

    Drv::I2cStatus status = this->busWriteRead_out(0, EXC7200_I2C_ADDRESS, readRegisterBuffer, responseBuffer);

    if (status != Drv::I2cStatus::I2C_OK) {
        this->log_WARNING_HI_I2cError(EXC7200_I2C_ADDRESS, status);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    const U32 response = responseBytes[0];
    this->tlmWrite_Reading(response);
    this->log_ACTIVITY_HI_I2cReadResponse(EXC7200_I2C_ADDRESS, response);
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace Components
