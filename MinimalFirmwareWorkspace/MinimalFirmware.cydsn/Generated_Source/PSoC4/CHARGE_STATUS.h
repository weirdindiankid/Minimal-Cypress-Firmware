/*******************************************************************************
* File Name: CHARGE_STATUS.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_CHARGE_STATUS_H) /* Pins CHARGE_STATUS_H */
#define CY_PINS_CHARGE_STATUS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CHARGE_STATUS_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} CHARGE_STATUS_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   CHARGE_STATUS_Read(void);
void    CHARGE_STATUS_Write(uint8 value);
uint8   CHARGE_STATUS_ReadDataReg(void);
#if defined(CHARGE_STATUS__PC) || (CY_PSOC4_4200L) 
    void    CHARGE_STATUS_SetDriveMode(uint8 mode);
#endif
void    CHARGE_STATUS_SetInterruptMode(uint16 position, uint16 mode);
uint8   CHARGE_STATUS_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void CHARGE_STATUS_Sleep(void); 
void CHARGE_STATUS_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(CHARGE_STATUS__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define CHARGE_STATUS_DRIVE_MODE_BITS        (3)
    #define CHARGE_STATUS_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - CHARGE_STATUS_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the CHARGE_STATUS_SetDriveMode() function.
         *  @{
         */
        #define CHARGE_STATUS_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define CHARGE_STATUS_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define CHARGE_STATUS_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define CHARGE_STATUS_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define CHARGE_STATUS_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define CHARGE_STATUS_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define CHARGE_STATUS_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define CHARGE_STATUS_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define CHARGE_STATUS_MASK               CHARGE_STATUS__MASK
#define CHARGE_STATUS_SHIFT              CHARGE_STATUS__SHIFT
#define CHARGE_STATUS_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CHARGE_STATUS_SetInterruptMode() function.
     *  @{
     */
        #define CHARGE_STATUS_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define CHARGE_STATUS_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define CHARGE_STATUS_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define CHARGE_STATUS_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(CHARGE_STATUS__SIO)
    #define CHARGE_STATUS_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(CHARGE_STATUS__PC) && (CY_PSOC4_4200L)
    #define CHARGE_STATUS_USBIO_ENABLE               ((uint32)0x80000000u)
    #define CHARGE_STATUS_USBIO_DISABLE              ((uint32)(~CHARGE_STATUS_USBIO_ENABLE))
    #define CHARGE_STATUS_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define CHARGE_STATUS_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define CHARGE_STATUS_USBIO_ENTER_SLEEP          ((uint32)((1u << CHARGE_STATUS_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << CHARGE_STATUS_USBIO_SUSPEND_DEL_SHIFT)))
    #define CHARGE_STATUS_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << CHARGE_STATUS_USBIO_SUSPEND_SHIFT)))
    #define CHARGE_STATUS_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << CHARGE_STATUS_USBIO_SUSPEND_DEL_SHIFT)))
    #define CHARGE_STATUS_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(CHARGE_STATUS__PC)
    /* Port Configuration */
    #define CHARGE_STATUS_PC                 (* (reg32 *) CHARGE_STATUS__PC)
#endif
/* Pin State */
#define CHARGE_STATUS_PS                     (* (reg32 *) CHARGE_STATUS__PS)
/* Data Register */
#define CHARGE_STATUS_DR                     (* (reg32 *) CHARGE_STATUS__DR)
/* Input Buffer Disable Override */
#define CHARGE_STATUS_INP_DIS                (* (reg32 *) CHARGE_STATUS__PC2)

/* Interrupt configuration Registers */
#define CHARGE_STATUS_INTCFG                 (* (reg32 *) CHARGE_STATUS__INTCFG)
#define CHARGE_STATUS_INTSTAT                (* (reg32 *) CHARGE_STATUS__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define CHARGE_STATUS_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(CHARGE_STATUS__SIO)
    #define CHARGE_STATUS_SIO_REG            (* (reg32 *) CHARGE_STATUS__SIO)
#endif /* (CHARGE_STATUS__SIO_CFG) */

/* USBIO registers */
#if !defined(CHARGE_STATUS__PC) && (CY_PSOC4_4200L)
    #define CHARGE_STATUS_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define CHARGE_STATUS_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define CHARGE_STATUS_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define CHARGE_STATUS_DRIVE_MODE_SHIFT       (0x00u)
#define CHARGE_STATUS_DRIVE_MODE_MASK        (0x07u << CHARGE_STATUS_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins CHARGE_STATUS_H */


/* [] END OF FILE */
