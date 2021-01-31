# Alternative Firmware for WS-DMX-xCH BAN Controllers

This repository contains an alternative firmware for the WS-DMX-xch ban dmx led drivers.
Those drivers are available from several resellers in different configurations.

**Currently this firmware is only working on the WS-DMX-8CH BAN V4.1!**
Porting to other controllers should be easy but right now this is the only
one I have at hand.

The WS-DMX driver is attractive because it is cheap but its stock firmware is fairly basic. Luckily it contains an Intel 8051 compatible chip and expose the ISP pins.

This project aims to extend the firmware to include a master intensity channel and a strobe channel.
Further improvements like different dimming curves, smoother dimming etc. might also be added.

![Alt text](programmer_pinout.jpg?raw=true "WS-DMX-8ch BAN pinout")

# Dependencies
```bash
sudo apt install sdcc
pip3 install stcgal
```
# Compiling
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=../sdcc.toolchain ..
```

# Flashing

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




