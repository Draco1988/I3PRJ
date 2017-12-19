/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.


 * OPS PUMPE 40% pwm
 * ========================================
*/
#include "project.h"
#include <CyLib.h>
#include <stdio.h>
#include <stdlib.h>
#include "Motor.h"
#include "BatterySensor.h"
#include "LoadCell.h"

#define LEFT 1u
#define RIGHT 2u



volatile uint8_t sensor = 0;
volatile uint8_t received = 0; //Varaible to store received data
volatile uint8_t intFlag = 0; //Variable to indicate if there have been an interrupt

static uint8 sensorPushed = 0;

CY_ISR_PROTO(ISR_SPI); //Interrupt prototype
CY_ISR(ISR_SPI) //Interrupt service routine
{
    received = SPI_Slave_ReadRxData(); //Storing the received data
    intFlag = 1; //Indicating that an interrupt has occurred
    SPI_Slave_ClearRxBuffer(); //Clearing the RX buffer
    SPI_Slave_ClearFIFO(); //Clearing the FIFO register
}

CY_ISR(sensor_ISR)
{
    if(!sensor)
    {
    sensor = Pin_1_Read();
    UART_1_PutString("Flag bliver sat. Pin1\r\n");
     if(Pin_1_INTSTAT & (0x01 << Pin_1_SHIFT))
    {
        sensorPushed = LEFT;
    }
    else
    {
        sensorPushed = RIGHT;
    }
    }
    
     Pin_1_ClearInterrupt(); // Clears interrupt, makes ready for new one
    
}

CY_ISR_PROTO(ISR_UART_rx_handler);
void handleByteReceived(uint8_t byteReceived);
CY_ISR(ISR_UART_rx_handler)
{
	//Read char from RX buffer and react
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
        case 'q' :
        {
            decreaseSpeed();
        }
        break;
        case 'w' :
        {
            increaseSpeed();
        }
        break;
        case '1' :
        {
            driveForwards();
        }
        break;
        case '2' :
        {
            driveBackwards();
        }
        break;
        case '0' :
        {
            stop();
            
        }
        break;
          break;
        case 'h' :
        {
            turnLeft();
            
        }
        break;
          break;
        case 'v' :
        {
            turnRight();
            
        }
        break;
        case 't' :
        {
            if(ADC_SAR_V_IsEndConversion(ADC_SAR_V_WAIT_FOR_RESULT))
            {
            int16_t offset = 0;
            offset = ADC_SAR_V_GetResult16();
            ADC_SAR_V_SetOffset(offset);
            }
        }
        default :
        {
            // nothing
        }
        break;
    }
}


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    isr_uart_rx_StartEx(ISR_UART_rx_handler);
    isr_1_StartEx(sensor_ISR);
    ISR_SPI_StartEx(ISR_SPI);
    UART_1_Start();
    SPI_Slave_Start();
    ADC_SAR_V_Start();
    ADC_SAR_V_StartConvert();
    ADC_SAR_B_Start();
    ADC_SAR_B_StartConvert();
    PWM_M1_Start();    //PWM Motor1 (1hjul)
    PWM_M2_Start();    //PWM Motor1 (1hjul)
    PWM_M3_Start();   //PWM Motor2 (2jhul)
    PWM_M4_Start();   //PWM Motor2 (2hjul)
    PWM_P_Start();
    
  
    
    
    
    UART_1_PutString("DC-Motor-PWM application started\r\n");
    UART_1_PutString("0: Stop\r\n");
    UART_1_PutString("1: Drive forwards\r\n");
    UART_1_PutString("2: Drive backwards\r\n");
    UART_1_PutString("q: Decrease speed\r\n");
    UART_1_PutString("w: Increase speed\r\n");
    PWM_P_WriteCompare(80);
    PWM_M1_WriteCompare(100);
    PWM_M3_WriteCompare(100);
    
    for(;;)
    {
        //CyDelay(500);
       
        UART_1_PutString("Broomba run\r\n");
        if(sensorPushed == LEFT)
        {
            turnLeft();
            sensor = 0;
        } 
        else if(sensorPushed == RIGHT)
        {
           turnRight();
            sensor = 0;
        }
        Pin_1_ClearInterrupt();
        isr_1_ClearPending();
        sensorPushed = 0;
        CyDelay(2000);
        
        checkBattery();
        //checkLoad();
    }
    return 0;
}
