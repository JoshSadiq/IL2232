
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <malloc/malloc.h> 
double euclidean_distance(double *vector1, double *vector2, int length) {
    double sum = 0.0;
    for (int i = 0; i < length; i++) {
        double diff = vector1[i] - vector2[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}

double** kmeans(int *assignment, int K, int max_iter, int n_samples, int m_features, double *data) {

    // Initialize centroids
    double** centroids = (double**)malloc(K * sizeof(double*));
    for (int i = 0; i < K; i++) {
        centroids[i] = (double*)malloc(m_features * sizeof(double));
        for (int j = 0; j < m_features; j++) {
            centroids[i][j] = data[i * 11 * m_features + j]; //for BME
            //centroids[i][j] = data[i * m_features + j]; // for Iris
        }
    }

    // Main K-means loop
    int iter = 0;
    while (iter < max_iter) {
        // Assign samples to nearest centroid
        for (int i = 0; i < n_samples; i++) {
            double min_distance = INFINITY;
            int min_index = 0;

            for (int j = 0; j < K; j++) {
                double distance = 0.0;

                for (int k = 0; k < m_features; k++) {
                    double diff = data[i * m_features + k] - centroids[j][k];
                    distance += diff * diff;
                }

                if (distance < min_distance) {
                    min_distance = distance;
                    min_index = j;
                }
            }

            assignment[i] = min_index;
        }

        // Update centroids
        int *cluster_counts = (int *)malloc(K * sizeof(int)); // Dynamically allocate memory
        for (int i = 0; i < K; i++) {
            cluster_counts[i] = 0;
        }

        double (*new_centroids)[m_features] = (double (*)[m_features])malloc(K * sizeof(double[m_features])); // Dynamically allocate memory


        for (int i = 0; i < n_samples; i++) {
            int cluster = assignment[i];

            for (int j = 0; j < m_features; j++) {
                new_centroids[cluster][j] += data[i * m_features + j];
            }

            cluster_counts[cluster]++;
        }

        for (int i = 0; i < K; i++) {
            if (cluster_counts[i] > 0) {
                for (int j = 0; j < m_features; j++) {
                    centroids[i][j] = new_centroids[i][j] / cluster_counts[i];
                }
            }
        }

        iter++;
    }
    return centroids;
}


/*double calculate_rand_index(int *assignment, int *class_labels, int n_samples) {
    int TP = 0, TN = 0, FP = 0, FN = 0;

    for (int i = 0; i < n_samples; i++) {
        for (int j = i + 1; j < n_samples; j++) {
            if (class_labels[i] == class_labels[j]) {
                if (assignment[i] == assignment[j]) {
                    TP++;
                } else {
                    FN++;
                }
            } else {
                if (assignment[i] != assignment[j]) {
                    TN++;
                } else {
                    FP++;
                }
            }
        }
    }

    double rand_index = (double)(TP + TN) / (TP + FP + TN + FN);
    return rand_index;
}*/

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


// Function to print the cluster assignments
void printClusterAssignments(int *assignment, int n_samples) {
    printf("Cluster Assignments:\n");
    for (int i = 0; i < n_samples; i++) {
        printf("Sample %d -> Cluster %d\n", i, assignment[i]);
    }
}

int test() {
    int n_samples = 6;
    int m_features = 2;
    int K = 2;
    int max_iter = 100;
    double data[] = {
        1.0, 1.0,
        1.5, 2.0,
        3.0, 4.0,
        5.0, 7.0,
        3.5, 5.0,
        4.5, 5.0
    };

    // Allocate memory for cluster assignments
    int *assignment = (int *)malloc(n_samples * sizeof(int));

    // Perform K-means clustering
    kmeans(assignment, K, max_iter, n_samples, m_features, data);

    // Print the cluster assignments
    printClusterAssignments(assignment, n_samples);

    // Free memory
    free(assignment);

    return 0;
}

void kMeansInference(double *input_data, double **centroids, int n_samples, int m_features, int *assignments) {
  for (int sample_index = 0; sample_index < n_samples; sample_index++) {
        double *sample = &input_data[sample_index * m_features];
        double min_distance = INFINITY;
        int predicted_cluster = -1;

        for (int i = 0; i < 3; i++) {
            //double distance;
            /*for (int k = 0; k < m_features; k++) {
                    double diff = input_data[i * m_features + k] - centroids[i][k];
                    distance += diff * diff;
                }*/
            double distance = euclidean_distance(centroids[i * m_features], sample, m_features);
            if (distance < min_distance) {
                min_distance = distance;
                predicted_cluster = i + 1;
            }
        }

        assignments[sample_index] = predicted_cluster;
    }
}

void test_kmeans(int *test_assignment, int K, int n_test_samples, int m_features, double *test_data, double **centroids) {
    for (int i = 0; i < n_test_samples; i++) {
        double min_distance = INFINITY;
        int min_index = -1;

        for (int j = 0; j < K; j++) {
            double distance = euclidean_distance(test_data + i * m_features, centroids[j], m_features);

            if (distance < min_distance) {
                min_distance = distance;
                min_index = j;
            }
        }

        test_assignment[i] = min_index;
    }
}


int BME() {
    FILE* file = fopen("BME_COMBINE.txt", "r");
    if (file == NULL) {
        printf("Failed to open file BME\n");
        exit(1);
    }

    int train_samples = 180; // Number of samples
    int m_features = 128; // Number of features per sample (assuming fixed)

    // Allocate memory for data and class labels
    double *train_data = (double *)malloc(train_samples * m_features * sizeof(double));
    double *train_class_labels = (double *)malloc(train_samples * sizeof(double));

    for (int i = 0; i < train_samples; i++) {
        fscanf(file, "%lf", &train_class_labels[i]);
        //printf("%d\t%lf\n", i, train_class_labels[i]);
        for (int j = 0; j < m_features; j++) {
            fscanf(file, "%lf", &train_data[i * m_features + j]);
            //printf("%d\t%lf\n", j, train_data[i * m_features + j]);
        }
    }

    fclose(file);

    // Set hyperparameters for K-means
    int K = 3;
    int max_iter = 100; 

    // Allocate memory for cluster assignments
    int *assignment = (int *)malloc(train_samples * sizeof(int));
    double** train_centroids = (double**)malloc(K * sizeof(double*));

    // Perform K-means clustering
    train_centroids = kmeans(assignment, K, max_iter, train_samples, m_features, train_data);

    /*for (int i = 0; i < K; ++i) {
        for (int j = 0; j < m_features; ++j) {
            printf("%lf, ", train_centroids[i][j]);
        }
        printf("\n");
    }*/
    //kMeansInference(train_samples, train_centroids, train_samples, m_features, assignment);
    // Print the cluster assignments with class labels
    //printf("Sample\tCluster\tClass\n");

    test_kmeans(assignment, K, train_samples, m_features, train_data, train_centroids);

    for (int i = 0; i < train_samples; i++) {
        assignment[i] = assignment[i] + 1;
        printf("%d\t%d\t%d\n", i, assignment[i], (int)train_class_labels[i]);
    }

    // Calculate RAND index
    double rand_index = calculate_rand_index(assignment, train_class_labels, train_samples);
    printf("RAND index: %.4f\n", rand_index);
    
    // Free memory
    free(assignment);
    free(train_class_labels);
    free(train_data);
    free(train_centroids);

    return 0;
}


typedef struct {
    int x;
    int y;
} t_pos;



int main() {
    //iris();
    //BME();

    struct timespec start_time, end_time;
    double execution_time;

    // Start the timer
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    // Run the clustering algorithm
    //irisSOM();
    //iris();
    BME();
    //BMESOM();

    // Stop the timer
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    // Calculate the execution time
    execution_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    // Print the execution time
    printf("Execution time: %.6f seconds\n", execution_time);

    

    return 0;
}
