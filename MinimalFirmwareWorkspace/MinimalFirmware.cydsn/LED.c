/* ========================================
 *
 * Copyright Humon, 2016
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Humon.
 *
 * ========================================
*/
#include <LED.h>

// This function initializes the LED driver
void LED_initialize() {
    uint8 sbuf[2];
    sbuf[0] = 0x04;
    sbuf[1] = 0x41;
    //M = 0: No transition detection, I = 1: individual currents, S = 1: shutdown mode off
   
    I2C_write(LED_SLAVE_ADDRESS, sbuf, 2);

    uint8 wbuf[8];
    wbuf[0] = 0x09; // Select portd 12 - 15
    wbuf[1] = 0x55; // Set ports 4 - 7, not connected, set as G{OP output to save power and autoinc
    wbuf[2] = 0x55; // Set ports 8 - 11, not connected, set as G{OP output to save power and autoinc
    wbuf[3] = 0x00; // Set ports 12 - 15 as LED drivers and auto-increment (next 4 bytes: set P12-P27 as open drain) 
    wbuf[4] = 0x00; // Set ports 16 - 19 as LED drivers and auto-increment
    wbuf[5] = 0x00; // Set ports 20 - 23 as LED drivers and auto-increment
    wbuf[6] = 0x00; // Set ports 24 - 27 as LED drivers and auto-increment
    wbuf[7] = 0xFF; // Set ports 28 - 31 as LED drivers and auto-increment (as input with pullup)

    I2C_write(LED_SLAVE_ADDRESS, wbuf, 8);
    
    int ctr = 0;
    // Turn LEDs off
    for(ctr = 0; ctr < 13; ctr++) {
        uint8 onBuf[2];
        onBuf[0] = P12_REG + ctr;   //address of individual output pins
        onBuf[1] = OFF; 
        // only D0 bit is used, other bits are ignored: 1=on, 0=off
        I2C_write(LED_SLAVE_ADDRESS, onBuf, 2);
    }
    
    // Set individual current registers for LEDs (Table 11, Table 12): ALL DIM
    int i = 0;
    // TODO: Take a look at datasheet to figure out what is going on
    // Change to i = 0 and i < 13
    // Used to be i = 1 and i < 14
    for (i = 0; i < 13; i++) {
        uint8 currentBuf[2];
        currentBuf[0] = 0x12 + i;
        currentBuf[1] = 0x00;
        I2C_write(LED_SLAVE_ADDRESS, currentBuf, 2);
    } 
    // Initialize LED Parameters
    LED_init_params();
    led_pattern = 0;
}

// Set LED Brightness
void LED_set_brightness(uint8 led_num, uint8 brightness) {
    led_array[led_num].brightness = brightness;
    uint8 cmd[2];
    cmd[0] = led_array[led_num].current_reg;
    cmd[1] = brightness;
    I2C_write(LED_SLAVE_ADDRESS, cmd, 2);
}

// Set RGB LED brightness
void LED_RGB_set_brightness(uint8 led_num, uint8 brightness) {
    uint8 led_num_pair = RGB_led_array[led_num].led_num_pair;
    uint8 brightness_hex;
    uint8 led_current_digit;
  
    if(led_num_pair == 0){
        led_current_digit = RGB_led_array[led_num].current_digit;
        brightness_hex = led_current_digit * brightness;
        RGB_led_array[led_num].brightness = brightness_hex;
    } else {
        led_current_digit = RGB_led_array[led_num].current_digit;
        brightness_hex = led_current_digit * brightness + RGB_led_array[led_num_pair].brightness;
        RGB_led_array[led_num].brightness = brightness_hex;
    }
    uint8 cmd[2];
    cmd[0] = RGB_led_array[led_num].current_reg;
    cmd[1] = brightness_hex;
    
    I2C_write(LED_SLAVE_ADDRESS, cmd, 2);
}

// Set the state of the RGB LEDs
void LED_RGB_set_state(uint8 led_num, uint8 led_state) {
    uint8 cmd[2];
    cmd[0] = RGB_led_array[led_num].led_reg;
    cmd[1] = led_state;
    I2C_write(LED_SLAVE_ADDRESS, cmd, 2);
    RGB_led_array[led_num].led_state = led_state;
}

// Get the current LED pattern
uint8 LED_get_current_pattern() {
  return led_pattern;
}

