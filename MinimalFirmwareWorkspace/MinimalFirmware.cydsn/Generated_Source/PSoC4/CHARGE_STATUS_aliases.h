/*******************************************************************************
* File Name: CHARGE_STATUS.h  
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

#if !defined(CY_PINS_CHARGE_STATUS_ALIASES_H) /* Pins CHARGE_STATUS_ALIASES_H */
#define CY_PINS_CHARGE_STATUS_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define CHARGE_STATUS_0			(CHARGE_STATUS__0__PC)
#define CHARGE_STATUS_0_PS		(CHARGE_STATUS__0__PS)
#define CHARGE_STATUS_0_PC		(CHARGE_STATUS__0__PC)
#define CHARGE_STATUS_0_DR		(CHARGE_STATUS__0__DR)
#define CHARGE_STATUS_0_SHIFT	(CHARGE_STATUS__0__SHIFT)
#define CHARGE_STATUS_0_INTR	((uint16)((uint16)0x0003u << (CHARGE_STATUS__0__SHIFT*2u)))

#define CHARGE_STATUS_INTR_ALL	 ((uint16)(CHARGE_STATUS_0_INTR))


#endif /* End Pins CHARGE_STATUS_ALIASES_H */


/* [] END OF FILE */
