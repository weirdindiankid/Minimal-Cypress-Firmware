/* ========================================
 *
 * Copyright Humon, 2015
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 * Author: Dharmesh Tarapore
 * Description: This is the header file for the LED segment
 * ========================================
*/

#ifndef LED_H
#define LED_H
    
#include "I2C.h"

// Slave address definition -- change here DO NOT use magic numbers please
#define LED_SLAVE_ADDRESS (0x44u)
#define NUMBER_OF_LEDS 2

// No magic numbers in the code
#define ON 0x01
#define OFF 0x00
    
#define LED1_NAME  "660nm"
#define LED2_NAME  "855nm"

// Using these for "sensor" LEDs (Table 5, P. 13)
#define P12_REG   0x2C // Port 12: LED1A
#define P13_REG   0x2D // Port 13: LED1B
#define P14_REG   0x2E // Port 14: LED2A
#define P15_REG   0x2F // Port 15: LED2B
#define P18_REG   0x32 // Port 18: RED
#define P19_REG   0x33 // Port 19: GREEN
#define P20_REG   0x34 // Port 20: BLUE
    
// Using these for "sensor" LEDs (current registers)
// Even pins get 0x0Y where Y is desired current
// Odd pin get 0xY0 where Y is desired current
// See Tables 12, 13, and 14 
#define P12_CURR_REG   0x16 // Port 12: LED1A
#define P13_CURR_REG   0x16 // Port 13: LED1B
#define P14_CURR_REG   0x17 // Port 14: LED2A
#define P15_CURR_REG   0x17 // Port 15: LED2B
#define P18_CURR_REG   0x19 // Port 18: RED
#define P19_CURR_REG   0x19 // Port 19: GREEN
#define P20_CURR_REG   0x1A // Port 20: BLUE


// LED numbers
#define RED_LED     0
#define GREEN_LED   1
#define BLUE_LED    2
    
// LED Names
#define RED_LED_NAME  "red"
#define GREEN_LED_NAME  "green"
#define BLUE_LED_NAME  "blue"
    
// To check device charging status
#define BATTERY_STAT_PORT  0x3F

typedef enum {
  LED1  = 0,
  LED2  = 1,
  LAST_LED = LED2,
} Port_num;

typedef struct {
    uint8 led_num;
    uint8 led_num_pair;
    char *led_name;
    uint8 part_number;
    uint8 port_num;
    uint8 led_reg;
    uint8 led_reg1;
    uint8 current_reg;
    uint8 current_digit;
    uint8 brightness;
    bool led_state;
    uint16 on_time;
} Led;

Led led_array[NUMBER_OF_LEDS];
Led RGB_led_array[3];

uint8  led_pattern;

/* LED Functions */

// Helps initialize the LED driver
void LED_initialize();
bool LED_init_params(void);

// Sets LED brightness
void LED_set_brightness(uint8 led_num, uint8 brightness);
// Control RGB LED brightness 
void LED_RGB_set_brightness(uint8 led_num, uint8 brightness);

// Set LED state
void LED_set_state(uint8 led_num, uint8 led_state);
// Sets the state of the RGB LED
void LED_RGB_set_state(uint8 led_num, uint8 led_state);

// Get current LED Pattern
uint8 LED_get_current_pattern(void);

// Toggle LEDs
void LED_toggle_and_dark(void);

// Turn off all LEDs
void LED_all_off( void );

#endif
/* [] END OF FILE */
