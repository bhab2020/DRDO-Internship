#include <stdio.h>
#include <math.h>

#define SIGNAL_LENGTH 20
#define WINDOW_SIZE 5

void moving_window(double ecg_signal[], int signal_length, int window_size) {
    double window[WINDOW_SIZE];
    int qrs_peaks[SIGNAL_LENGTH];
    int qrs_index = 0;

    for (int i = 0; i < signal_length; i++) {
        window[i % window_size] = ecg_signal[i];

        if (i >= window_size - 1) {
            double derivative[WINDOW_SIZE - 1];
            double squared[WINDOW_SIZE - 1];

            for (int j = 1; j < window_size; j++) {
                derivative[j - 1] = window[j] - window[j - 1];
                squared[j - 1] = pow(derivative[j - 1], 2);
            }

            double filtered[WINDOW_SIZE - 1];
            for (int j = 0; j < window_size - 1; j++) {
                filtered[j] = squared[j]; 
            }

            double threshold = 0.5 * filtered[0];
            int peak_index = 0;
            double max_value = filtered[0];

            for (int j = 1; j < window_size - 1; j++) {
                if (filtered[j] > max_value) {
                    max_value = filtered[j];
                    peak_index = j;
                }
            }

            if (filtered[peak_index] > threshold) {
                qrs_peaks[qrs_index++] = i - (window_size - 1) + peak_index;
            }
        }
    }

    printf("Detected QRS peaks: ");
    for (int i = 0; i < qrs_index; i++) {
        printf("%d ", qrs_peaks[i]);
    }
    printf("\n");
}

int main() {
    double ecg_signal[SIGNAL_LENGTH] = {1.2, 0.9, 1.5, 1.6, 2.0, 2.1, 1.8, 1.4, 1.0, 0.7, 0.9, 1.1, 1.6, 1.9, 2.3, 2.2, 1.7, 1.3, 1.1, 0.8};

    moving_window(ecg_signal, SIGNAL_LENGTH, WINDOW_SIZE);

    return 0;
}