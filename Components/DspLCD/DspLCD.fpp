module Components {
    @ Display Controller STM32H753-EVAL
    active component DspLCD {

        # One async command/port is required for active components
        # This should be overridden by the developers with a useful command/port
        @ TODO
        async command LCDI2CBusWrite (
            data: U32 @< Data to write to the I2C bus
        ) opcode 0
        
        ##############################################################################
        # I2C Driver Ports for I2C Communication                            #
        ##############################################################################

        @ Port for I2C bus communication
        output port busWriteRead: Drv.I2cWriteRead
        
        @ Port for I2C bus communication
        output port busWrite: Drv.I2c

        @ Telemetry channel for DSP LCD data
        telemetry Reading: U32
        
         ##############################################################################
        # Events for I2C Communication                            #
        ##############################################################################

        event I2cError(
            address: U32,
            status: Drv.I2cStatus
        ) severity warning high format "I2C error on address {} with status {}" throttle 5

        event I2cReadResponse(
            address: U32,
            response: U32
        ) severity activity high format "I2C read from address {} returned {}"

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Enables command handling
        import Fw.Command

        @ Enables event handling
        import Fw.Event

        @ Enables telemetry channels handling
        import Fw.Channel

    }
}
