/*******************************************************************************
* File Name: START_BUTTON_IN.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_START_BUTTON_IN_ALIASES_H) /* Pins START_BUTTON_IN_ALIASES_H */
#define CY_PINS_START_BUTTON_IN_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define START_BUTTON_IN_0			(START_BUTTON_IN__0__PC)
#define START_BUTTON_IN_0_PS		(START_BUTTON_IN__0__PS)
#define START_BUTTON_IN_0_PC		(START_BUTTON_IN__0__PC)
#define START_BUTTON_IN_0_DR		(START_BUTTON_IN__0__DR)
#define START_BUTTON_IN_0_SHIFT	(START_BUTTON_IN__0__SHIFT)
#define START_BUTTON_IN_0_INTR	((uint16)((uint16)0x0003u << (START_BUTTON_IN__0__SHIFT*2u)))

#define START_BUTTON_IN_INTR_ALL	 ((uint16)(START_BUTTON_IN_0_INTR))


#endif /* End Pins START_BUTTON_IN_ALIASES_H */


/* [] END OF FILE */
