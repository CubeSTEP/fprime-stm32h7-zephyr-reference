module ReferenceDeployment {

  # ----------------------------------------------------------------------
  # Symbolic constants for port numbers
  # ----------------------------------------------------------------------

    enum Ports_RateGroups {
      rateGroup1
    }

  topology ReferenceDeployment {

    # ----------------------------------------------------------------------
    # Subtopology instances
    # ----------------------------------------------------------------------

    # ----------------------------------------------------------------------
    # Instances used in the topology
    # ----------------------------------------------------------------------

    instance $health
    instance rateDriver
    instance chronoTime
    instance cmdDisp
    instance eventManager
    instance fatalHandler
    instance rateGroup1
    instance rateGroup2
    instance rateGroup3
    instance rateGroupDriver
    instance textLogger
    instance tlmSend
    instance systemResources
    instance led
    instance gpioDriver
    instance prmDb
    instance UartTextLogger
    instance uartDriver
    instance bufferManager

    # ----------------------------------------------------------------------
    # Pattern graph specifiers
    # ----------------------------------------------------------------------

    command connections instance cmdDisp

    param connections instance prmDb

    event connections instance eventManager

    telemetry connections instance tlmSend

    text event connections instance textLogger

    time connections instance chronoTime

    # ----------------------------------------------------------------------
    # Direct graph specifiers
    # ----------------------------------------------------------------------

    connections RateGroups {
      # Block driver
      rateDriver.CycleOut -> rateGroupDriver.CycleIn

      # Rate group 1
      rateGroupDriver.CycleOut[Ports_RateGroups.rateGroup1] -> rateGroup1.CycleIn
      rateGroup1.RateGroupMemberOut[0] -> tlmSend.Run
      rateGroup1.RateGroupMemberOut[1] -> UartTextLogger.run
      rateGroup1.RateGroupMemberOut[2] -> uartDriver.schedIn
    }
    
    connections FaultHandler {
      eventManager.FatalAnnounce -> fatalHandler.FatalReceive
    }

    connections LedConnections {
      # Rate Group 2 (1Hz cycle) ouput is connected to led's run input
      rateGroup2.RateGroupMemberOut[1] -> led.run
      # led's gpioSet output is connected to gpioDriver's gpioWrite input
      led.gpioSet -> gpioDriver.gpioWrite
    }

    connections UartConnections {
      # Port conections for sending buffers between uart component and uart driver
      UartTextLogger.uartSend     -> uartDriver.$send
      uartDriver.$recv            -> UartTextLogger.uartRecv

      # Port to send buffer back to the uart driver after its done being used
      UartTextLogger.uartRecvReturn ->  uartDriver.recvReturnIn

      # Port to signal uart component that the driver is ready
      uartDriver.ready              ->  UartTextLogger.uartReady

      # Buffer allocation and deallocation for the uart driver
      uartDriver.allocate     -> bufferManager.bufferGetCallee
      uartDriver.deallocate  -> bufferManager.bufferSendIn

      # Buffer allocation and deallocation for the uart component
      UartTextLogger.allocate     -> bufferManager.bufferGetCallee
      UartTextLogger.deallocate  -> bufferManager.bufferSendIn
    }
  }
}
