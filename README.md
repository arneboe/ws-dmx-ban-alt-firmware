# Alternative Firmware for WS-DMX-xCH BAN Controllers
This repository contains an alternative firmware for the WS-DMX-xch ban dmx led drivers.
**Currently this firmware is only working on the WS-DMX-8CH BAN V4.1!** Support for other revisions might follow as soon as I get my hands on them.

![Alt text](programmer_pinout.jpg?raw=true "WS-DMX-8ch BAN pinout")

# Features
## Implemented
* 200hz led refresh rate
* Master control channel to scale the brightness of all leds
* Strobe channel (nearly finished)
* Individual control of each led
## Planned
* Increase led refresh rate to at least 400hz
* Different dimming curves
* Use power led to signal if dmx signal is present or not

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




