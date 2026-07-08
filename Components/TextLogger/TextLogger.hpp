// ======================================================================
// \title  TextLogger.hpp
// \author thakkar
// \brief  hpp file for TextLogger component implementation class
// ======================================================================

#ifndef Components_TextLogger_HPP
#define Components_TextLogger_HPP

#include "Components/TextLogger/TextLoggerComponentAc.hpp"

namespace Components {

class TextLogger final : public TextLoggerComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct TextLogger object
    TextLogger(const char* const compName  //!< The component name
    );

    //! Destroy TextLogger object
    ~TextLogger();

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

    //! Handler implementation for command TODO
    //!
    //! TODO
    void TODO_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                         U32 cmdSeq            //!< The command sequence number
                         ) override;
};

}  // namespace Components

#endif
