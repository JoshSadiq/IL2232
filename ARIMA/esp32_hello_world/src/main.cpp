// Used for debugging and information display
// #include <Arduino.h> // Should be the ESP.getFreeHeap() header, but need to download libraries? 
#include "esp_log.h"
// #include <unistd.h>
// Used for calculating execution time
#include <chrono>
using namespace std::chrono;

// For debugging
static const char* TAG = "MyModule";
// size_t freeHeap = ESP.getFreeHeap(); // Needs Arduino header? Look back at later


// Dataset: "Global land surface temperature anomalies" values
float A[] = {-0.50,-0.43,-0.46,-0.67,-0.71,-0.58,-0.51,-0.49,-0.44,-0.32,-0.54,-0.55,-0.53,-0.57,-0.43,-0.43,-0.36,-0.29,-0.41,-0.24,-0.17,-0.13,-0.29,-0.38,-0.45,-0.34,-0.17,-0.61,-0.44,-0.42,-0.35,-0.48,-0.48,-0.31,-0.05,-0.08,-0.45,-0.62,-0.48,-0.31,-0.35,-0.14,-0.25,-0.28,-0.24,-0.14,-0.01,-0.21,-0.13,-0.47,-0.11,-0.01,-0.03,-0.35,-0.06,-0.17,-0.12,-0.02,0.17,0.09,0.07,0.10,0.06,0.07,0.19,-0.07,-0.01,0.04,0.06,-0.07,-0.33,-0.07,-0.06,0.19,-0.13,-0.12,-0.41,-0.04,0.14,0.08,-0.02,0.11,0.15,0.20,-0.23,-0.13,-0.06,0.01,-0.12,-0.08,0.04,-0.03,-0.17,0.33,-0.19,0.13,-0.24,0.25,0.11,0.17,0.31,0.53,0.12,0.51,0.07,0.10,0.30,0.45,0.58,0.36,0.66,0.53,0.25,0.35,0.48,0.77,0.35,0.64,0.98,0.78,0.63,0.85,0.97,0.96,0.83,1.10,0.99,1.13,0.90,0.91,1.16,0.93,0.98,1.05,1.04,1.42,1.54,1.41,1.22,1.43,1.59};

// ARIMA parameters extracted from Python
float params[] = {-1.086464,
                -0.672785,
                -0.537128,
                -0.522477,
                -0.619176,
                0.723350};

// Program start
extern "C" {
    void app_main() {
        ESP_LOGI(TAG, "\r\n\r\nApplication started...\r\n\r\n");

        // Main loop running indefinitely
        for(int j = 0; j < 10; j++) {
        // Start of execution time for in-sample prediction
        ESP_LOGD(TAG, "\r\n\r\nPrediction running...\r\n\r\n");
        // B: Predictions stored in this array as for-loop below runs
        // C: Errors array, similar as above
        auto start = high_resolution_clock::now();
        float B[] = {};
        float C[] = {}; 
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        auto exec_time = duration.count();
        ESP_LOGI(TAG, "Array init. execution time: %llu us", exec_time);
        
        start = high_resolution_clock::now();
        // For-loop for in-sample prediction generation
        for (int i = 0; i < 141; i++){
            // Init. prediction and error as 0 for each timestep 
            float pred = 0;
            float err = 0;

            // 
            if (i - 1 >= 0){
                pred += params[0]*A[i-1];    // y_t-1
                err = A[i] - pred;
            }

            if (i - 2 >= 0){
                pred += params[1]*A[i-2];    // y_t-2
                pred += params[2]*C[i-1];    // err_t-1
            }

            if (i - 3 >= 0){
                pred += params[3]*C[i-2];    // err_t-2
            }
            if (i - 4 >= 0){
                pred += params[4]*C[i-3];    // err_t-3
            }
            if (i - 5 >= 0){
                pred += params[5]*C[i-4];    // err_t-4
            }           
            B[i] = pred;
            C[i] = err;

            // ESP_LOGD(TAG, "Current calc: %.5f", calc);

            }
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        exec_time = duration.count();
        ESP_LOGI(TAG, "In-sample prediction's execution time: %llu us", exec_time);

        // Out-of-sample / Future forecast 
        start = high_resolution_clock::now();       
        for (int i = 141; i < 1500; i++){
            // Init. prediction and error as 0 for each timestep 
            float pred = 0;
            float err = 0;

            // 
            if (i - 1 >= 0){
                pred += params[0]*A[i-1];    // y_t-1
                err = A[i] - pred;
            }

            if (i - 2 >= 0){
                pred += params[1]*A[i-2];    // y_t-2
                pred += params[2]*C[i-1];    // err_t-1
            }

            if (i - 3 >= 0){
                pred += params[3]*C[i-2];    // err_t-2
            }
            if (i - 4 >= 0){
                pred += params[4]*C[i-3];    // err_t-3
            }
            if (i - 5 >= 0){
                pred += params[5]*C[i-4];    // err_t-4
            }           
            B[i] = pred;
            C[i] = err;

            // ESP_LOGD(TAG, "Current calc: %.5f", calc);

            }
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        exec_time = duration.count();
        ESP_LOGI(TAG, "Forecast prediction's execution time: %llu us", exec_time);

        }
    
    ESP_LOGI(TAG, "\r\n\r\nApplication finished running!\r\n\r\n");

    }
}