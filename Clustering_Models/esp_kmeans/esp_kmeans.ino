#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino.h>

const int k = 3;
const int num_features = 128;
const char* ssid = "CCTV1";
const char* password = "cgy6726288";
//const char* storageURL = "https://storage.googleapis.com/bmepredict/BME_TRAIN_4.txt";
const char* storageURL = "https://bmedata.oss-cn-hangzhou.aliyuncs.com/BME_TRAIN_4.txt";
String payload;

double **initializeCentroids() {
  // Allocate memory for the weight matrix
  double **preTrainedCentroids = new double *[k];
  const double centroids[][num_features] = {
    {0.025532, 0.026723, 0.023196, 0.026678, 0.026995, 0.042801, 0.086189, 0.144458, 0.220185, 0.296607, 0.350409, 0.375320, 0.369310, 0.344015, 0.311730, 0.261162, 0.196571, 0.136480, 0.083656, 0.051899, 0.036854, 0.032412, 0.028779, 0.030868, 0.025785, 0.025976, 0.024351, 0.026781, 0.024642, 0.024695, 0.024260, 0.015862, -0.009719, -0.044866, -0.090874, -0.147842, -0.222759, -0.309016, -0.399940, -0.502053, -0.630068, -0.765587, -0.875013, -0.947933, -0.991300, -1.014633, -1.025133, -1.029383, -1.030800, -1.031283, -1.031350, -1.031267, -1.031683, -1.032583, -1.032933, -1.032783, -1.032483, -1.032017, -1.031867, -1.032250, -1.032800, -1.033083, -1.032883, -1.032817, -1.032917, -1.033167, -1.031267, -1.026350, -1.020983, -1.017433, -1.015717, -1.014912, -1.014158, -1.014250, -1.013843, -1.014177, -1.014104, -1.012242, -1.007448, -1.002486, -0.993711, -0.975548, -0.948972, -0.916589, -0.880270, -0.844457, -0.804775, -0.756394, -0.700495, -0.638585, -0.570678, -0.506978, -0.451820, -0.402003, -0.353079, -0.292891, -0.221448, -0.155166, -0.108955, -0.079601, -0.062129, -0.048225, -0.031518, -0.008509, 0.006968, 0.019367, 0.052577, 0.077075, 0.105455, 0.147850, 0.205690, 0.261199, 0.337624, 0.404398, 0.425521, 0.416053, 0.378099, 0.320530, 0.251457, 0.177243, 0.115019, 0.071946, 0.049446, 0.036971, 0.027217, 0.025285, 0.026618, 0.026107},
    {0.028176, 0.024879, 0.026583, 0.025094, 0.024507, 0.030211, 0.045023, 0.073314, 0.110002, 0.155385, 0.198971, 0.222869, 0.236442, 0.235715, 0.214070, 0.178075, 0.138593, 0.102646, 0.073865, 0.059038, 0.048773, 0.037798, 0.028619, 0.031091, 0.022292, 0.026984, 0.023713, 0.024777, 0.023136, 0.028480, 0.032178, 0.032647, 0.039188, 0.048846, 0.064078, 0.080591, 0.104885, 0.138531, 0.202371, 0.309708, 0.459785, 0.607106, 0.731722, 0.829101, 0.898157, 0.940592, 0.967222, 0.985368, 0.996826, 1.005971, 1.011681, 1.014333, 1.015565, 1.016362, 1.016986, 1.017464, 1.017725, 1.017565, 1.017522, 1.017623, 1.017130, 1.016478, 1.015942, 1.015652, 1.015565, 1.016058, 1.016507, 1.016551, 1.016638, 1.016449, 1.016319, 1.016319, 1.016536, 1.016536, 1.016435, 1.016536, 1.016768, 1.016696, 1.016014, 1.015406, 1.015739, 1.016000, 1.016043, 1.016145, 1.016159, 1.016188, 1.005841, 0.969362, 0.909174, 0.836565, 0.754609, 0.662328, 0.553989, 0.453769, 0.367646, 0.305997, 0.263777, 0.237608, 0.210210, 0.179998, 0.144240, 0.115135, 0.091287, 0.080062, 0.067701, 0.059721, 0.064538, 0.089056, 0.115773, 0.148496, 0.172483, 0.201069, 0.228461, 0.245795, 0.251665, 0.244824, 0.224785, 0.174641, 0.114936, 0.073210, 0.049562, 0.040282, 0.031166, 0.027336, 0.025779, 0.022844, 0.025467, 0.027194},
    {0.023897, 0.022405, 0.023726, 0.026506, 0.032919, 0.040193, 0.064676, 0.112930, 0.170394, 0.213880, 0.231983, 0.240191, 0.234849, 0.221041, 0.196243, 0.163377, 0.131333, 0.108726, 0.085336, 0.061704, 0.048100, 0.031663, 0.029993, 0.027038, 0.022764, 0.028210, 0.023115, 0.021460, 0.024565, 0.024007, 0.025541, 0.035889, 0.069054, 0.144126, 0.263144, 0.402074, 0.534368, 0.666970, 0.787115, 0.875939, 0.937510, 0.977667, 0.999961, 1.010333, 1.014863, 1.016529, 1.016980, 1.017196, 1.017510, 1.018000, 1.018078, 1.017824, 1.017275, 1.016529, 1.016608, 1.017098, 1.017686, 1.017765, 1.017784, 1.018255, 1.018784, 1.018647, 1.017725, 1.016725, 1.016824, 1.017667, 1.018137, 1.018431, 1.018373, 1.016137, 1.010059, 1.003745, 0.999941, 0.998020, 0.992401, 0.973916, 0.941573, 0.904477, 0.870129, 0.829984, 0.771588, 0.694149, 0.616209, 0.542215, 0.466435, 0.378881, 0.281169, 0.188505, 0.117438, 0.071260, 0.045258, 0.030957, 0.030466, 0.026157, 0.025543, 0.026482, 0.026340, 0.024594, 0.023400, 0.025604, 0.025593, 0.021651, 0.021169, 0.026953, 0.023802, 0.024909, 0.028085, 0.036296, 0.060251, 0.086441, 0.112349, 0.135839, 0.146948, 0.154179, 0.151178, 0.139816, 0.118228, 0.095279, 0.067374, 0.051409, 0.035694, 0.028640, 0.027256, 0.024707, 0.024776, 0.024755, 0.025209, 0.029370}
  };

  for (int i = 0; i < k; i++) {
    preTrainedCentroids[i] = new double[num_features];
  }

  // Copy the weights to the preTrainedWeights matrix
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < num_features; j++) {
      preTrainedCentroids[i][j] = centroids[i][j];
    }
  }
  return preTrainedCentroids;
}

