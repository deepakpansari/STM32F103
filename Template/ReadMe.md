*********************************************************************************
#Compiling the Project on Mac

1. Locate into project folder where Makefile is present and execute this

"make all"

2. cleaning the project

"make clean"


#Flahing project in chip using FTDI Serial Interface by STM32Loader

"python stm32loader.py -e -w -v -p /dev/cu.usbserial-A50285BI ./build/main.bin"

**********************************************************************************
