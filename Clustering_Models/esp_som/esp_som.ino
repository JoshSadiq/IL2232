
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino.h>




// *********** Constant variable ***********//
const int height = 3; 
const int width = 1; 
const int m_features = 128;
const char* ssid = "xiaomi13"; //your wifi ssid
const char* password = "itsmygo77"; //your wifi password
const char* storageURL = "https://storage.googleapis.com/bmepredict/BME_TRAIN_4.txt";
//const char* storageURL = "https://bmedata.oss-cn-hangzhou.aliyuncs.com/BME_TRAIN_4.txt";
String payload;


typedef struct {
 int x;
 int y;
} t_pos;




// *********** Functions ***********//
/**
* @brief   Trained SOM neuron weights info import
*
* @return  preTrainedWeights
*/
double **initializeWeights()
{
 // Allocate memory for the weight matrix
 double **preTrainedWeights = new double *[height * width];
 for (int i = 0; i < height * width; i++)
 {
   preTrainedWeights[i] = new double[m_features];
 }


 // Manually copy the weights from the provided data
 const double neuronWeights[][128] =
 {
 // Neuron (0, 0) weights
   {0.030962, 0.029352, 0.030109, 0.032853, 0.024414, 0.026097, 0.029583, 0.029079, 0.032330, 0.036929, 0.033441, 0.029489, 0.031127, 0.030596, 0.036490, 0.034761, 0.025908, 0.032959, 0.024275, 0.028995, 0.026392, 0.029612, 0.026419, 0.031685, 0.029607, 0.022183, 0.024647, 0.024724, 0.023645, 0.024834, 0.027399, 0.015833, -0.020786, -0.106035, -0.196818, -0.264863, -0.328978, -0.384369, -0.439694, -0.513646, -0.615874, -0.718688, -0.784706, -0.816401, -0.828381, -0.831994, -0.831318, -0.829744, -0.828546, -0.826621, -0.824415, -0.823431, -0.824061, -0.825902, -0.827032, -0.826978, -0.826359, -0.825975, -0.825904, -0.826170, -0.826475, -0.825993, -0.825465, -0.825706, -0.826139, -0.826188, -0.825996, -0.825995, -0.825815, -0.825260, -0.825352, -0.825677, -0.825530, -0.825857, -0.826613, -0.826779, -0.827065, -0.826486, -0.823036, -0.820076, -0.818987, -0.812207, -0.791525, -0.755235, -0.703981, -0.650569, -0.600169, -0.539278, -0.469511, -0.402713, -0.330620, -0.249604, -0.179717, -0.137458, -0.120658, -0.089031, -0.056317, -0.017355, 0.004043, 0.015293, 0.013375, 0.022196, 0.015805, 0.031059, 0.023654, 0.039973, 0.075848, 0.100032, 0.136667, 0.201572, 0.273214, 0.345577, 0.472377, 0.591997, 0.657614, 0.681723, 0.674408, 0.620588, 0.520438, 0.385748, 0.245942, 0.136621, 0.073756, 0.042452, 0.034501, 0.029192, 0.028452, 0.026627},
   // Neuron (1, 0) weights
   {0.030349, 0.028301, 0.029681, 0.029959, 0.025327, 0.025761, 0.028016, 0.027224, 0.028350, 0.029835, 0.027835, 0.022450, 0.024922, 0.025487, 0.030959, 0.028985, 0.023031, 0.028803, 0.023547, 0.027712, 0.024504, 0.029147, 0.026919, 0.030838, 0.025723, 0.023704, 0.026404, 0.023890, 0.022975, 0.027604, 0.027339, 0.017135, -0.006786, -0.057784, -0.109596, -0.147885, -0.179741, -0.205575, -0.226714, -0.248376, -0.276000, -0.308786, -0.314943, -0.303131, -0.289463, -0.280470, -0.274404, -0.269611, -0.266132, -0.258213, -0.250571, -0.246752, -0.245897, -0.246461, -0.246821, -0.246558, -0.245957, -0.245670, -0.245576, -0.245723, -0.246016, -0.245743, -0.245274, -0.245393, -0.245676, -0.245538, -0.245467, -0.245616, -0.245544, -0.245568, -0.246195, -0.246808, -0.246679, -0.246541, -0.246603, -0.246644, -0.247247, -0.247161, -0.246096, -0.247416, -0.250112, -0.247532, -0.235774, -0.216449, -0.191899, -0.169379, -0.149143, -0.121510, -0.083612, -0.040845, -0.000176, 0.035571, 0.056555, 0.052825, 0.033722, 0.036126, 0.042649, 0.053129, 0.051068, 0.047534, 0.036047, 0.034963, 0.022087, 0.035754, 0.037578, 0.060845, 0.097688, 0.138715, 0.191197, 0.270409, 0.349879, 0.425612, 0.531498, 0.623131, 0.674676, 0.689785, 0.667745, 0.588922, 0.462648, 0.325290, 0.205025, 0.117200, 0.064322, 0.039107, 0.030829, 0.028182, 0.028485, 0.028107},
   // Neuron (2, 0) weights
   {0.029857, 0.026079, 0.028486, 0.025612, 0.026142, 0.025670, 0.026952, 0.027456, 0.027441, 0.027819, 0.027952, 0.022383, 0.024235, 0.026704, 0.030260, 0.026604, 0.023505, 0.025697, 0.024093, 0.025430, 0.022069, 0.027611, 0.027526, 0.029333, 0.019822, 0.026667, 0.029039, 0.022148, 0.021367, 0.031115, 0.027327, 0.020959, 0.020476, 0.028953, 0.045331, 0.060176, 0.085209, 0.106901, 0.137298, 0.194084, 0.283746, 0.363779, 0.451521, 0.530907, 0.583489, 0.610937, 0.624729, 0.634042, 0.640734, 0.658361, 0.674971, 0.683535, 0.687004, 0.688480, 0.689167, 0.689674, 0.690290, 0.690433, 0.690563, 0.690708, 0.690515, 0.690440, 0.690771, 0.690753, 0.690717, 0.691240, 0.691281, 0.690979, 0.690887, 0.690048, 0.688670, 0.687682, 0.687743, 0.688494, 0.689426, 0.689472, 0.688096, 0.686964, 0.683705, 0.674913, 0.665726, 0.661040, 0.655263, 0.642416, 0.621589, 0.593496, 0.563532, 0.534628, 0.517226, 0.516964, 0.505842, 0.470808, 0.416201, 0.341196, 0.265814, 0.222262, 0.185851, 0.153153, 0.116004, 0.092572, 0.067224, 0.052357, 0.030016, 0.040511, 0.052963, 0.082437, 0.113919, 0.176461, 0.254247, 0.359249, 0.456356, 0.541024, 0.616314, 0.664544, 0.694026, 0.697553, 0.656837, 0.542676, 0.379949, 0.241146, 0.149714, 0.091657, 0.052468, 0.034635, 0.025414, 0.027405, 0.028536, 0.031030}
 };
 // Copy the weights to the preTrainedWeights matrix
 for (int i = 0; i < height * width; i++) {
   for (int j = 0; j < m_features; j++) {
     preTrainedWeights[i][j] = neuronWeights[i][j];
   }
 }
 return preTrainedWeights;
}


