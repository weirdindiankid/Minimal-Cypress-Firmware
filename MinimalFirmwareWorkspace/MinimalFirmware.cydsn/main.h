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
#include <project.h>
#include <stdlib.h>
#include "I2C.h"
#include "LED.h"
// Send this to the GAP central
typedef struct {     
    unsigned char LED_pattern;                     
    
    uint32_t sensor_10mm;                    
    unsigned char gain_10mm;					 
    unsigned char int_time_10mm;			       
    
    uint32_t sensor_20mm;    	             
    unsigned char gain_20mm;					 
    unsigned char int_time_20mm;
    
    uint32_t sensor_30mm;    	               
    unsigned char gain_30mm;					  
    unsigned char int_time_30mm;				   
    
    uint32_t sensor_40mm;    	               
    unsigned char gain_40mm;					   
    unsigned char int_time_40mm;	
    
    // IR Values
    uint32_t ir_10mm;                        
    uint32_t ir_20mm;                        
    uint32_t ir_30mm;                        
    uint32_t ir_40mm;                        
    
    int time; 								  
    float cell_voltage; 					  
    float state_of_charge; 					   
    unsigned short temp_skin;      	           
    unsigned short temp_amb;       	          
        
} Humon_data_struct;

/* [] END OF FILE */
