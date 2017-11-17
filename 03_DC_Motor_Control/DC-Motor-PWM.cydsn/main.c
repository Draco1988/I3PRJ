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
#include <CyLib.h>

volatile uint8_t speed = 50;
volatile uint8_t turnspeed = 3;
volatile uint8 received = 0; //Varaible to store received data
volatile uint8 intFlag = 0; //Variable to indicate if there have been an interrupt

CY_ISR_PROTO(ISR_SPI); //Interrupt prototype
CY_ISR(ISR_SPI) //Interrupt service routine
{
    received = SPI_Slave_ReadRxData(); //Storing the received data
    intFlag = 1; //Indicating that an interrupt has occurred
    SPI_Slave_ClearRxBuffer(); //Clearing the RX buffer
    SPI_Slave_ClearFIFO(); //Clearing the FIFO register
}

CY_ISR_PROTO(ISR_UART_rx_handler);
void handleByteReceived(uint8_t byteReceived);
void decreaseSpeed(void);
void increaseSpeed(void);
void driveForwards(void);
void driveBackwards(void);
void stop(void);
//void turnRight(void);
//void turnLeft(void);


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    isr_uart_rx_StartEx(ISR_UART_rx_handler);
    UART_1_Start();
    PWM_M1_Start();    //PWM Motor1 (hjul)
    PWM_M2_Start();    //PWM Motor2 (hjul)
    //PWM_B_Start();   //PWM Børste
    //PWM_P_Start();   //PWM pumpe
	Pin_1_H_Write(1);  //H-Bro 2 
	Pin_2_H_Write(0);  //H-Bro 1
    //Pin_1_S_Read();    //Sensor 2
    //Pin_2_S_Read();    //Sensor 1
    
    
    UART_1_PutString("DC-Motor-PWM application started\r\n");
    UART_1_PutString("0: Stop\r\n");
    UART_1_PutString("1: Drive forwards\r\n");
    UART_1_PutString("2: Drive backwards\r\n");
    UART_1_PutString("q: Decrease speed\r\n");
    UART_1_PutString("w: Increase speed\r\n");

    for(;;)
    {
        //If and interrupt has occurred
        if(intFlag == 1)
        {
            intFlag = 0; //Reset to next interrupt
            
            //Looking at what is recevied
            if(received == '1')
            {
                UART_1_PutString("Modtaget: '1' fra spi\r\n");
            }
            else if( received == '0')
            {
                UART_1_PutString("Modtaget: '0' fra spi\r\n");
            }
            else if(received == 's')
            {
                UART_1_PutString("Modtaget: 's' fra spi sender s tilbage\r\n");
                SPI_Slave_WriteTxData(received); //WriteData the status of the LED back to the master
                SPI_Slave_ClearRxBuffer();
                SPI_Slave_ClearTxBuffer();                
            }
            else
            {
                UART_1_PutString("Har modtaget: ");
                char mod[8]; 
                mod[0]= received;
                UART_1_PutChar(mod[0]);
                UART_1_PutString("\r\n");
            }
        }
    }
}

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
        default :
        {
            // nothing
        }
        break;
    }
}

//void turnRight(void)
//{
//    UART_1_PutString("Turning right\r\n");
//    PWM_M2_WriteCompare(speed);
//    PWM_M1_WriteCompare(0);
//    CyDelay(Turnspeed);
//    PWM_M1_WriteCompare(speed);
//}
//void turnLeft(void)
//{
//    UART_1_PutString("Turning left\r\n");
//    PWM_M1_WriteCompare(speed);
//    PWM_M2_WriteCompare(0);
//    CyDelay(Turnspeed);
//    PWM_M2_WriteCompare(speed);
//}

void decreaseSpeed()
{
    UART_1_PutString("Decreasing speed\r\n");

	if (speed <= 10)
	{
		speed = 0;
	}
	else
	{
		speed -= 10;
	}

    PWM_M1_WriteCompare(speed); //Decrease compare variable to decrease speed
    PWM_M2_WriteCompare(speed);
}

void increaseSpeed()
{
    UART_1_PutString("Increasing speed\r\n");
	speed = speed + 10;
	if (speed > 100)
	{
		speed = 100;
	}
    
    PWM_M1_WriteCompare(speed);
    PWM_M2_WriteCompare(speed);//Increase compare variable to increase speed
}

void driveForwards()
{
    UART_1_PutString("Set direction: forwards\r\n");
	if (speed == 0) //Start from stop
	{
		speed = 50;
		PWM_M1_WriteCompare(speed);
        PWM_M2_WriteCompare(speed);
	}
	Pin_1_H_Write(1);
	Pin_2_H_Write(0);
}

void driveBackwards()
{
    UART_1_PutString("Set direction: backwards\r\n");
	if (speed == 0) //Start from stop
	{
		speed = 50;
		PWM_M1_WriteCompare(speed);
        PWM_M2_WriteCompare(speed);
	}
	Pin_1_H_Write(0);
	Pin_2_H_Write(1);
}

void stop()
{
    UART_1_PutString("Stop\r\n");
	speed = 0;
	PWM_M1_WriteCompare(speed);
    PWM_M2_WriteCompare(speed);
}