/**
* @brief   Calculate euclidean distance between two vectors
*
* @return  sqrt(sum)
*/
double euclidean_distance(double *vector1, double *vector2, int length)
{
 double sum = 0.0;
 for (int i = 0; i < length; i++) {
   double diff = vector1[i] - vector2[i];
   sum += diff * diff;
 }
 return sqrt(sum);
}


/**
* @brief   Find the best matching unit of the input samples, update the best unit with the smallest distance
*
* @return  void
*/
void find_best_matching_unit(double **weights, double *sample, int height, int width, int m_features, t_pos *best_unit)
{
 double min_distance = INFINITY;
 for (int i = 0; i < height; i++) {
   for (int j = 0; j < width; j++) {
     double distance = euclidean_distance(weights[i * width + j], sample, m_features);
     if (distance < min_distance) {
       min_distance = distance;
       best_unit->x = i;
       best_unit->y = j;
     }
   }
 }
}


/**
* @brief   SOM model Inference process for input samples, update the assignment with best unit
*
* @return  void
*/
void SOMInference(t_pos *assignment, double *data, int n_samples, int m_features, int height, int width, double **weights)
{
 for (int sample_index = 0; sample_index < n_samples; sample_index++)
 {
   double *sample = &data[sample_index * m_features];
   t_pos best_unit;
   find_best_matching_unit(weights, sample, height, width, m_features, &best_unit);
   assignment[sample_index] = best_unit;
 }
}




/**
* @brief   Download the dataset from google cloud, store the dataset in payload
*
* @return  success of download
*/
bool downloadFromGCS(const char* url) {
 HTTPClient http;
 http.begin(url);
 int httpCode = http.GET();


 if (httpCode == HTTP_CODE_OK)
 {
   payload = http.getString();
   Serial.println("Downloaded data:");
   //Serial.println(payload);
   http.end();
   return true;
 } else
 {
   Serial.printf("Failed to download data. HTTP code: %d\n", httpCode);
   http.end();
   return false;
 }
}


