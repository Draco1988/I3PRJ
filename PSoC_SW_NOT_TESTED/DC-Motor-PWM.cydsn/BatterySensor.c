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
#include"project.h"
#include"BatterySensor.h"
#include <stdio.h>

#define CRITICAL_LEVEL 1.92       //1.92 V = 20% Battery Voltage 9,6 V

float voltage = 0;
char uartBufferBattery[256];

void checkBattery()
{
    if (ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT))
        {
            // Store result from conversion in result
            float result = ADC_SAR_1_GetResult16();
            
            voltage = (result-51.6)/397.6;  //x = (y-b)/a
                   
            snprintf(uartBufferBattery, sizeof(uartBufferBattery), "%f \r\n", voltage);
            UART_1_PutString(uartBufferBattery);   //prints the measures weight in grams
            
            if(voltage < CRITICAL_LEVEL)
            {
            UART_1_PutString("Voltage level too low. Stop Broomba");   //prints the measures weight in grams
            SPI_Slave_WriteTxData('B');
            }
            
        }
        CyDelay(500);
}

/* [] END OF FILE */
