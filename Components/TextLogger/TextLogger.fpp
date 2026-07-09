module Components {
    @ Text Logger to demonstrate an F Prime UART component.
    active component TextLogger {

        # One async command/port is required for active components
        # This should be overridden by the developers with a useful command/port
        @ TODO
        async command TODO opcode 0

        ##############################################################################
        #### Uncomment the following examples to start customizing your component ####
        ##############################################################################

        # @ Example async command
        # async command COMMAND_NAME(param_name: U32)

        # @ Example telemetry counter
        # telemetry ExampleCounter: U64

        # @ Example event
        # event ExampleStateEvent(example_state: Fw.On) severity activity high id 0 format "State set to {}"

        # @ Example port: receiving calls from the rate group
        sync input port run: Svc.Sched

        # @ Example parameter
        # param PARAMETER_NAME: U32

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

        ###############################################################################
        #                                UART ports                                   #
        ###############################################################################
        @ Sends buffer to the uart driver
        output port uartSend: Drv.ByteStreamSend

        @ Receives buffer from uart driver
        guarded input port uartRecv: Drv.ByteStreamData

        @ Receives signal that the uart driver is ready
        async input port uartReady: Drv.ByteStreamReady

        @ Sends buffer back to the driver after its done being used
        output port uartRecvReturn: Fw.BufferSend
        
        @ Sends request to allocate buffer
        output port allocate: Fw.BufferGet

        @ Sends request to deallocate buffer
        output port deallocate: Fw.BufferSend


        ###############################################################################
        #                                UART events                                  #
        ###############################################################################
        event errorMessage(
            message: string size 20
        ) severity warning high format "{}"
    }
}