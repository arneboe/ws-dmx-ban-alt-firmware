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
```bash
stcgal -P stc15 -p /dev/ttyUSB0  dmx.ihx
```




