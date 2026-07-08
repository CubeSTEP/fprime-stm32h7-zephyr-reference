// ======================================================================
// \title  DspLCD.hpp
// \author thakkar
// \brief  hpp file for DspLCD component implementation class
// ======================================================================

#ifndef Components_DspLCD_HPP
#define Components_DspLCD_HPP

#include "Components/DspLCD/DspLCDComponentAc.hpp"

namespace Components {

class DspLCD final : public DspLCDComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct DspLCD object
    DspLCD(const char* const compName  //!< The component name
    );
  
    //! Destroy DspLCD object
    ~DspLCD();
    
  private:
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command LCDI2CBusWrite
    //!
    //! TODO
    void LCDI2CBusWrite_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                                   U32 cmdSeq,           //!< The command sequence number
                                   U32 data              //!< Data to write to the I2C bus
                                   ) override;
};

}  // namespace Components

#endif
