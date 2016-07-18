/* =================================================================
 * File: I2C.h
 * Authors: Dharmesh Tarapore
 * Description: Serves as the abstraction layer for I2C operations
 * =================================================================
*/

#include <project.h>

#ifndef I2C_H
    
#define I2C_H

typedef enum { false, true } bool;

// Enables us to write to a given slave address
// Must put everything in a buffer
// Returns true on success, false otherwise.
bool I2C_write(uint32 slave_address, uint8 cmd[], uint32 buffer_size);

#endif