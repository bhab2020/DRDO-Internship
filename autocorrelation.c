#include <stdio.h>

#define SIGNAL_LENGTH 3

void autoCorrelation(int signal[], int correlation[])
{
    int i, j;

    for (i = 0; i < SIGNAL_LENGTH; i++) 
    {
        correlation[i] = 0;
        for (j = 0; j < SIGNAL_LENGTH - i; j++) 
        {
            correlation[i] += signal[j] * signal[j + i];
        }
    }
}

int main()
{
    int signal[SIGNAL_LENGTH] = {1, 2, 3};
    int correlation[SIGNAL_LENGTH];

    autoCorrelation(signal, correlation);

    printf("Auto-correlation of the signal:\n");
    for (int i = 0; i < SIGNAL_LENGTH; i++) 
    {
        printf("correlation[%d] = %d\n", i, correlation[i]);
    }

    return 0;
}
