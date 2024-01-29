# Project name: IL2232 Time series analysis
## Project part: The implementation of RNN of esp32
## Hengzhen Yuan 
## Dataset: a basic sin wave 

The main project can be divided into two parts.The first one is building and training the RNN model on PC and getting the weights and bias.
Then implemente the RNN model on ESP32.
For the first part,RNN_pre.py is for building and training the RNN model. RNN_pre_weights.py is for getting the weights and bias which will be stored in constant array in esp32.

For the second part, the original_Code.cpp is the implementation of rnn with storing the weights and bias by float  and the fixedpoint_Code is by fixedpoint.

The platform is ardunio ide 2.2.1 with esp32 dev module as board file.

For showing the result, just run the fixedpoint_Code on ardunio ide. So that you can get the result from serial monitor. 

the all code is using hidden_size=16 as example.
## For implementation process
1.train the model and get the weights from python code.
2.Use the different hidden size to get the different weights and bias.
3.use the all different hidden size to get the all results on esp32.

## Addition
The  results are shown in the technical report come from the original code. The fixedpoint results are shown in the slides in the final pre which are also in the folder.


