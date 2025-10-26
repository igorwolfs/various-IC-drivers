# AD9833-IN
Interface: 

# STM32 B-L072Z-LRWAN1
## Overview
There are 2 main IC's on the board
- STM32L072CZYx
- CMWX1ZZABZ LORA-module

## LED
- PA5: LED red
- PB5: Led Green
- PB6: led blue
- PB7: led red

## SPI connection
CN5:
- PB13: SPI2_SCK: D13
- PB15: SPI2_MOSI: D11
- PB14: SPI2_CS: D12

## Communication over USB
- LRA_USB_N; PA11 - Do not use
- LRA_USB_P: PA12 - Do not use

Solder SB15 and SB16

# AD9833
## Pin interface
### Signal
- MCLK: digital clock input - clock determines the output frequency accuracy and phase nosie.
- 

### SPI
- FSYNC: Active-low: frame synchronization
	- CS-pin likely
- SDATA
- SCLK