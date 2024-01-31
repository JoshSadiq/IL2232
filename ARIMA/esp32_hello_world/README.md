# Directory structure

* _platformio.ini_ contains the build instructions for the specific platform. This can be changed through a GUI-menu in VSCode's PlatformIO-extension, or directly in the .ini-file. Currently set for the ESP32 WROOM Dev Kit-device.
Note: If you're having issues with random characters in the Serial Monitor, play around with the monitor speed. The current BAUD-speed should circumvent the bug.
* _src/main.cpp_ contains the main file with the algorithm. This is built and deployed unto the embedded device.
