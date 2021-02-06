# Alternative Firmware for WS-DMX-xCH BAN LED Controllers
**Currently only working on the WS-DMX-8CH BAN V4.1!** Support for other revisions might follow as soon as I get my hands on them.

![Alt text](programmer_pinout.jpg?raw=true "WS-DMX-8ch BAN pinout")

# Features
This firmware aims to add some features that the original firmware is missing. Most notably a master and a strobe channel.

## DMX Channels

|Ch | Function|
|---|---------|
|1 | Master intensity |
|2 | Strobe |
|3 | Led 1 intensity | 
|4 | Led 2 intensity | 
|5 | Led 3 intensity | 
|6 | Led 4 intensity | 
|7 | Led 5 intensity | 
|8 | Led 6 intensity | 
|9 | Led 7 intensity | 
|10 | Led 8 intensity | 

## Implemented
* 400hz led refresh rate
* Master control channel to scale the brightness of all leds
* Strobe channel (nearly finished)
* Individual control of each led
* Set dmx adress using dip switch

## Planned
* Different dimming curves
* Use power led to signal if dmx signal is present or not
* Ignore illegal dmx adresses (i.e. 0 or above 512-num_channels)
* Maybe implement some static effects
* increase code readability without decreasing performance
* increase performance of the main loop


# State of the Code
The code is a bit messy, lots of external variables are used.
Some code has been unrolled to increase performance.
Some code is in locations that it logically shouldn't be in for performance reasons.

## Performance Trade-offs
There is a hard trade-off between led update frequency and strobe flash duration.
The strobe flash duration is calculated in the main loop, i.e. with the lowest priority.
The higher the led update frequency, the more the main loop gets interrupted and the longer
one iteration of the main loop takes. At 400hz it is currently impossible to go below 11 ms strobe flash duration.



# Compiling and Flashing
## Dependencies
```bash
sudo apt install sdcc
pip3 install stcgal
```
## Compiling
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=../sdcc.toolchain ..
```

## Flashing
The STC15W404s can be programmed using a standard usb-serial adapter.
I am using FTDI FT232 but any other adapter should work as well.

1. Set the FT232 to 3.3V
2. Connect RX/TX/GND from FT232 adapter according to the pinout image. Do not connect VCC!
3. Connect external power supply to the board
4. start the flasing process using the command below
5. turn on the board

- DMX needs to be disconnected for flashing to work.
- Flasher TX needs to be disconnected for dmx to work.
- Flasher RX/GND can stay connected while dmx is received. This is nice for debugging.


```bash
stcgal -P stc15 -p /dev/ttyUSB0  dmx.ihx
```




