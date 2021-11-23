UV Click

UV sensor (ML8511) sensor with STM32F4

PROJECT: UV click 
MCU: STM32F407VGT 
DEV. BOARD: STM32F407G-DISC1 
SENSOR: ML8511
IDE: STM32CubeIDE 
AUTHOR: Mario Oletić

PROJECT DESCRIPTION:
UV click board carries the ML8511 IC that is sensitive to UV-A (365-315 nm) and UV-B (315-280 nm) rays. In this project, the MCP3201 AD Converter is used to convert the analog data from the ML811 sensor. Obtained data is then read via the SPI communication interface. Functions for initializing, reading and processing data have been developed. The final result, ie the intensity of UV radiation in mW / cm2 is then sent via UART communication to the PC.
