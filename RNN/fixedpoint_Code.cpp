
//Hengzhen Yuan wrote on 2024.1.10
//IL2232 project Time series analysis

#include <Arduino.h>
//Ensure that core parameters are not optimized
volatile int8_t output;
volatile int8_t count = 0;

// Define RNN parameters  定义RNN的参数
const int input_size = 1;
const int hidden_size = 16;
const int output_size = 1;
volatile int8_t h[hidden_size];
// Define Scale    缩放因子
const int scale_factor = 256;

//the weight of RNN    RNN的权重矩阵
int8_t W_ih[hidden_size][input_size] = {{-2},
                                        {32},
                                        {72},
                                        {6},
                                        {61},
                                        {-13},
                                        {48},
                                        {-21},
                                        {-23},
                                        {-5},
                                        {-71},
                                        {-91},
                                        {57},
                                        {-112},
                                        {65},
                                        {-187}};

int8_t W_hh[hidden_size][hidden_size] = {{-27, -1, 7, 3, 13, -6, 16, -12,
                                          0, 5, 2, 23, -9, -16, 14, 3},
                                         {17, 16, 22, -3, -2, -4, 4, 10,
                                          3, 12, -10, -25, 8, 17, 9, 28},
                                         {-30, -23, 36, 23, 5, -3, 6, 0,
                                          34, 2, 10, 30, -27, 5, -10, -7},
                                         {14, -17, 11, -39, 25, -27, -1, 19,
                                          39, 26, 27, 18, -14, -30, -6, -26},
                                         {-14, -32, -44, -16, 4, 36, -47, 62,
                                          13, -20, 6, 47, -16, 52, -20, -24},
                                         {-4, 24, -5, 7, -33, -73, -6, -20,
                                          -9, 29, -43, 6, 38, 5, -11, 11},
                                         {-30, 13, -8, 19, 7, 29, -11, -10,
                                          -3, -1, 23, -10, 24, 2, 4, -13},
                                         {6, -27, -25, -8, 26, 21, -29, -8,
                                          -1, -30, 2, 33, -20, 69, 34, -16},
                                         {13, -10, 23, 11, -3, 9, 10, -11,
                                          -49, 3, 24, -10, 3, -54, -31, 21},
                                         {3, 21, 36, 3, -3, -27, 29, -41,
                                          -1, 29, 8, -10, 23, -35, 20, 41},
                                         {20, 32, 13, -32, -24, -37, 64, -79,
                                          -39, -2, 6, -67, 49, -31, 0, 51},
                                         {-21, 5, 29, 16, 24, -17, -5, -12,
                                          12, 33, 18, 2, -3, -28, 13, -28},
                                         {18, -1, -29, -9, -39, -15, -1, 17,
                                          -21, -46, -9, 2, -25, 46, -13, -38},
                                         {-15, 29, 9, 12, -31, -14, 32, -15,
                                          14, -25, -1, 6, 15, 7, -9, -18},
                                         {-32, -1, 19, -7, 60, -26, 2, 3,
                                          -1, -2, 0, -27, 46, -68, -19, -40},
                                         {-1, 26, 57, 4, -8, -13, 41, -40,
                                          -2, 27, 6, -51, 30, -72, 29, -35}};

int8_t W_ho[output_size][hidden_size] = {{3, 11, 26, 2, -16, -1, 13, -2,
                                           0, 19, 12, -25, 8, -20, 37, -72}};

// the bias of RNN          RNN的偏置
int8_t b_ih[hidden_size] = {-1, 11, -7, 9, -16, -20, 1, -56,
                             -7, -5, 10, -27, -1, 13, 26, -11};

int8_t b_hh[hidden_size] = {0, 8, 1, 14, -20, -3, 7, -27,
                             20, -3, -13, 7, -3, 29, -9, -34};

int8_t b_o[output_size] = {-26};


void setup() {
    Serial.begin(19200);

    // initialization of state     初始化状态
    for (int i = 0; i < hidden_size; ++i) {
        h[i] = 0;
    }

    
}

void loop() {
    // input                      输入数据
      unsigned long startTime = micros();
     volatile int8_t input[input_size] = {count};

    for (int i = 0; i < hidden_size; ++i) {
        h[i] = 0;
        // Serial.println(h[i]);
    }

    //forward  propagation        前向传播
    for (int i = 0; i < hidden_size; ++i) {
        volatile int16_t sum = 0;
        for (int j = 0; j < input_size; ++j) {
            sum += (int16_t)W_ih[i][j] * input[j] * scale_factor;
        }
        for (int j = 0; j < hidden_size; ++j) {
            sum += (int16_t)W_hh[i][j] * h[j] * scale_factor;
           
        }
        sum += b_ih[i] * scale_factor;
        sum += b_hh[i] * scale_factor;
        h[i] = tanh(sum / scale_factor);
        // Serial.println(h[i]);
    }

    // output    
    int8_t output[output_size] = {0};
    for (int i = 0; i < output_size; ++i) {
        volatile  int16_t sum = 0;
        for (int j = 0; j < hidden_size; ++j) {
            sum += (int16_t)W_ho[i][j] * h[j] * scale_factor;
        }
        sum += b_o[i] * scale_factor;
        output[i] = tanh(sum / scale_factor);
        // Serial.print("input：");
        // Serial.print(count);
        // Serial.print("output：");
        // // Serial.println(output[i]);
        
    }

  unsigned long endTime = micros(); 
  unsigned long executionTime = endTime - startTime;

  Serial.print("the inference time：");
  Serial.print(executionTime);
  Serial.println(" μm");
  // print the memory left 

  size_t freeHeap = ESP.getFreeHeap();
  Serial.print("Available memory：");
  Serial.print(freeHeap);
  Serial.println(" byte");
  count += 1;
    delay(3000);  
}
