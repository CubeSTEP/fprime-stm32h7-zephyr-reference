// ======================================================================
// \title  DspLCD.cpp
// \author thakkar
// \brief  cpp file for DspLCD component implementation class
// ======================================================================

#include "Components/DspLCD/DspLCD.hpp"

namespace {
    static constexpr U32 TS3510_I2C_ADDRESS = 0x40;
    static constexpr U8 TS3510_READ_BLOCK_REG = 0x8A;
    static constexpr U8 TS3510_READ_CMD = 0x81;
    static constexpr U8 TS3510_WRITE_CMD = 0x08;
    static constexpr FwSizeType TS3510_READ_RESPONSE_SIZE = 1;
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

    if (!this->isConnected_busWrite_OutputPort(0) || !this->isConnected_busWriteRead_OutputPort(0)) {
        this->log_WARNING_HI_I2cError(TS3510_I2C_ADDRESS, Drv::I2cStatus::I2C_OTHER_ERR);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    U8 setupBytes[] = {TS3510_READ_BLOCK_REG, TS3510_READ_CMD, TS3510_WRITE_CMD};
    Fw::Buffer setupBuffer(setupBytes, sizeof(setupBytes));

    Drv::I2cStatus status = this->busWrite_out(0, TS3510_I2C_ADDRESS, setupBuffer);
    
    if (status != Drv::I2cStatus::I2C_OK) {
        this->log_WARNING_HI_I2cError(TS3510_I2C_ADDRESS, status);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    U8 readRegister[] = {TS3510_READ_BLOCK_REG};
    U8 responseBytes[TS3510_READ_RESPONSE_SIZE] = {};
    Fw::Buffer readRegisterBuffer(readRegister, sizeof(readRegister));
    Fw::Buffer responseBuffer(responseBytes, sizeof(responseBytes));

    status = this->busWriteRead_out(0, TS3510_I2C_ADDRESS, readRegisterBuffer, responseBuffer);

    if (status != Drv::I2cStatus::I2C_OK) {
        this->log_WARNING_HI_I2cError(TS3510_I2C_ADDRESS, status);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    const U32 response = responseBytes[0];
    this->tlmWrite_Reading(response);
    this->log_ACTIVITY_HI_I2cReadResponse(TS3510_I2C_ADDRESS, response);

    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace Components
