#include "pico/stdlib.h"
#include "sampling.h"
#include "buffer.h"
#include "stdio.h"
#include "stats.h"
#include "math.h"

#define TEST_PUSH_COUNT 350
#define EPSILON 0.0001f // Defines the accepted error of roundings coming from math operators in comparison to the expected values.

int main() {
    stdio_init_all();
    sleep_ms(2000); //Give the microcontroller some bootup time. If I use screen to check for output then I have time to open it before the outputs are printed.
    buffer_init();
    

    uint32_t success = 0;
    uint32_t failure = 0;
    for(int i = 0; i < TEST_PUSH_COUNT; i++){
        bool push = buffer_push((float)i); // Index is cast to float. Push to buffer is performed as many times as test parameter specifies.
        if(push == 1){ // If push is successful then the success count is appended.
            success++;
        }else{ // If push is unsuccessful then the failure count is appended.
            failure++;
        }
    } // Altogether pushed floats are just numbers that are equal to index. push member 1 is equal to 1 for ease of testing the buffer.

    float popped_value; // Define a float.

    for(uint32_t i = 0; i < (success+1); i++){
        bool pop = buffer_pop(&popped_value); // Pop values stored on the buffer from the buffer
        
        if(pop == 1){ //if pop is successful
            if(popped_value == i){ //and the popped value is equal to the index of the member prints pass.
                //printf("PASS\n");
                //printf("the popped float value is: %f\n", popped_value); // Prints the popped value.
            }else{
                printf("FAIL- an unexpected pop value\n"); // if the popped value is not equal to its index then print FAIL.  
        }
        }else{
            if (i < success){ // success count represents accurately the value of members on the buffer.
                printf("FAIL- i is smaller than success count\n"); // Print failed if a POP operation failed. Meaning that all members were not popped from the buffer.
            }else if(i == success){ // If i is equal to success count that means that all the members of buffer were popped.
                printf("PASS- queue empty as expected\n");
            }
        }
    }
    printf("The success count is following: %lu\n", success);
    printf("The failure count is following: %lu\n", failure);
    printf("The overflow count is the following: %lu\n", buffer_overflow_count());


    float test_data[] = {0.0f, 2.0f, 4.0f};
    // TODO 1: get the element count WITHOUT hardcoding "3" — there's a classic
    // C idiom for this: sizeof(an_array) gives the array's total size in
    // bytes, sizeof(an_array[0]) gives one element's size in bytes, and
    // dividing the two gives you the element count, computed at compile
    // time. Same "derive it, don't hardcode it" habit as IterationsForP
    // back in Phase 3 — if you ever add a 4th test value, this keeps working
    // without you remembering to update a separate count by hand.
        uint32_t ArraySize = sizeof(test_data);
        uint32_t ElementSize = sizeof(test_data[0]);
        uint32_t count = (ArraySize/ElementSize); // Sizeof gives me the size of the array in bytes. Using sizeof on a member of the array gives me the size of the member.
    // TODO 2: call mean_f32 on test_data and your count, store the result.
        float Calc_Mean = mean_f32(test_data, count);
    // TODO 3: call variance_f32, passing test_data, the count, AND the
    // you just computed — remember variance_f32 doesn't compute its own
    // mean, it's handed one
        float Variance = variance_f32(test_data, count, Calc_Mean);
        printf("CHECKPOINT D, variance=%f\n", Variance);
    // TODO 4: call stddev_f32 on the variance you just computed
        float Stddev = stddev_f32(Variance);
        printf("CHECKPOINT E, stddev=%f\n", Stddev);
        // TODO 5: compare each of the three results against its expected va
        // (2, 4, 2) and print PASS/FAIL, same style as your buffer checkpoint.
        if (fabsf(Calc_Mean - 2) < EPSILON){
            // If value within error limits = PASS
            printf("Mean is correct and inside of allowed error and its value is: %f\n", Calc_Mean);
        } else {
        // FAIL
            printf("Mean is incorrect and not inside of allowed error, its value is %f\n", Calc_Mean);
        }
        if (fabsf(Variance - 4) < EPSILON){
            // If value within error limits = PASS
            printf("Variance is correct and inside of allowed error and its value is: %f\n", Variance);
        } else {
            // If value within error limits = PASS
            printf("Variance is incorrect and not inside of allowed error, its value is %f\n", Variance);
        }
        if (fabsf(Stddev - 2) < EPSILON){
            // If value within error limits = PASS
            printf("Standard deviation is correct and inside of allowed error and its value is: %f\n", Stddev);
        } else {
        // FAIL
            printf("Standard deviation is incorrect and not inside of allowed error, its value is %f\n", Stddev);
        }
            fflush(stdout); // Force USB buffer, to see what is printed beyond buffer logs.
    while (true) {
        //sampling_timing_test(); was conducted to verify that logging indeed happens 500 times per second.
        tight_loop_contents(); // Loop returns to waiting state.
    }
}