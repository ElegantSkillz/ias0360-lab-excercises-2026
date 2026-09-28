#include "pico/stdlib.h"
#include "sampling.h"

int main() {
    stdio_init_all();
    sleep_ms(2000);
    while (true) {
        tight_loop_contents();
        sampling_timing_test();
    }
}