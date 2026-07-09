// ======================================================================
// \title  Potentiometer.hpp
// \author thakkar
// \brief  hpp file for Potentiometer component implementation class
// ======================================================================

#ifndef Components_Potentiometer_HPP
#define Components_Potentiometer_HPP

#include "Components/Potentiometer/PotentiometerComponentAc.hpp"
#include <stddef.h>

struct adc_dt_spec;

namespace Components {

class Potentiometer final : public PotentiometerComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct Potentiometer object
    Potentiometer(const char* const compName  //!< The component name
    );

    //! Destroy Potentiometer object
    ~Potentiometer();

    void configure(const struct adc_dt_spec *adc_dev, U16 *buffer, size_t buffer_size);
    U16 read_raw();
    U32 read_mv();
  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for run
    void run_handler(FwIndexType portNum,  //!< The port number
                     U32 context           //!< The call order
                     ) override;

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------
    // System configuration elements

    const struct adc_dt_spec* m_adc_dev_config = nullptr; //!< Zephyr ADC device specification
    U16* m_buffer = nullptr; //!< ADC sample buffer
    size_t m_buffer_size = 0; //!< ADC sample buffer size
    Fw::On m_begin_read = Fw::On::OFF; //!< Flag to indicate if potentiometer reading is enabled

    //! Handler implementation for command READ_Potentiometer
    void READ_Potentiometer_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                                       U32 cmdSeq,           //!< The command sequence number
                                       Fw::On onOff          //!< Indicates whether the potentiometer is on or off
                                       ) override;


};

}  // namespace Components

#endif
