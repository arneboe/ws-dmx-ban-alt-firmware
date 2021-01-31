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
* 200hz led refresh rate
* Master control channel to scale the brightness of all leds
* Strobe channel (nearly finished)
* Individual control of each led
* Set dmx adress using dip switch
## Planned
* Increase led refresh rate to at least 400hz
* Different dimming curves
* Use power led to signal if dmx signal is present or not
* Ignore illegal dmx adresses (i.e. 0 or above 512-num_channels)
* Maybe implement some static effects

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

- Connect RX/TX/GND from FT232 adapter according to the pinout image.
- Set the FT232 to 3.3V
- Connect external 5v to the board
- turn off board
- start flashing
- turn on board

- DMX needs to be disconnected for flashing to work.
- Flasher TX needs to be disconnected for dmx to work.
- Flasher RX/GND can stay connected while dmx is received. This is nice for debugging.


```bash
stcgal -P stc15 -p /dev/ttyUSB0  dmx.ihx
```




