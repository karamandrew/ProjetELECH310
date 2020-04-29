/*******************************************************************************
* File Name: photoSensor.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_photoSensor_H) /* Pins photoSensor_H */
#define CY_PINS_photoSensor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "photoSensor_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 photoSensor__PORT == 15 && ((photoSensor__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    photoSensor_Write(uint8 value);
void    photoSensor_SetDriveMode(uint8 mode);
uint8   photoSensor_ReadDataReg(void);
uint8   photoSensor_Read(void);
void    photoSensor_SetInterruptMode(uint16 position, uint16 mode);
uint8   photoSensor_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the photoSensor_SetDriveMode() function.
     *  @{
     */
        #define photoSensor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define photoSensor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define photoSensor_DM_RES_UP          PIN_DM_RES_UP
        #define photoSensor_DM_RES_DWN         PIN_DM_RES_DWN
        #define photoSensor_DM_OD_LO           PIN_DM_OD_LO
        #define photoSensor_DM_OD_HI           PIN_DM_OD_HI
        #define photoSensor_DM_STRONG          PIN_DM_STRONG
        #define photoSensor_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define photoSensor_MASK               photoSensor__MASK
#define photoSensor_SHIFT              photoSensor__SHIFT
#define photoSensor_WIDTH              1u

/* Interrupt constants */
#if defined(photoSensor__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in photoSensor_SetInterruptMode() function.
     *  @{
     */
        #define photoSensor_INTR_NONE      (uint16)(0x0000u)
        #define photoSensor_INTR_RISING    (uint16)(0x0001u)
        #define photoSensor_INTR_FALLING   (uint16)(0x0002u)
        #define photoSensor_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define photoSensor_INTR_MASK      (0x01u) 
#endif /* (photoSensor__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define photoSensor_PS                     (* (reg8 *) photoSensor__PS)
/* Data Register */
#define photoSensor_DR                     (* (reg8 *) photoSensor__DR)
/* Port Number */
#define photoSensor_PRT_NUM                (* (reg8 *) photoSensor__PRT) 
/* Connect to Analog Globals */                                                  
#define photoSensor_AG                     (* (reg8 *) photoSensor__AG)                       
/* Analog MUX bux enable */
#define photoSensor_AMUX                   (* (reg8 *) photoSensor__AMUX) 
/* Bidirectional Enable */                                                        
#define photoSensor_BIE                    (* (reg8 *) photoSensor__BIE)
/* Bit-mask for Aliased Register Access */
#define photoSensor_BIT_MASK               (* (reg8 *) photoSensor__BIT_MASK)
/* Bypass Enable */
#define photoSensor_BYP                    (* (reg8 *) photoSensor__BYP)
/* Port wide control signals */                                                   
#define photoSensor_CTL                    (* (reg8 *) photoSensor__CTL)
/* Drive Modes */
#define photoSensor_DM0                    (* (reg8 *) photoSensor__DM0) 
#define photoSensor_DM1                    (* (reg8 *) photoSensor__DM1)
#define photoSensor_DM2                    (* (reg8 *) photoSensor__DM2) 
/* Input Buffer Disable Override */
#define photoSensor_INP_DIS                (* (reg8 *) photoSensor__INP_DIS)
/* LCD Common or Segment Drive */
#define photoSensor_LCD_COM_SEG            (* (reg8 *) photoSensor__LCD_COM_SEG)
/* Enable Segment LCD */
#define photoSensor_LCD_EN                 (* (reg8 *) photoSensor__LCD_EN)
/* Slew Rate Control */
#define photoSensor_SLW                    (* (reg8 *) photoSensor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define photoSensor_PRTDSI__CAPS_SEL       (* (reg8 *) photoSensor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define photoSensor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) photoSensor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define photoSensor_PRTDSI__OE_SEL0        (* (reg8 *) photoSensor__PRTDSI__OE_SEL0) 
#define photoSensor_PRTDSI__OE_SEL1        (* (reg8 *) photoSensor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define photoSensor_PRTDSI__OUT_SEL0       (* (reg8 *) photoSensor__PRTDSI__OUT_SEL0) 
#define photoSensor_PRTDSI__OUT_SEL1       (* (reg8 *) photoSensor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define photoSensor_PRTDSI__SYNC_OUT       (* (reg8 *) photoSensor__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(photoSensor__SIO_CFG)
    #define photoSensor_SIO_HYST_EN        (* (reg8 *) photoSensor__SIO_HYST_EN)
    #define photoSensor_SIO_REG_HIFREQ     (* (reg8 *) photoSensor__SIO_REG_HIFREQ)
    #define photoSensor_SIO_CFG            (* (reg8 *) photoSensor__SIO_CFG)
    #define photoSensor_SIO_DIFF           (* (reg8 *) photoSensor__SIO_DIFF)
#endif /* (photoSensor__SIO_CFG) */

/* Interrupt Registers */
#if defined(photoSensor__INTSTAT)
    #define photoSensor_INTSTAT            (* (reg8 *) photoSensor__INTSTAT)
    #define photoSensor_SNAP               (* (reg8 *) photoSensor__SNAP)
    
	#define photoSensor_0_INTTYPE_REG 		(* (reg8 *) photoSensor__0__INTTYPE)
#endif /* (photoSensor__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_photoSensor_H */


/* [] END OF FILE */