// Toggle LEDs
void LED_toggle_and_dark(void) {
    if (led_pattern == 0) {
        LED_set_state(LED1, ON);
        LED_set_state(LED2, OFF);
        
        led_pattern = 1;
    } else if (led_pattern == 1) {
        LED_set_state(LED1, OFF);
        LED_set_state(LED2, ON);
        
        led_pattern = 2;
      } else {
        LED_set_state(LED1, OFF);
        LED_set_state(LED2, OFF);
        
        led_pattern = 0;
      }
}

// Sets LED state
/*
* NB: We set the state twice because there are two pins that are
* "jumpered". In the cmd buffer, that we are writing to the LED slave
* address using I2C, we do not use the next address because the LED
* driver auto-increments this address.
*/
void LED_set_state(uint8 led_num, uint8 led_state) {
    uint8 cmd[3];
    cmd[0] = led_array[led_num].led_reg;
    cmd[1] = led_state;
    cmd[2] = led_state;
    
    I2C_write(LED_SLAVE_ADDRESS, cmd, 3);
    led_array[led_num].led_state = led_state;
}

// Setup Addresses
// Initialize all LEDs
bool LED_init_params( void ) {
  // LED1
  led_array[LED1].led_num = LED1;
  led_array[LED1].led_name = LED1_NAME;
  led_array[LED1].port_num = 14;
  led_array[LED1].led_reg = P14_REG;
  led_array[LED1].current_reg = P14_CURR_REG;
  led_array[LED1].current_digit = 0x11;
  led_array[LED1].brightness = 0x00;
  led_array[LED1].led_state = OFF;
  led_array[LED1].on_time = 100;

  // LED2
  led_array[LED2].led_num = LED2;
  led_array[LED2].led_name = LED2_NAME;
  led_array[LED2].port_num = 12;
  led_array[LED2].led_reg = P12_REG;
  led_array[LED2].current_reg = P12_CURR_REG;
  led_array[LED2].current_digit = 0x11;
  led_array[LED2].brightness = 0x00;
  led_array[LED2].led_state = OFF;
  led_array[LED2].on_time = 100;

  // Red LED
  RGB_led_array[RED_LED].led_num = RED_LED;
  RGB_led_array[RED_LED].led_num_pair = 0;
  RGB_led_array[RED_LED].led_name = RED_LED_NAME;
  RGB_led_array[RED_LED].port_num = 18;
  RGB_led_array[RED_LED].led_reg = P18_REG;
  RGB_led_array[RED_LED].current_reg = P18_CURR_REG;
  RGB_led_array[RED_LED].current_digit = 0x01;
  RGB_led_array[RED_LED].brightness = 0x00;
  RGB_led_array[RED_LED].led_state = OFF;
  RGB_led_array[RED_LED].on_time = 100;

  // Green LED
  RGB_led_array[GREEN_LED].led_num = GREEN_LED;
  RGB_led_array[GREEN_LED].led_num_pair = BLUE_LED;
  RGB_led_array[GREEN_LED].led_name = GREEN_LED_NAME;
  RGB_led_array[GREEN_LED].port_num = 19;
  RGB_led_array[GREEN_LED].led_reg = P19_REG;
  RGB_led_array[GREEN_LED].current_reg = P19_CURR_REG;
  RGB_led_array[GREEN_LED].current_digit = 0x10;
  RGB_led_array[GREEN_LED].brightness = 0x00;
  RGB_led_array[GREEN_LED].led_state = OFF;
  RGB_led_array[GREEN_LED].on_time = 100;

  // Blue LED
  RGB_led_array[BLUE_LED].led_num = BLUE_LED;
  RGB_led_array[BLUE_LED].led_num_pair = GREEN_LED;
  RGB_led_array[BLUE_LED].led_name = GREEN_LED_NAME;
  RGB_led_array[BLUE_LED].port_num = 20;
  RGB_led_array[BLUE_LED].led_reg = P20_REG;
  RGB_led_array[BLUE_LED].current_reg = P20_CURR_REG;
  RGB_led_array[BLUE_LED].current_digit = 0x01;
  RGB_led_array[BLUE_LED].brightness = 0x00;
  RGB_led_array[BLUE_LED].led_state = OFF;
  RGB_led_array[BLUE_LED].on_time = 100;

  return true;
};

void LED_all_off( void ) {
    LED_RGB_set_state(RED_LED, OFF);
    LED_RGB_set_state(GREEN_LED, OFF);
    LED_RGB_set_state(BLUE_LED, OFF);
    LED_set_state(LED1, OFF);
    LED_set_state(LED2, OFF);
}

/* [] END OF FILE */
