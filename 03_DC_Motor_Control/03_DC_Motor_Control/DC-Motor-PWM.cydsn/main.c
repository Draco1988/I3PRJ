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

#define LEFT 1u
#define RIGHT 2u

volatile uint8_t speed = 50;
volatile uint turnspeed = 300;
volatile uint backtimer = 500;
volatile uint8_t sensor = 0;
volatile uint8 received = 0; //Varaible to store received data
volatile uint8 intFlag = 0; //Variable to indicate if there have been an interrupt
volatile uint8 forward = 1;

volatile static uint8 flag = 0;
static uint8 turn = 0;

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
    flag = Pin_1_Read();
    UART_1_PutString("Flag bliver sat. Pin1\r\n");

    
    CyDelay(50);
    //Check which pin caused the interrupt by reading interrupt status register
    if(Pin_1_INTSTAT & (0x01 << Pin_1_SHIFT))
    {
        turn = LEFT;
        CyDelay(50);
    }
    else
    {
        turn = RIGHT;
        CyDelay(50);
    }
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
//    stop();
//    driveBackwards();
//    CyDelay(backTimer);
//    driveForwards();
//    PWM_M2_WriteCompare(speed);
//    PWM_M4_WriteCompare(0);
//    CyDelay(Turnspeed);
//    PWM_M4_WriteCompare(speed);
//}
//void turnLeft(void)
//{
//    UART_1_PutString("Turning left\r\n");
//    stop();
//    driveBackwards();
//    CyDelay(backTimer);
//    driveForwards();
//    PWM_M1_WriteCompare(speed);
//    PWM_M3_WriteCompare(0);
//    CyDelay(Turnspeed);
//    PWM_M3_WriteCompare(speed);
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

    if (forward == 1)
    {
        PWM_M1_WriteCompare(speed);    
    }
    else
    {
        PWM_M2_WriteCompare(speed);//Increase compare variable to increase speed
    }
}

void increaseSpeed()
{
    UART_1_PutString("Increasing speed\r\n");
	speed = speed + 10;
	if (speed > 100)
	{
		speed = 100;
	}
    if (forward == 1)
    {
        PWM_M1_WriteCompare(speed);    
    }
    else
    {
        PWM_M2_WriteCompare(speed);//Increase compare variable to increase speed
    }
}

void driveForwards()
{
    UART_1_PutString("Set direction: forwards\r\n");
    forward = 1;
    PWM_M1_WriteCompare(0);
    CyDelay(1);
    speed = 50;
    PWM_M1_WriteCompare(speed);
}

void driveBackwards()
{
    UART_1_PutString("Set direction: backwards\r\n");
    forward = 0;
    PWM_M2_WriteCompare(0);
    CyDelay(1);
    speed = 50;
    PWM_M2_WriteCompare(speed);
}

void stop()
{
    UART_1_PutString("Stop\r\n");
	speed = 0;
	PWM_M1_WriteCompare(speed);
    PWM_M2_WriteCompare(speed);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    isr_uart_rx_StartEx(ISR_UART_rx_handler);
    isr_1_StartEx(sensor_ISR);
    UART_1_Start();
    SPI_Slave_Start();
    PWM_M1_Start();    //PWM Motor1 (1hjul)
    PWM_M2_Start();    //PWM Motor1 (1hjul)
    //PWM_M3_Start();   //PWM Motor2 (2jhul)
    //PWM_M4_Start();   //PWM Motor2 (2hjul)
    //Pin_1_S_Read();    //Sensor 2
    //Pin_2_S_Read();    //Sensor 1
    ISR_SPI_StartEx(ISR_SPI);
    
    
    
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
            char test[100];
          //Looking at what is recevied
            snprintf(test,100," Den sendte integer er: %d\r\n",received );
            UART_1_PutString(test); 
            
       
        }
        
        if(turn == LEFT)
        {
            UART_1_PutString("Venstre sensor\r\n");
            
            CyDelay(50);
            UART_1_PutString("Venstre sensor gennemfoert\r\n");
            //turnRight();
            CyDelay(500);
            flag = 0;
            UART_1_PutString("Interrupt reset\r\n");    
            Pin_1_ClearInterrupt();
            
            
        } 
        else if(turn == RIGHT)
        {
            UART_1_PutString("Hoejre sensor\r\n");           
            
            CyDelay(50);
            UART_1_PutString("Hoejre sensor gennemfoert\r\n");
            
            //turnLeft();
            CyDelay(500);
            flag = 0;
            UART_1_PutString("Interrupt reset\r\n");    
            Pin_1_ClearInterrupt();
        }
        turn = 0;
        //SPI_Slave_WriteTxData('5');
        //CyDelay(300);
        
        
    }
    return 0;
}
