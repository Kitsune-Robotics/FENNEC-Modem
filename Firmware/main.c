#include <stdio.h>
#include "pico/stdlib.h"
#include "shift_register_display.h"

// Shift register pin configuration
#define DIN_PIN 18    // Data input pin
#define CLK_PIN 17    // Clock pin  
#define LATCH_PIN 16  // Latch pin

// Square wave generation pin
#define SQUARE_WAVE_PIN 2  // Could be any pin really

int main() {
    // Initialize stdio for USB output
    stdio_init_all();
    
    // Configure display pins
    display_config_t display_config = {
        .din_pin = DIN_PIN,
        .clk_pin = CLK_PIN,
        .latch_pin = LATCH_PIN
    };
    
    // Initialize the display
    if (display_init(&display_config) != 0) {
        printf("Failed to initialize display!\n");
        return -1;
    }

    // Initialize square wave pin
    gpio_init(SQUARE_WAVE_PIN);
    gpio_set_dir(SQUARE_WAVE_PIN, GPIO_OUT);
    gpio_put(SQUARE_WAVE_PIN, 0);

    // Boot animation on the 7-segment display
    display_boot_animation(100);
    
    // Clear the display after animation
    display_clear();
    
    // Critical frequencies for slow scan
    const uint32_t frequencies[] = {900, 1200, 2400, 2800, 2900, 3000};
    const uint32_t num_frequencies = sizeof(frequencies) / sizeof(frequencies[0]);
    uint32_t current_freq_index = 0;
    
    // Calculate initial half period for first frequency (900 Hz)
    uint32_t current_frequency = frequencies[current_freq_index];
    uint32_t half_period_us = 1000000 / (2 * current_frequency);  // microseconds
    
    printf("Starting with frequency: %d Hz (half period: %d us)\n", 
           current_frequency, half_period_us);
    
    absolute_time_t last_freq_change = get_absolute_time();
    uint32_t iteration = 0;
    
    while (true) {
        // Check if 10 seconds have passed to change frequency
        if (absolute_time_diff_us(last_freq_change, get_absolute_time()) >= 10000000) {
            current_freq_index = (current_freq_index + 1) % num_frequencies;
            current_frequency = frequencies[current_freq_index];
            half_period_us = 1000000 / (2 * current_frequency);
            last_freq_change = get_absolute_time();
            
            printf("Switching to frequency: %d Hz (half period: %d us)\n", 
                   current_frequency, half_period_us);
            display_set_digit(current_freq_index);
        }
        
        // Generate current frequency square wave
        gpio_put(SQUARE_WAVE_PIN, 1);
        sleep_us(half_period_us);
        gpio_put(SQUARE_WAVE_PIN, 0);
        sleep_us(half_period_us);
        
        // Toggle the decimal point every 1000 iterations 
        if (iteration % 1000 == 0) {
            display_toggle_decimal_point();
        }
        
        iteration++;
    }
    
    return 0;
}
