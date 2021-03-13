# Alternative Firmware for WS-DMX-xCH BAN LED Controllers

# Features
This firmware adds some features that the original firmware is missing.

* Increase led refresh rate to 400hz (up from 200hz)
* Master control channel to scale the brightness of all leds
* Strobe channel (2hz to 40hz) with a flash length of 10ms
* Individual control of each led
* Set dmx adress using dip switch
* Flicker power led to indicate correct dmx signal reception.

## Planned Features
* Implement a random strobe
* Different dimming curves
* Maybe implement some static effects
* increase code readability without decreasing performance
* increase performance of the main loop

# Supported controllers
*  WS-DMX-8CH BAN V4.1

Support for others will follow as soon as I get my hands on them.


# DMX Channels

|Ch | Function|
|---|---------|
|1 | Master intensity |
|2 | Strobe 2hz to 40hz |
|3 | Led 1 intensity | 
|4 | Led 2 intensity | 
|5 | Led 3 intensity | 
|6 | Led 4 intensity | 
|7 | Led 5 intensity | 
|8 | Led 6 intensity | 
|9 | Led 7 intensity | 
|10 | Led 8 intensity | 




# State of the Code
The code is a bit messy, lots of external variables are used.
Some code has been unrolled to increase performance.
Some code is in locations that it logically shouldn't be in for performance reasons.


# Compiling and Flashing
## Dependencies
```bash
sudo apt install sdcc
pip3 install stcgal
```
## Compiling
```bash
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../sdcc.toolchain ..
```

## Flashing
The STC15W404s can be programmed using a standard usb-serial adapter.
I am using FTDI FT232 but any other adapter should work as well.

1. Set the FT232 to 3.3V
2. Connect RX/TX/GND from FT232 adapter according to the pinout image. Do not connect VCC!
3. Connect external power supply to the board
4. start flashing using the following command
```bash
stcgal -P stc15 -p /dev/ttyUSB0  dmx.ihx
```
5. turn on the board

- DMX needs to be disconnected for flashing to work.
- Flasher TX needs to be disconnected for dmx to work.
- Flasher RX/GND can stay connected while dmx is received. This is nice for debugging.





# License
This code is released under the gplv3. If you require a different license please contact me.






