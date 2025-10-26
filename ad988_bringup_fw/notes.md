# Compiling
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=cmake/gcc-arm-none-eabi.cmake ..
make
```

# Flashing

```bash
st-flash write build/ad988_bringup_fw.bin 0x08000000
```