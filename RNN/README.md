# Project name: IL2232 Time series analysis
## Project part: The implementation of RNN of esp32
## Hengzhen Yuan 
## Dataset: a basic sin wave 

The main project can be divided into two parts. The first one is building and training the RNN model on PC and getting the weights and bias.
Then implement the RNN model on ESP32.
The first part, RNN_pre.py is for building and training the RNN model. RNN_pre_weights.py is for getting the weights and bias which will be stored in the constant array in esp32.

For the second part, the original_Code.cpp is the implementation of RNN with storing the weights and bias by the float and the fixedpoint_Code is by fixed point.

The platform is Arduino ide 2.2.1 with ESP32 dev module as the board file.

To show the result, go to the subfolders fixedpoint_Code/original_Code and open the .ino files in Arduino ide. So that you can get the result from the serial monitor, with baud 115200.

All code uses hidden_size=16 as an example.
## For implementation process
1. Train the model and get the weights from Python code.
2. Use the different hidden size to get the different weights and bias.
3. Use different hidden sizes to get all the results on esp32.

## Addition
The  results shown in the technical report come from the original code. The fixed-point results are shown in the slides in the final pre which are also in the folder.


