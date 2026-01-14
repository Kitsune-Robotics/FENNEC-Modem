#ifndef SHIFT_REGISTER_DISPLAY_H
#define SHIFT_REGISTER_DISPLAY_H

#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Display configuration structure
typedef struct {
    uint8_t din_pin;
    uint8_t clk_pin;
    uint8_t latch_pin;
} display_config_t;

// Display state structure
typedef struct {
    display_config_t config;
    uint8_t current_digit;
    bool decimal_point;
    bool display_enabled;
} display_state_t;

// Function prototypes

/**
 * @brief Initialize the shift register display with pin configuration
 * @param config Pointer to display configuration structure
 * @return 0 on success, -1 on error
 */
int display_init(const display_config_t *config);

/**
 * @brief Set a specific digit (0-9) on the display
 * @param digit Digit to display (0-9)
 * @return 0 on success, -1 on invalid digit
 */
int display_set_digit(uint8_t digit);

/**
 * @brief Clear/turn off the display
 */
void display_clear(void);

/**
 * @brief Enable or disable the decimal point
 * @param enable true to enable decimal point, false to disable
 */
void display_set_decimal_point(bool enable);

/**
 * @brief Toggle the decimal point on/off
 */
void display_toggle_decimal_point(void);

/**
 * @brief Get the current digit being displayed
 * @return Current digit (0-9) or 255 if display is off
 */
uint8_t display_get_current_digit(void);

/**
 * @brief Check if decimal point is currently enabled
 * @return true if decimal point is on, false if off
 */
bool display_is_decimal_point_on(void);

/**
 * @brief Check if display is currently enabled
 * @return true if display is on, false if off
 */
bool display_is_enabled(void);

/**
 * @brief Simple lil boot animation ^.^
 * @param delay_ms Speed/delay between digits
 */
void display_boot_animation(uint32_t delay_ms);

// Constants for 7-segment patterns
extern const uint8_t DIGIT_PATTERNS[10];

#endif // SHIFT_REGISTER_DISPLAY_H
