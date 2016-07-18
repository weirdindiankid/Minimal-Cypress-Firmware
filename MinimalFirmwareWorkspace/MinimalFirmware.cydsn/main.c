/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "main.h"

// This will keep track of BLE connection status
bool ble_connected = false;

CYBLE_CONN_HANDLE_T connection_handle;

// We use this to handle common BLE events
void BLE_stack_handler( uint32 event_code, void *event_param ) {
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wr_req;
    // CYBLE_API_RESULT_T apiResult;
    // CYBLE_GAP_CONN_UPDATE_PARAM_T connUpdateParam;

    switch( event_code ) {
        case CYBLE_EVT_STACK_ON:
        
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
          CyBle_GappStartAdvertisement( CYBLE_ADVERTISING_FAST );
          ble_connected = false;
          break;
         case CYBLE_EVT_GATT_CONNECT_IND:  
          connection_handle = *(CYBLE_CONN_HANDLE_T *)event_param;
          ble_connected = true;
          break;
            
        // Used to send a write response back if we ever write to the device from 
        // a central device.
        case CYBLE_EVT_GATTS_WRITE_REQ:
          wr_req = (CYBLE_GATTS_WRITE_REQ_PARAM_T *)event_param;
          CyBle_GattsWriteAttributeValue( &wr_req->handleValPair, 0, &connection_handle, CYBLE_GATT_DB_LOCALLY_INITIATED);
          CyBle_GattsWriteRsp(connection_handle);
          break;
        
       
        case CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_RSP:
            // UART_PutString("L2CAP Update response received. \r\n");
            if(*(uint8 *)event_param == 0x00)
            {
                /* Connection parameter update request accepted by Master */

                // UART_PutString("Connection param accepted\r\n");
            
            }
            else if(*(uint8 *)event_param == 0x01)
            {
                /* Connection parameter update request rejected by Master */

                // UART_PutString("Connection param update req denied\r\n");
            }
            break;
        default:
          break;
    }
}


