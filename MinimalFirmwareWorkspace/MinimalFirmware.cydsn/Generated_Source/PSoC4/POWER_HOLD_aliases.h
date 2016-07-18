/*******************************************************************************
* File Name: POWER_HOLD.h  
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

#if !defined(CY_PINS_POWER_HOLD_ALIASES_H) /* Pins POWER_HOLD_ALIASES_H */
#define CY_PINS_POWER_HOLD_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define POWER_HOLD_0			(POWER_HOLD__0__PC)
#define POWER_HOLD_0_PS		(POWER_HOLD__0__PS)
#define POWER_HOLD_0_PC		(POWER_HOLD__0__PC)
#define POWER_HOLD_0_DR		(POWER_HOLD__0__DR)
#define POWER_HOLD_0_SHIFT	(POWER_HOLD__0__SHIFT)
#define POWER_HOLD_0_INTR	((uint16)((uint16)0x0003u << (POWER_HOLD__0__SHIFT*2u)))

#define POWER_HOLD_INTR_ALL	 ((uint16)(POWER_HOLD_0_INTR))


#endif /* End Pins POWER_HOLD_ALIASES_H */


/* [] END OF FILE */
