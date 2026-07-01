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

    instance ComFprime.Subtopology
    instance FileHandling.Subtopology

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
    instance gpioDriver
    instance prmDb

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
      rateGroup1.RateGroupMemberOut[2] -> ComFprime.comQueue.run
      rateGroup1.RateGroupMemberOut[3] -> FileHandling.Subtopology.fileDownlinkRun
    }
    
    connections FaultHandler {
      eventManager.FatalAnnounce -> fatalHandler.FatalReceive
    }

    connections Communications {
      # ComDriver buffer allocations
      comDriver.allocate   -> ComFprime.Subtopology.commsBufferGetCallee
      comDriver.deallocate -> ComFprime.Subtopology.commsBufferSendIn

      # ComDriver <-> ComStub
      comDriver.$recv                           -> ComFprime.Subtopology.drvReceiveIn
      ComFprime.Subtopology.drvReceiveReturnOut -> comDriver.recvReturnIn
      ComFprime.Subtopology.drvSendOut          -> comDriver.$send
      comDriver.ready                           -> ComFprime.Subtopology.drvConnected

      # Event, telemetry, and file to ComQueue
      eventManager.PktSend -> ComFprime.Subtopology.comPacketQueueIn[ComFprime.Ports_ComPacketQueue.EVENTS]
      tlmSend.PktSend     -> ComFprime.Subtopology.comPacketQueueIn[ComFprime.Ports_ComPacketQueue.TELEMETRY]
      FileHandling.Subtopology.fileDownlinkBufferSendOut  -> ComFprime.Subtopology.bufferQueueIn[ComFprime.Ports_ComBufferQueue.FILE]
      ComFprime.Subtopology.bufferReturnOut[ComFprime.Ports_ComBufferQueue.FILE] -> FileHandling.Subtopology.fileDownlinkBufferReturn

      # Router <-> CmdDispatcher
      ComFprime.Subtopology.commandOut -> cmdDisp.seqCmdBuff
      cmdDisp.seqCmdStatus             -> ComFprime.Subtopology.cmdResponseIn

      # FileUplink <-> FprimeRouter
      ComFprime.Subtopology.fileUplinkOut  ->  FileHandling.Subtopology.fileUplinkBufferSendIn
      FileHandling.Subtopology.fileUplinkBufferSendOut -> ComFprime.Subtopology.fileUplinkReturnIn
    }

    connections ReferenceDeployment {
    }

    connections LedConnections {
      # Rate Group 2 (1Hz cycle) ouput is connected to led's run input
      rateGroup2.RateGroupMemberOut[1] -> led.run
      # led's gpioSet output is connected to gpioDriver's gpioWrite input
      led.gpioSet -> gpioDriver.gpioWrite
    }

  }

}
