# fprime-zephyr-reference project
This project is an implementation of F` on Zephyr RTOS, with MCUBoot being built additionally as a separate Zephyr application.

> [!Note]
> This deployment by default builds for the NUCLEO-H723ZG development board and has been verified on macOS and on Windows 11 using WSL (Ubuntu 22.04 LTS). 
> 

# Dependencies
- git
- python3 & venv (Tested with python3.13)
- Computer
- Internet connection


# Setup
> [!Note]
> This reference requires a couple steps of manual setup before it's able to be fully automated by ```setup.sh```. 
>

- Apply the git patch present in ```$PROJECT_ROOT\BOARD_NAME\setup_shell.patch ```
- Run setup.sh 

Setup Complete

# Usage
> [!Note]
> If possible, use .hex files ONLY. It makes the flashing order of both the MCUBoot application and fprime-zephyr application agonistic. Otherwise, you must manually offset the flashing of the fprime-zephyr application as to not overwrite the MCUBoot application, for which you will flash first.
>
The MCUBoot application, after being compiled, is built in ```$PROJECT_ROOT\lib\zephyr-workspace\bootloader\mcuboot\boot\zephyr\build\zephyr```
- ```zephyr.hex``` is what you're looking for. This ```.hex``` file is what contains the MCUBoot bootloader

The fprime-zephyr application, after being compiled, is built in ```$PROJECT_ROOT\build-fprime-automatic-zephyr\zephyr```
- ```zephyr.signed.hex``` is what you're looking for, if your intention is to use the fprime-zephyr application with MCUBoot. Otherwise, ```zephyr.hex``` is what you're looking for. ```zephyr.hex``` will NOT work on an MCU with MCUBoot loaded on it.

# Flashing
> [!Note]
> This reference has only been tested on a STMicrocontroller Nucleo board. Flashing steps may differ for other MCUs.
>

- Open up STM32CubeProgrammer and navigate to "Erasing & Programming". Fully erase the MCU if this is the first time flashing.
- ENSURE "Skip flash erase before programming" IS CHECKED. Or not. Just ensure your partitions are a factor of 128KiB (in your board's .dtsi). 
- Flash both .hex files in any order you'd like.

Success!





