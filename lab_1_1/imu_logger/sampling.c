#include "sampling.h"
#include "pico/stdlib.h"
#include <stdio.h>

#define PERIOD_US        2000   // 2ms -> 500Hz
#define TEST_DURATION_S  10     // 10 seconds

void sampling_timing_test(void) {
    absolute_time_t start = get_absolute_time();// TODO 1: get a starting absolute_time_t "now", and a starting
    // time_us_64() timestamp (you need both: the absolute_time_t for
    // pacing the loop, the raw microsecond count for measuring elapsed
    // real time afterward)

   int32_t IterationsForPeriod = ((TEST_DURATION_S*1000000)/PERIOD_US); // TODO 2: work out how many iterations TEST_DURATION_S seconds at
    // PERIOD_US should take (simple arithmetic, not a magic number)

    int64_t count = 0;
    // TODO 3: loop that many times. Each iteration:
    //   - advance your deadline by PERIOD_US (from the PREVIOUS deadline,
    //     not from "now" -- see the drift explanation above)
    //   - busy_wait_until() that deadline
    //   - increment count
    absolute_time_t deadline = start;
    while(count < IterationsForPeriod){
        deadline = delayed_by_us(deadline, PERIOD_US);
        busy_wait_until(deadline);
        count = count + 1;
    }

    // TODO 4: take another time_us_64() timestamp, compute real elapsed
    // seconds from the difference, and printf: the iteration count, the
    // elapsed time, and count / elapsed_seconds as your achieved Hz
    float TimePassed_us2 = absolute_time_diff_us(start, get_absolute_time());
    float TimePassed_s = (TimePassed_us2/1000000.0f);
    float Achieved_Frequency =(count/TimePassed_s);
    printf("Iteration count: %llu, elapsed time: %.2f, achieved Hz: %.2f\n", count, TimePassed_s, Achieved_Frequency);
}