int main()
{
    
    // Enable interrupts
    CyGlobalIntEnable; 
    
    // Package everything into the Humon Struct
    Humon_data_struct ble;
    
    // Enable I2C
    I2CM_Start();
    
    // Enable BLE
    CyBle_Start(BLE_stack_handler);
    
    
    // Initialize LEDs
    LED_initialize();
    
    // LED Startup Sequence
    LED_RGB_set_brightness(RED_LED, 0x00);
    LED_RGB_set_brightness(GREEN_LED, 0x00);
    LED_RGB_set_brightness(BLUE_LED, 0x00);
    
    // Cycle through RGB LEDs to make sure everything is working
    LED_RGB_set_state(RED_LED, ON);
    CyDelay(500);
    LED_RGB_set_state(RED_LED, OFF);
        
    LED_RGB_set_state(GREEN_LED, ON);
    CyDelay(500);
    LED_RGB_set_state(GREEN_LED, OFF);
        
    LED_RGB_set_state(BLUE_LED, ON);
    CyDelay(500);
    LED_RGB_set_state(BLUE_LED, OFF);
    
    // Turn RED LED on to show that device is on
    LED_RGB_set_state(GREEN_LED, ON);
    
    
    // The handle value pair wraps values in a Cypress readable format
    // to help send data to BLE central devices
    // handle_value_pair expects the following data fields
    // CYBLE_GATT_VALUE_T  value 
    // CYBLE_GATT_DB_ATTR_HANDLE_T  attrHandle 
    // value contains
    //uint8 *  val: pointer to the value to be packed
    // uint16  len: length of the value to be packed
    // uint16  actualLen: <= len
    CYBLE_GATT_HANDLE_VALUE_PAIR_T humon_handle_value_pair;
    
    humon_handle_value_pair.value.val = (uint8 *)&ble;
    humon_handle_value_pair.attrHandle = CYBLE_HUMON_DATA_SERVICE_HUMON_DATA_CHARACTERISTIC_CHAR_HANDLE;
    humon_handle_value_pair.value.len = sizeof(ble);
    humon_handle_value_pair.value.actualLen = sizeof(ble);
    
    CYBLE_GATTS_HANDLE_VALUE_NTF_T humon_notif_pair;
    humon_notif_pair.attrHandle = humon_handle_value_pair.attrHandle;
    humon_notif_pair.value.val = humon_handle_value_pair.value.val;
    humon_notif_pair.value.len = humon_handle_value_pair.value.len;
    humon_notif_pair.value.actualLen = humon_handle_value_pair.value.actualLen;
   
    uint8_t led_p = 0;
    
    uint32_t ir_values[8] = {3214, 4254, 1415, 4178, 2101, 2335, 2336, 2545};
    uint32_t sensor_values[8] = {6532, 2100, 1834, 1787, 3212, 2121, 2003, 2654};
    
    
    for(;;)
    {
          if(POWER_BUTTON_IN_Read() == 0) {
            // Turn off LEDs
            POWER_HOLD_Write(0);
            break;
        }
        if(led_p != 2) {
            led_p++;
        } else {
            led_p = 0;
        }
        // Put everything in the humon struct
        ble.LED_pattern = led_p;
        ble.ir_10mm = ir_values[3];
        ble.ir_20mm = ir_values[3];
        ble.ir_30mm = ir_values[2];
        ble.ir_40mm = ir_values[1];;   
        ble.sensor_10mm = sensor_values[1];
        ble.sensor_20mm = sensor_values[6];
        ble.sensor_30mm = sensor_values[5];
        ble.sensor_40mm = sensor_values[3];
        ble.gain_10mm = 0;
        ble.int_time_10mm = 1;
        ble.gain_20mm = 1;
        ble.int_time_20mm = 0;
        ble.gain_30mm = 2;
        ble.int_time_30mm = 1;
        ble.gain_40mm = 3;
        ble.int_time_40mm = 2;
        ble.time = 3000; // Hardcoding until we find an equiv. to millis();
        ble.cell_voltage = 3.32;
        ble.state_of_charge = 1.23;
        // TODO: Send firmware version number instead of skin temp.
        ble.temp_skin = 23; // No temp. sensor-- Tmp.getTemp();
        ble.temp_amb = 33; // Hardcoding until we find an equiv. to RFduino_temperature(CELSIUS);
       
        // This will tell us how the write went
        CYBLE_GATT_ERR_CODE_T ble_error_code;
        
        // Now write these values to the GATT DB
        ble_error_code = CyBle_GattsWriteAttributeValue(&humon_handle_value_pair, 0, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
        
        if(ble_error_code == CYBLE_GATT_ERR_NONE) {
            // UART_PutString("No error writing GATT server attribute value.\r\n");
        } 
        else if(ble_error_code == CYBLE_GATT_ERR_INVALID_HANDLE ) {
            // UART_PutString("Invalid handle.\r\n");
        } 
        else if(ble_error_code == CYBLE_GATT_ERR_WRITE_NOT_PERMITTED ) {
            // UART_PutString("Write not permitted.\r\n");
        } 
        else if(ble_error_code == CYBLE_GATT_ERR_INVALID_OFFSET ) {
            // UART_PutString("Invalid offset.\r\n");
        } 
        else if (ble_error_code == CYBLE_GATT_ERR_UNLIKELY_ERROR ) {
            // UART_PutString("Unlikely error.\r\n");
        }
        
        // Notify device that the values have changed if we have an active connection
        if(ble_connected == true) {
            CyBle_GattsNotification(cyBle_connHandle, &humon_notif_pair); 
        }
        
        // Process BLE events
        CyBle_ProcessEvents();
        
        CyDelay(200);
        
    }
    // Silences warnings. Should never return.
    return 0;
}

/* [] END OF FILE */
