module Components {
    @ Control for Potentiometer on STM32H753-EVAL
    active component Potentiometer {

        async command READ_Potentiometer(
            onOff: Fw.On @< Indicates whether the potentiometer is on or off
        )

        # @ Example telemetry counter
        telemetry Mv_Value: U32
        telemetry Raw_Value: U16
        
        # @ Example event
        # event ExampleStateEvent(example_state: Fw.On) severity activity high id 0 format "State set to {}"
        event portSetPotentiometerState($state: Fw.On) \
            severity activity high \
            format "Read potentiometer state set to: {}"
        
        # @ Example port: receiving calls from the rate group
        sync input port run: Svc.Sched

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