bool downloadFromGCS(const char* url) {
  HTTPClient http;

  http.begin(url);
  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    payload = http.getString();
    Serial.println("Downloaded data:");
    //Serial.println(payload);
    http.end();
    return true;
  } else {
    Serial.printf("Failed to download data. HTTP code: %d\n", httpCode);
    http.end();
    return false;
  }
}

bool parsePayload(const String& payload, double* train_data, double* train_class_labels, int train_samples, int m_features) {
  int pos = 0;
  int count = 0;
  //Serial.printf("length: %d\n", payload.length());
  while (pos < payload.length() && count < train_samples) {
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

double euclidean_distance(double *vector1, double *vector2, int length) {
  double sum = 0.0;
  for (int i = 0; i < length; i++) {
    double diff = vector1[i] - vector2[i];
    sum += diff * diff;
  }
  return sqrt(sum);
}

void kMeansInference(double *input_data, double **centroids, int n_samples, int m_features, int *assignments) {
  for (int sample_index = 0; sample_index < n_samples; sample_index++) {
        double *sample = &input_data[sample_index * m_features];
        double min_distance = INFINITY;
        int predicted_cluster = -1;

        for (int i = 0; i < k; i++) {
            double distance = euclidean_distance(centroids[i], sample, m_features);
            if (distance < min_distance) {
                min_distance = distance;
                predicted_cluster = i + 1;
            }
        }

        assignments[sample_index] = predicted_cluster;
    }

}
double calculate_rand_index(int *assignment, double *class_labels, int n_samples) {
    int TP = 0, TN = 0, FP = 0, FN = 0;

    for (int i = 0; i < n_samples - 1; i++) {
        for (int j = i + 1; j < n_samples; j++) {
            if (class_labels[i] == class_labels[j]) {
                // Same class in ground truth
                if (assignment[i] == assignment[j]) {
                    TP++;
                } else {
                    FN++;
                }
            } else {
                // Different classes in ground truth
                if (assignment[i] == assignment[j]) {
                    FP++;
                } else {
                    TN++;
                }
            }
        }
    }
    double rand_index = (double)(TP + TN) / (TP + FP + TN + FN);
    return rand_index;
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  double **preTrainedCentroids = initializeCentroids();

  int fh1 = ESP.getFreeHeap();
  Serial.printf("Free heap before kMeansInference: %u bytes\n", fh1); 
  bool success = downloadFromGCS(storageURL);

  if (success) {
    int n_samples = 30; // Number of samples
    int m_features = 128;    // Number of features per sample (assuming fixed)

    // Allocate memory for data and class labels
    double* train_data = (double*)malloc(n_samples * m_features * sizeof(double));
    double* train_class_labels = (double*)malloc(n_samples * sizeof(double));
    int *assignments = (int *)malloc(n_samples * sizeof(int));
    parsePayload(payload, train_data, train_class_labels, n_samples, m_features);
    //Serial.printf("Free heap1 after kMeansInference: %u bytes\n", ESP.getFreeHeap());
    /*if (success) {
      // Use train_data and train_class_labels as needed
      for (int i = 0; i < train_samples; i++) {
        Serial.print(i);
        Serial.print("\t");
        Serial.printf("%lf\n", train_class_labels[i]);
        for (int j = 0; j < m_features; j++) {
          // You can use train_data[i * m_features + j] here
        }
      }
    } else {
      Serial.println("Failed to parse payload.");
    }*/

  // Print the weights for verification
  /*for (int i = 0; i < k; i++) {
    for (int j = 0; j < num_features; j++) {
      Serial.printf("%lf", preTrainedCentroids[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }*/
    // Run kMeansInference multiple times
    const int num_runs = 100;
    unsigned long total_time = 0;

    for (int run = 0; run < num_runs; ++run) {
      unsigned long start_time = millis();
      
    // Perform K-Means inference
      
      kMeansInference(train_data, preTrainedCentroids, n_samples, m_features, assignments);
      //printf("Safe");
      unsigned long end_time = millis();
      unsigned long run_time = end_time - start_time;

      total_time += run_time;
    }

    // Calculate average running time
    unsigned long average_time = total_time / num_runs;
    Serial.printf("Average running time for %d runs: %lu milliseconds\n", num_runs, average_time);

    int fh2 = ESP.getFreeHeap();
    Serial.printf("Free heap after kMeansInference: %u bytes\n", fh2);
    Serial.printf("Memory Consumption of kMeansInference: %u bytes\n", fh1 - fh2);

    // Output the predicted cluster
    printf("Assigned clusters:\n");
    for (int i = 0; i < n_samples; i++) {
        printf("%d\t%d\t%lf\n ", i, assignments[i], train_class_labels[i]);
    }
    printf("\n");
    double rand_index = calculate_rand_index(assignments, train_class_labels, n_samples);
    printf("RAND index: %.4f\n", rand_index);

    
    // Free allocated memory
    free(train_data);
    free(train_class_labels);
  } else {
    Serial.println("Failed to download data.");
  }
}

void loop() {
  // Your code here

}

