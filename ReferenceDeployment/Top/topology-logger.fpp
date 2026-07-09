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
    instance comDriver
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
    instance DspLCD
    instance gpioDriver
    instance i2cDriver
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
      rateGroup1.RateGroupMemberOut[1] -> comDriver.schedIn
      rateGroup1.RateGroupMemberOut[3] -> UartTextLogger.run
    }
    
    connections FaultHandler {
      eventManager.FatalAnnounce -> fatalHandler.FatalReceive
    }

    connections ReferenceDeployment {
      DspLCD.busWrite -> i2cDriver.write
      DspLCD.busWriteRead -> i2cDriver.writeRead
    }

    connections LedConnections {
      # Rate Group 2 (1Hz cycle) ouput is connected to led's run input
      rateGroup2.RateGroupMemberOut[1] -> led.run
      # led's gpioSet output is connected to gpioDriver's gpioWrite input
      led.gpioSet -> gpioDriver.gpioWrite
    }

    connections UartConnections {
      UartTextLogger.uartSend     -> UartDriver.$send
      UartDriver.$recv            -> UartTextDriver.uartRecv

      UartTextLogger.uartRecvReturn ->  UartDriver.recvReturnIn
      UartDriver.ready              ->  TextLoggerUart.uartReady

      UartDriver.allocate     -> bufferManager.bufferGetCallee
      UartDriver.deallocate  -> bufferManager.bufferSendIn

      UartTextLogger.allocate     -> bufferManager.bufferGetCallee
      UartTextLogger.deallocate  -> bufferManager.bufferSendIn
    }
  }
}
