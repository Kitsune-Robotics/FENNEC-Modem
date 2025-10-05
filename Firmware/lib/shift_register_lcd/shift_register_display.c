#include "shift_register_display.h"
#include <stdio.h>

// 7-segment display patterns for digits 0-9
// Each bit represents a segment: gfedcba (MSB to LSB)
const uint8_t DIGIT_PATTERNS[10] = {
    0b00111111,  // 0: (segments a,b,c,d,e,f)
    0b00000110,  // 1: (segments b,c)
    0b01011011,  // 2: (segments a,b,g,e,d)
    0b01001111,  // 3: (segments a,b,g,c,d)
    0b01100110,  // 4: (segments f,g,b,c)
    0b01101101,  // 5: (segments a,f,g,c,d)
    0b01111101,  // 6: (segments a,f,g,e,d,c)
    0b00000111,  // 7: (segments a,b,c)
    0b01111111,  // 8: (all segments)
    0b01101111   // 9: (segments a,b,c,d,f,g)
};

// Global display state
static display_state_t g_display_state = {0};

// Private helper functions
static void shift_out_byte(uint8_t data);
static void latch_data(void);

static void shift_out_byte(uint8_t data) {
    // Send 8 bits MSB first
    for (int i = 7; i >= 0; i--) {
        // Set data bit
        gpio_put(g_display_state.config.din_pin, (data >> i) & 1);
        
        // Clock pulse
        gpio_put(g_display_state.config.clk_pin, 1);
        sleep_us(1);  // Small delay for setup time
        gpio_put(g_display_state.config.clk_pin, 0);
        sleep_us(1);  // Small delay for hold time
    }
}

static void latch_data(void) {
    // Latch the data to the output
    gpio_put(g_display_state.config.latch_pin, 1);
    sleep_us(1);  // Small delay for latch pulse width
    gpio_put(g_display_state.config.latch_pin, 0);
}

int display_init(const display_config_t *config) {
    if (!config) {
        return -1;
    }
    
    // Store configuration
    g_display_state.config = *config;
    
    // Initialize GPIO pins
    gpio_init(g_display_state.config.din_pin);
    gpio_init(g_display_state.config.clk_pin);
    gpio_init(g_display_state.config.latch_pin);
    
    gpio_set_dir(g_display_state.config.din_pin, GPIO_OUT);
    gpio_set_dir(g_display_state.config.clk_pin, GPIO_OUT);
    gpio_set_dir(g_display_state.config.latch_pin, GPIO_OUT);
    
    // Initialize pins to low
    gpio_put(g_display_state.config.din_pin, 0);
    gpio_put(g_display_state.config.clk_pin, 0);
    gpio_put(g_display_state.config.latch_pin, 0);
    
    // Initialize state
    g_display_state.current_digit = 0;
    g_display_state.decimal_point = false;
    g_display_state.display_enabled = false;
    
    return 0;
}

int display_set_digit(uint8_t digit) {
    if (digit > 9) {
        return -1;  // Invalid digit
    }
    
    g_display_state.current_digit = digit;
    g_display_state.display_enabled = true;
    
    // Get the pattern for this digit
    uint8_t pattern = DIGIT_PATTERNS[digit];
    
    // Add decimal point if enabled
    if (g_display_state.decimal_point) {
        pattern |= 0b10000000;  // Set bit 7 for decimal point
    }
    
    // Send to shift register
    shift_out_byte(pattern);
    latch_data();
    
    return 0;
}

void display_clear(void) {
    g_display_state.display_enabled = false;
    
    // Send all zeros to turn off display
    shift_out_byte(0x00);
    latch_data();
}

void display_set_decimal_point(bool enable) {
    g_display_state.decimal_point = enable;
    
    // Always send the decimal point state to the shift register
    uint8_t pattern = 0b00000000;  // Start with all segments off
    
    // If display is currently showing a digit, include that pattern
    if (g_display_state.display_enabled) {
        pattern = DIGIT_PATTERNS[g_display_state.current_digit];
    }
    
    // Add decimal point if enabled
    if (g_display_state.decimal_point) {
        pattern |= 0b10000000;  // Set bit 7 for decimal point
    }
    
    // Send to shift register
    shift_out_byte(pattern);
    latch_data();
}

void display_toggle_decimal_point(void) {
    display_set_decimal_point(!g_display_state.decimal_point);
}

uint8_t display_get_current_digit(void) {
    if (g_display_state.display_enabled) {
        return g_display_state.current_digit;
    }
    return 255;  // Indicate display is off
}

bool display_is_decimal_point_on(void) {
    return g_display_state.decimal_point;
}

bool display_is_enabled(void) {
    return g_display_state.display_enabled;
}

void display_boot_animation(uint32_t delay_ms) {
    // Boot animation pattern: f, a, b, c, d, e
    const uint8_t animation_patterns[] = {
        0b00100000,  // segment f
        0b00000001,  // segment a  
        0b00000010,  // segment b
        0b00000100,  // segment c
        0b00001000,  // segment d
        0b00010000,  // segment e
        0b00111111   // all
    };
    
    // Clear display
    shift_out_byte(0x00);
    latch_data();
    sleep_ms(100);
    
    // Animate
    for (int i = 0; i < 7; i++) {
        // Send the pattern to shift register
        shift_out_byte(animation_patterns[i]);
        latch_data();
        
        // Wait for the specified delay
        sleep_ms(delay_ms);
    }
    
    // Brief pause with all segments on
    sleep_ms(delay_ms * 2);
    
    // Clear display
    shift_out_byte(0x00);
    latch_data();
}
