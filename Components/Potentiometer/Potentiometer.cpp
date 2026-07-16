// ======================================================================
// \title  Potentiometer.cpp
// \author thakkar
// \brief  cpp file for Potentiometer component implementation class
// ======================================================================

#include "Components/Potentiometer/Potentiometer.hpp"

#include <zephyr/drivers/adc.h>

namespace Components {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

Potentiometer ::Potentiometer(const char* const compName) : PotentiometerComponentBase(compName) {}

Potentiometer ::~Potentiometer() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void Potentiometer ::configure(const struct adc_dt_spec *adc_dev_config, U16 *buffer, size_t buffer_size) {
    // Basic Asserts
    FW_ASSERT(adc_dev_config != nullptr);
    FW_ASSERT(buffer != nullptr);
    FW_ASSERT(buffer_size > 0);
    
    // Zephyr ADC driver asserts
    FW_ASSERT(adc_is_ready_dt(adc_dev_config));
    FW_ASSERT(adc_channel_setup_dt(adc_dev_config) == 0);

    struct adc_sequence sequence = {};
    sequence.buffer = buffer;
    sequence.buffer_size = buffer_size;

    FW_ASSERT(adc_sequence_init_dt(adc_dev_config, &sequence) == 0);

    this->m_adc_dev_config = adc_dev_config;
    this->m_buffer = buffer;
    this->m_buffer_size = buffer_size;
    
    return;
}

U16 Potentiometer::read_raw(){
    FW_ASSERT(this->m_adc_dev_config != nullptr);
    FW_ASSERT(this->m_buffer != nullptr);

    struct adc_sequence sequence = {};
    sequence.buffer = this->m_buffer;
    sequence.buffer_size = this->m_buffer_size;
    FW_ASSERT(adc_sequence_init_dt(this->m_adc_dev_config, &sequence) == 0);

    int status = adc_read_dt(this->m_adc_dev_config, &sequence);
    
    if (status != 0) {
        FW_ASSERT(0, status, 0);
        return 0;
    }

    U16 raw = *static_cast<U16*>(sequence.buffer);

    return raw;
}

U32 Potentiometer::read_mv(){
    const U16 raw = this->read_raw();
    int32_t mv = raw;
    adc_raw_to_millivolts_dt(this->m_adc_dev_config, &mv);
    
    return mv;
}


void Potentiometer ::run_handler(FwIndexType portNum, U32 context) {
    if (this->m_begin_read == Fw::On::ON) {
        const U16 raw = this->read_raw();
        int32_t mv = raw;
        adc_raw_to_millivolts_dt(this->m_adc_dev_config, &mv);

        this->tlmWrite_Mv_Value(static_cast<U32>(mv));
        this->tlmWrite_Raw_Value(raw);
    }
}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void Potentiometer ::READ_Potentiometer_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, Fw::On onOff) {
    this->m_begin_read = onOff;

    if (onOff == Fw::On::ON) {
        this->log_ACTIVITY_HI_portSetPotentiometerState(Fw::On::ON);
    } else {
        this->log_ACTIVITY_HI_portSetPotentiometerState(Fw::On::OFF);
    }

    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace Components
