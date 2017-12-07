/*******************************************************************************
* File Name: PWM_P_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_P.h"

static PWM_P_backupStruct PWM_P_backup;


/*******************************************************************************
* Function Name: PWM_P_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_P_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_P_SaveConfig(void) 
{

    #if(!PWM_P_UsingFixedFunction)
        #if(!PWM_P_PWMModeIsCenterAligned)
            PWM_P_backup.PWMPeriod = PWM_P_ReadPeriod();
        #endif /* (!PWM_P_PWMModeIsCenterAligned) */
        PWM_P_backup.PWMUdb = PWM_P_ReadCounter();
        #if (PWM_P_UseStatus)
            PWM_P_backup.InterruptMaskValue = PWM_P_STATUS_MASK;
        #endif /* (PWM_P_UseStatus) */

        #if(PWM_P_DeadBandMode == PWM_P__B_PWM__DBM_256_CLOCKS || \
            PWM_P_DeadBandMode == PWM_P__B_PWM__DBM_2_4_CLOCKS)
            PWM_P_backup.PWMdeadBandValue = PWM_P_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_P_KillModeMinTime)
             PWM_P_backup.PWMKillCounterPeriod = PWM_P_ReadKillTime();
        #endif /* (PWM_P_KillModeMinTime) */

        #if(PWM_P_UseControl)
            PWM_P_backup.PWMControlRegister = PWM_P_ReadControlRegister();
        #endif /* (PWM_P_UseControl) */
    #endif  /* (!PWM_P_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_P_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_P_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_P_RestoreConfig(void) 
{
        #if(!PWM_P_UsingFixedFunction)
            #if(!PWM_P_PWMModeIsCenterAligned)
                PWM_P_WritePeriod(PWM_P_backup.PWMPeriod);
            #endif /* (!PWM_P_PWMModeIsCenterAligned) */

            PWM_P_WriteCounter(PWM_P_backup.PWMUdb);

            #if (PWM_P_UseStatus)
                PWM_P_STATUS_MASK = PWM_P_backup.InterruptMaskValue;
            #endif /* (PWM_P_UseStatus) */

            #if(PWM_P_DeadBandMode == PWM_P__B_PWM__DBM_256_CLOCKS || \
                PWM_P_DeadBandMode == PWM_P__B_PWM__DBM_2_4_CLOCKS)
                PWM_P_WriteDeadTime(PWM_P_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_P_KillModeMinTime)
                PWM_P_WriteKillTime(PWM_P_backup.PWMKillCounterPeriod);
            #endif /* (PWM_P_KillModeMinTime) */

            #if(PWM_P_UseControl)
                PWM_P_WriteControlRegister(PWM_P_backup.PWMControlRegister);
            #endif /* (PWM_P_UseControl) */
        #endif  /* (!PWM_P_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_P_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_P_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_P_Sleep(void) 
{
    #if(PWM_P_UseControl)
        if(PWM_P_CTRL_ENABLE == (PWM_P_CONTROL & PWM_P_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_P_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_P_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_P_UseControl) */

    /* Stop component */
    PWM_P_Stop();

    /* Save registers configuration */
    PWM_P_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_P_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_P_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_P_Wakeup(void) 
{
     /* Restore registers values */
    PWM_P_RestoreConfig();

    if(PWM_P_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_P_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
