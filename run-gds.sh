#!/bin/bash
set -e


# Example: UART_PORT=/dev/ttyACM0 (MAKE SURE TO CORRECTLY SELECT THE PORT THAT YOUR STM32 IS CONNECTED TO ON YOUR DEVICE
UART_PORT="N/A"

if [ "$UART_PORT" == "N/A" ]; then
    echo "UART Port NOT SET in run-gds.sh"
    exit 1
fi


fprime-gds\
    -n\
    --dictionary build-artifacts/zephyr/fprime-zephyr-deployment/dict/ReferenceDeploymentTopologyDictionary.json\
    --communication-selection uart\
    --uart-device $UART_PORT\
    --uart-baud 115200\
    --framing-selection fprime
