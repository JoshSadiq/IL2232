# Clustering Models

This repository contains code for running K-Means clustering and Self-Organizing Maps (SOM) inference on ESP32 using Arduino. Additionally, it includes a training code (`pc_ccode.c`) for running on a PC.

## Directory Structure

- **esp_kmeans**: Contains Arduino code for running K-Means clustering inference on ESP32.
- **esp_som**: Contains Arduino code for running Self-Organizing Maps (SOM) inference on ESP32.
- **pc_ccode.c**: Contains training code to be run on a PC.

## Running the Arduino Code

### Prerequisites

- Connect the ESP32 to the PC using a data cable.
- Make sure the Arduino IDE is installed on your PC.

### Instructions

1. Open the Arduino IDE.
2. Select the board as "ESP32 Dev Module" in the Arduino IDE.
3. Choose the correct port (e.g., `/dev/cu.usbserial-01E01DEC`).
4. Navigate to the `esp_kmeans` or `esp_som` directory, open the respective `.ino` file in the Arduino IDE.
5. Click the "Upload" button to flash the code onto the ESP32.

## Running the Training Code (pc_ccode.c)

### Prerequisites

- Ensure you have a C compiler installed on your PC.

### Instructions

1. Navigate to the root directory of the repository.
2. Compile the `pc_ccode.c` file using your preferred C compiler.
3. Run the compiled executable on your PC.


