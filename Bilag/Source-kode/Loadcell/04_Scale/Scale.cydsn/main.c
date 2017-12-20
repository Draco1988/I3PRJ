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
#include "project.h"
#include <stdio.h>
#include <stdlib.h>

CY_ISR_PROTO(ISR_UART_rx_handler);
void handleByteReceived(uint8_t byteReceived);

int16_t offsetADC = 0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    char uartBuffer[256];

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    isr_uart_rx_StartEx(ISR_UART_rx_handler);
    UART_1_Start();
    ADC_SAR_1_Start();
    ADC_SAR_1_StartConvert();

    UART_1_PutString("Scale application started\r\n");

    for(;;)
    {
        /* Place your application code here. */
        if (ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT))
        {
			//Get current measurement from ADC
            uint16_t result = ADC_SAR_1_GetResult16();
			//Convert measurement to mV using the built-in function
			uint16_t resultInMVolts = ADC_SAR_1_CountsTo_mVolts(result);    
			
			//Convert to grams using linear function
			float convertedResult = (result - 1471.8)/1.4174;   
			
			//Put results into string and print to user
            snprintf(uartBuffer, sizeof(uartBuffer), "ADC result: %d in mV: 0x%x \t Converted: %f\r\n", result, resultInMVolts, convertedResult);
            UART_1_PutString(uartBuffer);
        }
        CyDelay(100);
    }
}

CY_ISR(ISR_UART_rx_handler)
{
    uint8_t bytesToRead = UART_1_GetRxBufferSize();
    while (bytesToRead > 0)
    {
        uint8_t byteReceived = UART_1_ReadRxData();
        UART_1_WriteTxData(byteReceived); // echo back
        
        handleByteReceived(byteReceived);
        
        bytesToRead--;
    }
}

void handleByteReceived(uint8_t byteReceived)
{
    switch(byteReceived)
    {
        case 'r' :
        {
			UART_1_PutString("Resetting ADC\r\n");
			if (ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT))
			{
				offsetADC = ADC_SAR_1_GetResult16(); //Get current value from ADC
				ADC_SAR_1_SetOffset(offsetADC); //Set offset to current value, resetting the ADC to 0
			}

        }

        break;
        default :
        {
            // nothing
        }
        break;
    }
}

/* [] END OF FILE */
