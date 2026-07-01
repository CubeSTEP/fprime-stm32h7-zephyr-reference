# ======================================================================
# AcConstants.fpp
# F Prime configuration constants
# ======================================================================

@ Number of rate group member output ports for ActiveRateGroup
constant ActiveRateGroupOutputPorts = 4

@ Number of rate group member output ports for PassiveRateGroup
constant PassiveRateGroupOutputPorts = 4

@ Used to drive rate groups
constant RateGroupDriverRateGroupPorts = 3

@ Used for command and registration ports
constant CmdDispatcherComponentCommandPorts = 10

@ Used for uplink/sequencer buffer/response ports
constant CmdDispatcherSequencePorts = 1

@ Used for dispatching sequences to command sequencers
constant SeqDispatcherSequencerPorts = 1

@ Used for sizing the command splitter input arrays
constant CmdSplitterPorts = CmdDispatcherSequencePorts

@ Number of static memory allocations
constant StaticMemoryAllocations = 2

@ Used to ping active components
constant HealthPingPorts = 8

@ Used for broadcasting completed file downlinks
constant FileDownCompletePorts = 1

@ Used for number of Fw::Com type ports supported by Svc::ComQueue
constant ComQueueComPorts = 2

@ Used for number of Fw::Buffer type ports supported by Svc::ComQueue
constant ComQueueBufferPorts = 1

@ Used for maximum number of connected buffer repeater consumers
constant BufferRepeaterOutputPorts = 4

@ Size of port array for DpManager
constant DpManagerNumPorts = 2

@ Size of processing port array for DpWriter
constant DpWriterNumProcPorts = 2

@ The size of a file name string
constant FileNameStringSize = 128

@ The size of an assert text string
constant FwAssertTextSize = 128

@ The size of a file name in an AssertFatalAdapter event
@ Note: File names in assertion failures are also truncated by
@ the constants FW_ASSERT_TEXT_SIZE and FW_LOG_STRING_MAX_SIZE, set
@ in FpConfig.h.
constant AssertFatalAdapterEventFileSize = FileNameStringSize