/**
* @brief   Parse and re-organize the payload
*
* @return  success of download
*/
bool parsePayload(const String& payload, double* train_data, double* train_class_labels, int train_samples, int m_features)
{
 int pos = 0;
 int count = 0;
 //Serial.printf("length: %d\n", payload.length());
 while (pos < payload.length() && count < train_samples)
 {
   int bytesRead = sscanf(payload.c_str() + pos, "%lf", &train_class_labels[count]);
   //Serial.println(payload.c_str());
   //Serial.printf("%lf\n",train_class_labels[count]);
   if (bytesRead != 1) {
     Serial.println("Failed to parse class label.");
     return false;
   }
   pos = payload.indexOf(' ', pos) + 1;


   for (int j = 0; j < m_features; j++) {
     bytesRead = sscanf(payload.c_str() + pos, "%lf", &train_data[count * m_features + j]);
     //Serial.printf("Features: %lf\n",train_data[count * m_features + j]);
     if (bytesRead != 1) {
       Serial.println("Failed to parse feature.");
       return false;
     }
     pos = payload.indexOf(' ', pos) + 1;
   }
   count++;
 }
 return true;
}







void setup()
{
 Serial.begin(115200);
 delay(3000);  // Allow time for serial monitor to initialize
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
   delay(1000);
   Serial.println("Connecting to WiFi...");
 }

 double **preTrainedWeights = initializeWeights();
 /* PRINT TEST
 // Print the weights for verification
 for (int i = 0; i < height * width; i++) {
   for (int j = 0; j < m_features; j++) {
     Serial.printf("%lf", preTrainedWeights[i][j]);
     Serial.print(" ");
   }
   Serial.println();
 }
*/
  int fh1 = ESP.getFreeHeap();
  Serial.printf("Free heap before somInference: %u bytes\n", fh1);
  bool success = downloadFromGCS(storageURL);


  if (success)
  {
    int train_samples = 30; // Number of samples
    int m_features = 128;    // Number of features per sample (assuming fixed)
    // Allocate memory for data and class labels
    double* train_data = (double*)malloc(train_samples * m_features * sizeof(double));
    double* train_class_labels = (double*)malloc(train_samples * sizeof(double));
    t_pos *assignment = (t_pos *)malloc(train_samples * sizeof(t_pos));
    success = parsePayload(payload, train_data, train_class_labels, train_samples, m_features);

    /* PRINT TEST
    // Print the orign labels
    if (success)
    {
      // Use train_data and train_class_labels as needed
      for (int i = 0; i < train_samples; i++) {
        Serial.print(i);
        Serial.print("\t");
        Serial.printf("%lf\n", train_class_labels[i]);
        for (int j = 0; j < m_features; j++) {
          // You can use train_data[i * m_features + j] here
        }
      }
    }
    else
    {
      Serial.println("Failed to parse payload.");
    }
    */

    // Run SOMInference multiple times to get the
    const int num_runs = 100;
    unsigned long total_time = 0;
    for (int run = 0; run < num_runs; ++run) 
    {
      unsigned long start_time = millis();
      // Call the inference function
      SOMInference(assignment, train_data, train_samples, m_features, height, width, preTrainedWeights);
      unsigned long end_time = millis();
      unsigned long run_time = end_time - start_time;
      total_time += run_time;
    }
    // Calculate average running time
    unsigned long average_time = total_time / num_runs;
    Serial.printf("Average running time for %d runs: %lu milliseconds\n", num_runs, average_time);

    int fh2 = ESP.getFreeHeap();
    Serial.printf("Free heap after somInference: %u bytes\n", fh2);
    Serial.printf("Memory Consumption of somInference: %u bytes\n", fh1 - fh2);

    // Access the clustering result
    for (int i = 0; i < train_samples; i++) 
    {
      Serial.printf("Sample %d is assigned to unit (%d, %d)\n", i, assignment[i].x, assignment[i].y);
    }

    // Free allocated memory
    free(train_data);
    free(train_class_labels);
  }// if (success)
  else 
  {
    Serial.println("Failed to download data.");
  }

  // Clean up memory
  for (int i = 0; i < height * width; i++) 
  {
    delete[] preTrainedWeights[i];
  }
  delete[] preTrainedWeights;

}


void loop() {
   // Your main code goes here
}

