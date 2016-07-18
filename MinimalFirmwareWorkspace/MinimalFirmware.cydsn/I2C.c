/* ========================================
 *
 * Copyright Humon, 2016
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Humon.
 *
 * Author: Dharmesh Tarapore
 * Purpose: Serves as an abstraction layer for all
 *          I2C operations.
 * ========================================
*/

#include <I2C.h>

bool I2C_write(uint32 slave_address, uint8 cmd[], uint32 buffer_size) {
    // Clear Master Status
    I2CM_I2CMasterClearStatus(); 
    I2CM_I2CMasterWriteBuf(slave_address, cmd, buffer_size, I2CM_I2C_MODE_COMPLETE_XFER);
    
    // Wait until master completes write transfer
    while (0u == (I2CM_I2CMasterStatus() & I2CM_I2C_MSTAT_WR_CMPLT)) {
    }
    
     // If we observe no status errors 
    if (0u == (I2CM_I2C_MSTAT_ERR_XFER & I2CM_I2CMasterStatus()))  //no status errors
    {
        /* Check if all bytes was written */
        if (I2CM_I2CMasterGetWriteBufSize() == buffer_size)
        {
            return true;
        }
    }
    // If all the bytes were not written, we assume the write failed
    return false;
}

/* [] END OF FILE */