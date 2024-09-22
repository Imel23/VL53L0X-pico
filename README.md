# VL53L0X Driver for Raspberry Pi Pico (C++)

This project demonstrates how to interface the VL53L0X Time-of-Flight distance sensor with the Raspberry Pi Pico using C++ and the Raspberry Pi Pico SDK. The driver and main application are built using CMake and linked as a static library.

## Project Structure

The project is divided into two parts:

1. **VL53L0X Driver Library**: A static library that provides an interface to the VL53L0X sensor.
2. **Main Application**: Uses the VL53L0X driver to communicate with the sensor and perform distance measurements.

### File Structure

```
├── CMakeLists.txt          # Main CMake file for the project
├── lib
│   ├── VL53L0X.cpp         # Source file for VL53L0X driver
│   ├── VL53L0X.h           # Header file for VL53L0X driver
│   └── CMakeLists.txt      # CMake file for building the static library
├── main.cpp                # Main application using the VL53L0X driver
├── pico_sdk_import.cmake   # Import script for Raspberry Pi Pico SDK
```

### Key Files

1. **VL53L0X.cpp** and **VL53L0X.h**:
   - These files contain the implementation of the VL53L0X driver, providing the necessary functions to interface with the sensor via I2C.
2. **CMakeLists.txt (in `/lib`)**:

   - This file is responsible for creating the static library `VL53L0X_Lib` from the driver files.
   - It links the Pico SDK's standard library and hardware I2C to enable communication with the sensor.

   ```cmake
   add_library(VL53L0X_Lib STATIC src/VL53L0X.cpp)
   target_link_libraries(VL53L0X_Lib pico_stdlib hardware_i2c)
   target_include_directories(VL53L0X_Lib PUBLIC inc/)
   ```

3. **main.cpp**:

   - The entry point for the project that includes and utilizes the `VL53L0X_Lib` to interact with the sensor.
   - This file contains logic for initializing the sensor, reading distance data, and outputting the results via USB or UART.

4. **CMakeLists.txt (main)**:

   - The main CMake file initializes the Pico SDK and sets up the build for the `main_app` executable.
   - It includes the static library (`VL53L0X_Lib`) and links it with the main application.

   ```cmake
   add_executable(main_app main.cpp)
   target_link_libraries(main_app VL53L0X_Lib pico_stdlib)
   pico_add_extra_outputs(main_app)
   ```

### Requirements

- Raspberry Pi Pico SDK (configured and installed)
- GNU Arm Embedded Toolchain (e.g., `gcc-arm-none-eabi`)
- VL53L0X Time-of-Flight sensor
- CMake 3.19 or later

### Building the Project

1. Clone or download the Pico SDK and this project.
2. Set up the Pico SDK by pointing to the `PICO_SDK_PATH` in your environment:

   ```bash
   export PICO_SDK_PATH=/path/to/pico-sdk
   ```

3. Create a build directory and run CMake:

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. Once compiled, you can upload the generated `.uf2` file to the Raspberry Pi Pico by dragging it to the Pico's mass storage device when in bootloader mode.

### Usage

1. Connect the VL53L0X sensor to the Raspberry Pi Pico via I2C.
2. The main application will initialize the sensor and begin reading distance data.
3. The distance measurements can be output via USB or UART (configurable in the `CMakeLists.txt`).

### References

This project uses the [VL53L0X-driver for Pico SDK (C++)](https://github.com/yspreen/VL53L0X-driver-pico-sdk-cpp) to simplify interaction with the VL53L0X sensor on the Raspberry Pi Pico.

---
