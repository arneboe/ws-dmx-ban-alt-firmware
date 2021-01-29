# ws-dmx-ban-alt-firmware
an alternative firmware for the ws-dmx-ban led controllers


# dependencies
```bash
sudo apt install sdcc
pip3 install stcgal
```
# compiling
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=../sdcc.toolchain ..
```

# flashing

- Connect RX/TX/GND from FT232 adapter according to the pinout image.
- Set the FT232 to 3.3V
- Connect external 5v to the board
- turn off board
- start flashing
- turn on board

```bash
stcgal -P stc15 -p /dev/ttyUSB0  dmx.ihx
```




