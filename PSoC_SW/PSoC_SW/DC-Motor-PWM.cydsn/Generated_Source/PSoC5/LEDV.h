/*******************************************************************************
* File Name: LEDV.h  
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

#if !defined(CY_PINS_LEDV_H) /* Pins LEDV_H */
#define CY_PINS_LEDV_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LEDV_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LEDV__PORT == 15 && ((LEDV__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LEDV_Write(uint8 value);
void    LEDV_SetDriveMode(uint8 mode);
uint8   LEDV_ReadDataReg(void);
uint8   LEDV_Read(void);
void    LEDV_SetInterruptMode(uint16 position, uint16 mode);
uint8   LEDV_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LEDV_SetDriveMode() function.
     *  @{
     */
        #define LEDV_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LEDV_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LEDV_DM_RES_UP          PIN_DM_RES_UP
        #define LEDV_DM_RES_DWN         PIN_DM_RES_DWN
        #define LEDV_DM_OD_LO           PIN_DM_OD_LO
        #define LEDV_DM_OD_HI           PIN_DM_OD_HI
        #define LEDV_DM_STRONG          PIN_DM_STRONG
        #define LEDV_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LEDV_MASK               LEDV__MASK
#define LEDV_SHIFT              LEDV__SHIFT
#define LEDV_WIDTH              1u

/* Interrupt constants */
#if defined(LEDV__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LEDV_SetInterruptMode() function.
     *  @{
     */
        #define LEDV_INTR_NONE      (uint16)(0x0000u)
        #define LEDV_INTR_RISING    (uint16)(0x0001u)
        #define LEDV_INTR_FALLING   (uint16)(0x0002u)
        #define LEDV_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LEDV_INTR_MASK      (0x01u) 
#endif /* (LEDV__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LEDV_PS                     (* (reg8 *) LEDV__PS)
/* Data Register */
#define LEDV_DR                     (* (reg8 *) LEDV__DR)
/* Port Number */
#define LEDV_PRT_NUM                (* (reg8 *) LEDV__PRT) 
/* Connect to Analog Globals */                                                  
#define LEDV_AG                     (* (reg8 *) LEDV__AG)                       
/* Analog MUX bux enable */
#define LEDV_AMUX                   (* (reg8 *) LEDV__AMUX) 
/* Bidirectional Enable */                                                        
#define LEDV_BIE                    (* (reg8 *) LEDV__BIE)
/* Bit-mask for Aliased Register Access */
#define LEDV_BIT_MASK               (* (reg8 *) LEDV__BIT_MASK)
/* Bypass Enable */
#define LEDV_BYP                    (* (reg8 *) LEDV__BYP)
/* Port wide control signals */                                                   
#define LEDV_CTL                    (* (reg8 *) LEDV__CTL)
/* Drive Modes */
#define LEDV_DM0                    (* (reg8 *) LEDV__DM0) 
#define LEDV_DM1                    (* (reg8 *) LEDV__DM1)
#define LEDV_DM2                    (* (reg8 *) LEDV__DM2) 
/* Input Buffer Disable Override */
#define LEDV_INP_DIS                (* (reg8 *) LEDV__INP_DIS)
/* LCD Common or Segment Drive */
#define LEDV_LCD_COM_SEG            (* (reg8 *) LEDV__LCD_COM_SEG)
/* Enable Segment LCD */
#define LEDV_LCD_EN                 (* (reg8 *) LEDV__LCD_EN)
/* Slew Rate Control */
#define LEDV_SLW                    (* (reg8 *) LEDV__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LEDV_PRTDSI__CAPS_SEL       (* (reg8 *) LEDV__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LEDV_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LEDV__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LEDV_PRTDSI__OE_SEL0        (* (reg8 *) LEDV__PRTDSI__OE_SEL0) 
#define LEDV_PRTDSI__OE_SEL1        (* (reg8 *) LEDV__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LEDV_PRTDSI__OUT_SEL0       (* (reg8 *) LEDV__PRTDSI__OUT_SEL0) 
#define LEDV_PRTDSI__OUT_SEL1       (* (reg8 *) LEDV__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LEDV_PRTDSI__SYNC_OUT       (* (reg8 *) LEDV__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LEDV__SIO_CFG)
    #define LEDV_SIO_HYST_EN        (* (reg8 *) LEDV__SIO_HYST_EN)
    #define LEDV_SIO_REG_HIFREQ     (* (reg8 *) LEDV__SIO_REG_HIFREQ)
    #define LEDV_SIO_CFG            (* (reg8 *) LEDV__SIO_CFG)
    #define LEDV_SIO_DIFF           (* (reg8 *) LEDV__SIO_DIFF)
#endif /* (LEDV__SIO_CFG) */

/* Interrupt Registers */
#if defined(LEDV__INTSTAT)
    #define LEDV_INTSTAT            (* (reg8 *) LEDV__INTSTAT)
    #define LEDV_SNAP               (* (reg8 *) LEDV__SNAP)
    
	#define LEDV_0_INTTYPE_REG 		(* (reg8 *) LEDV__0__INTTYPE)
#endif /* (LEDV__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LEDV_H */


/* [] END OF FILE */
