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
#include"LoadCell.h"
#include"project.h"
#include <stdio.h>

char uartBufferLoad[256];

void checkLoad()
{
    if (ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT))
        {
			//Get current measurement from ADC
            uint16_t result = ADC_SAR_1_GetResult16();
			//Convert measurement to mV using the built-in function
			uint16_t resultInMVolts = ADC_SAR_1_CountsTo_mVolts(result); //
			//Convert to grams using linear function
			float convertedResult = (result - 1471.8)/1.4174;  
            //float convertedResult = result/1.4174;
            
            snprintf(uartBufferLoad,sizeof(uartBufferLoad),"Result er %f\r\n",convertedResult);
            UART_1_PutString(uartBufferLoad);
            if (convertedResult < 100)
            {
                UART_1_PutString("Result er under 100\r\n");  
                SPI_Slave_WriteTxData('V');
            }
        }
}

/* [] END OF FILE */
