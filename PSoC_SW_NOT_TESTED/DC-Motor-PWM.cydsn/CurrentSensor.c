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

#include"CurrentSensor.h"
#include"project.h"
#include <stdio.h>

//#define CRITICAL_LEVEL 330       //700 mV over 0.1 ohm resistor
//
//char uartBufferCurrent[256];
//void checkCurrent()
//{
//    // Code to be run when an ADC conversion is ready
//        if (ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT))
//        {
//            // Store result from conversion in result
//            float result = ADC_SAR_1_GetResult16();
//                   
//            snprintf(uartBufferCurrent, sizeof(uartBufferCurrent), "%f \r\n", result);
//            UART_1_PutString(uartBufferCurrent);   //prints the measures weight in grams
//            
//            if(result > CRITICAL_LEVEL)
//            {
//            UART_1_PutString("Current level to high. Stop Broomba");   //prints the measures weight in grams
//            SPI_Slave_WriteTxData('O');
//            }
//            
//        }
//        CyDelay(500);
//    }

/* [] END OF FILE */
