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
#include"Motor.h"
#include"project.h"
#include<CyLib.h>

volatile uint8_t speed = 100;
volatile unsigned long backTimer = 3000;
volatile unsigned long turnSpeed = 3000;
volatile uint8_t forward = 1;

void turnRight(void)
{
    UART_1_PutString("Turning right\r\n");
    driveBackwards();
    CyDelay(backTimer);
    driveForwards();
    PWM_M3_WriteCompare(speed);
    PWM_M1_WriteCompare(0);
    CyDelay(turnSpeed);
    PWM_M1_WriteCompare(speed);
}
void turnLeft(void)
{
    UART_1_PutString("Turning left\r\n");
    driveBackwards();
    CyDelay(backTimer);
    driveForwards();
    PWM_M1_WriteCompare(speed);
    PWM_M3_WriteCompare(0);
    CyDelay(turnSpeed);
    PWM_M3_WriteCompare(speed);
}

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
        PWM_M3_WriteCompare(speed);
        
    }
    else
    {
        PWM_M2_WriteCompare(speed);
        PWM_M4_WriteCompare(speed);//Increase compare variable to increase speed
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
        PWM_M3_WriteCompare(speed);
        PWM_M1_WriteCompare(speed); 
        
    }
    else
    {
        PWM_M2_WriteCompare(speed);
        PWM_M4_WriteCompare(speed);//Increase compare variable to increase speed
    }
}

void driveForwards()
{
    UART_1_PutString("Set direction: forwards\r\n");
    forward = 1;
    stop();
    speed = 50;
    PWM_M1_WriteCompare(speed);
    PWM_M3_WriteCompare(speed);
}

void driveBackwards()
{
    UART_1_PutString("Set direction: backwards\r\n");
    forward = 0;
    stop();
    speed = 50;
    PWM_M2_WriteCompare(speed);
    PWM_M4_WriteCompare(speed);
}

void stop()
{
    UART_1_PutString("Stop\r\n");
	speed = 0;
	PWM_M1_WriteCompare(speed);
    PWM_M2_WriteCompare(speed);
    PWM_M3_WriteCompare(speed);
    PWM_M4_WriteCompare(speed);
}

/* [] END OF FILE */
