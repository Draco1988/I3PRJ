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
#include"LiquidSensor.h"
#include"project.h"
#include"RPICom.h"
#include <stdio.h>

char uartBufferLoad[256];
volatile int16_t offsetADC = 0;

void readLValue()
{
    if (ADC_SAR_V_IsEndConversion(ADC_SAR_V_WAIT_FOR_RESULT))
        {
			//Get current measurement from ADC
            uint16_t result = ADC_SAR_V_GetResult16();
			//Convert measurement to mV using the built-in function
			uint16_t resultInMVolts = ADC_SAR_V_CountsTo_mVolts(result); //
			//Convert to grams using linear function
			float convertedResult = (result - 1471.8)/1.4174;  
            //float convertedResult = result/1.4174;
            
            snprintf(uartBufferLoad,sizeof(uartBufferLoad),"Result er %f\r\n",convertedResult);
            UART_1_PutString(uartBufferLoad);
            if (convertedResult < 100)
            {
                UART_1_PutString("Result er under 100\r\n");  
                sendValue('V'); //sender til RPI
                Pin_ADC_V_Write(1); //tænder LED
            }
            else 
            {
                Pin_ADC_V_Write(0); //Slukker LED
                sendValue('I'); //sender til RPI
            }
        }
}

/* [] END OF FILE */
