

This project is first meant as a Workspace Template for the Nucleo STM32F401 to be used with the GNU toolchain.

To build simply run make.

To flash make flash or copy the .bin on the USB mounted device. The Nucleo will automatically reset and run the program.

To debug with St-link on linux
 
https://github.com/texane/stlink

run the server:
$st-util

load the ELF in arm gdb:
$arm-none-eabi-gdb build/bin/program.elf

start debugging with the gdb server remotely:
$(gdb)tar extended-remote :4242





