#include "pico/stdlib.h"
#include "sampling.h"
#include "buffer.h"
#include "stdio.h"
#define TEST_PUSH_COUNT 350

int main() {
    stdio_init_all();
    sleep_ms(2000);
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
                printf("PASS\n");
                printf("the popped float value is: %f\n", popped_value); // Prints the popped value.
            }else if(popped_value != i){
                printf("FAIL- an unexpected pop value\n"); // if the popped value is not equal to its index then print FAIL.
            }   
    }else if(i < success){ // success count represents accurately the value of members on the buffer.
        printf("FAIL- i is smaller than success count\n"); // Print failed if a POP operation failed. Meaning that all members were not popped from the buffer.
    }else if(i == success){ // If i is equal to success count that means that all the members of buffer were popped.
        printf("PASS- queue empty as expected\n");
    }
    }
    
    printf("The success count is following: %lu\n", success);
    printf("The failure count is following: %lu\n", failure);
    printf("The overflow count is the following: %lu\n", buffer_overflow_count());

    while (true) {
        tight_loop_contents();
        //sampling_timing_test(); was conducted to verify that logging indeed happens 500 times per second.
    }
}