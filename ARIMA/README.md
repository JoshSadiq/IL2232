# ARIMA model 

This repository contains the files for running the ARIMA model on PC (used for benchmarking and extracting equation parameters) and the ARIMA algorithm in C++ for the embedded device. 

## Directory structure

* _Backups_ contains backups used during the project
* _Data sets_ contains the data set _Global Surface Land Temperature Anomalies_, which is used throughout both moodels (Python and C++)
* _esp32_hello_world_ contains the relevant program files for the C++ version of the ARIMA model, to be deployed on an embedded device
* _arima_prep.ipynb_ is a Python-notebook which produces an ARIMA model using various libraries. Upon fitting the model to the dataset, it retrieves the parameters used in the ARIMA-equation.

## Running the Python-notebook

### Prerequisites

* An IDE that supports Python-notebook (such as VSCode with relevant extensions)
* Python
* Relevant libraries installed (see list of required libraries in the _arima_prep.ipynb_-file

### Instructions

1. Open the _arima_prep.ipynb_-file in the IDE
2. Run all the cells

## Deploying and running the C++-code

The C++-code was built and deployed using [PlatformIO](https://platformio.org/), a VSCode-extension which allows the building, deployment and monitoring of program files unto embedded devices. The prerequisites/instructions will refer to this method of deploying the program.

### Prerequisities

* Visual Studio Code + PlatformIO extension
* Embedded device connected to PC, preferably ESP32 if following these specific instructions

### Instructions

1. Connect the ESP32 to the PC, identify the correct COM-port (e.g. `COM17`)
2. In PlatformIO menu, pick 

Subfolder contains all files related to ARIMA on ESP32 research

DOIT ESP32 DEVKIT V1
Alt.: uPesy ESP32 Wroom DevKit
