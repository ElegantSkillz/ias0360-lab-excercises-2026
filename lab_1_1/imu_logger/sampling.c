#include "sampling.h"
#include "pico/stdlib.h"
#include <stdio.h>

#define PERIOD_US        2000   // 2ms -> 500Hz
#define TEST_DURATION_S  10     // 10 seconds

void sampling_timing_test(void) {
    absolute_time_t start = get_absolute_time();// get_absolute_time is used to establish start point of sampling.

   int32_t IterationsForPeriod = ((TEST_DURATION_S*1000000)/PERIOD_US); // Established test duration for 10 seconds at 500 Hz sampling Iterations are calculated.

    int64_t count = 0; //Counting is initialized
    // TODO 3: loop that many times. Each iteration:
    //   - advance your deadline by PERIOD_US (from the PREVIOUS deadline,
    //     not from "now" -- see the drift explanation above)
    //   - busy_wait_until() that deadline
    //   - increment count
    absolute_time_t deadline = start; //deadline is made equal with start point
    while(count < IterationsForPeriod){ // While count is smaller than number of iterations in test period:
        deadline = delayed_by_us(deadline, PERIOD_US); //deadline is advanced by single sample period
        busy_wait_until(deadline); // Wait until deadline
        count = count + 1; // increment count
    }

    float TimePassed_us2 = absolute_time_diff_us(start, get_absolute_time()); // Time passed from start is measured again in this point.
    float TimePassed_s = (TimePassed_us2/1000000.0f); // Time is converted from microseconds to seconds.
    float Achieved_Frequency =(count/TimePassed_s); // Sampling frequency is verified over dividing the count of samples and time passed for measuring them.
    printf("Iteration count: %llu, elapsed time: %.2f, achieved Hz: %.2f\n", count, TimePassed_s, Achieved_Frequency); // It prints out the result.
}