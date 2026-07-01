module FileHandlingConfig {
    #Base ID for the FileHandling Subtopology, all components are offsets from this base ID
    constant BASE_ID = 0x05000000
    
    module QueueSizes {
        constant fileUplink    = 3
        constant fileDownlink  = 3
        constant fileManager   = 3
        constant prmDb         = 3
    }
    
    module StackSizes {
        constant fileUplink    = 1024 * 5
        constant fileDownlink  = 1024 * 5
        constant fileManager   = 1024 * 5
        constant prmDb         = 1024 * 5
    }

    module Priorities {
        constant fileUplink    = 24
        constant fileDownlink  = 23
        constant fileManager   = 22
        constant prmDb         = 21
    }

    # File downlink configuration constants
    module DownlinkConfig {
        constant cooldown       = 1000         # File downlink cooldown in ms  
        constant cycleTime      = 1000         # File downlink cycle time in ms
        constant fileQueueDepth = 3           # File downlink queue depth
    }
}
