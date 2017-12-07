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

enum StepMode {
	WAVE = 0,
	FULLSTEP = 1,
	HALFSTEP = 2, 
	SNGCLOCK = 3, //Single step
	SNGCNTCLOCK = 4, //Single counterclockwise step
	STOP = 5
};

volatile enum StepMode stepMode = WAVE;
volatile uint8_t position = 0;
volatile uint8_t direction = 0;
volatile uint32 delay = 5;

CY_ISR_PROTO(ISR_UART_rx_handler);
CY_ISR_PROTO(ISR_Timer_TC);
void handleByteReceived(uint8 byteReceived);
void decreaseSpeed(void);
void increaseSpeed(void);
void driveForwards(void);
void driveBackwards(void);
void step(void);

CY_ISR(ISR_Timer_TC)
{
}
CY_ISR(ISR_UART_rx_handler)
{
    uint8_t bytesToRead = UART_GetRxBufferSize();
    while (bytesToRead > 0)
    {
        uint8_t byteReceived = UART_ReadRxData();
        UART_WriteTxData(byteReceived); // echo back
        
        handleByteReceived(byteReceived);
        
        bytesToRead--;
    }
}


	

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    isr_uart_StartEx(ISR_UART_rx_handler);
	//isr_timer_StartEx(ISR_Timer_TC);
    UART_Start();
	//Timer_Start();
  
    
    UART_PutString("Stepper motor application started\r\n");
    UART_PutString("0: Stop\r\n");
    UART_PutString("1: Drive forwards\r\n");
    UART_PutString("2: Drive backwards\r\n");
    UART_PutString("q: Decrease speed\r\n");
    UART_PutString("w: Increase speed\r\n");
	UART_PutString("5: Single rotation clockwise\r\n");
	UART_PutString("6: Single rotation counter clockwise\r\n");
	UART_PutString("7: Wave Drive\r\n");
	UART_PutString("8: Full Drive\r\n");
	UART_PutString("9: Half Step Drive\r\n");

    for(;;)
    {
		CyDelay(delay);
		step();
        /* Place your application code here. */
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
            stepMode = STOP;
            
        }
        break;
        case '5' :
        {
			UART_PutString("Single rotation clockwise\r\n");
			position = 0;
            stepMode = SNGCLOCK;
        }
        break;
        case '6' :
        {
			UART_PutString("Wave mode\r\n");
			position = 0;
            stepMode = SNGCNTCLOCK; 
        }
        break;
        case '7' :
        {
			UART_PutString("Wave mode\r\n");
			position = 0;
            stepMode = WAVE;
        }
        break;
        case '8' :
        {
			UART_PutString("Full step\r\n");
			position = 0;
            stepMode = FULLSTEP;		
            
        }
        break;
        case '9' :
        {
			UART_PutString("Half-drive step\r\n");
			position = 0;
            stepMode = HALFSTEP;          
        }
        break;
        default :
        {
            // nothing
        }
        break;
    }
}

void decreaseSpeed()
{
    UART_PutString("Decreasing speed\r\n");
	if (delay >= 8)
	{
	}
	else
	{
		delay++;
	}
}

void increaseSpeed()
{
    UART_PutString("Increasing speed\r\n");
	if (delay <= 1)
	{
	}
	else
	{
		delay--;
	}
	

}

void driveForwards()
{
    UART_PutString("Set direction: forwards\r\n");
	direction = 0;
	position = 0;
}

void driveBackwards()
{
    UART_PutString("Set direction: backwards\r\n");
	direction = 1;
	position = 0;	
}

void step()
{
	if (stepMode == WAVE)
	{
		switch(position)
		{
			case 0:
			{
				if (direction == 0)
				{
					position++;
				}
				else
				{
					position = 3;
				}
				Pin_1_Write(1); //A
				Pin_2_Write(0); //A'
				Pin_3_Write(0); //B
				Pin_4_Write(0); //B'
			}
			break;
			case 1:
			{
				if (direction == 0)
				{
					position++;
				}
				else
				{
					position = 0;
				}
				Pin_1_Write(0);//A
				Pin_2_Write(0);//A'
				Pin_3_Write(1);//B
				Pin_4_Write(0);//B'
			}
			break;
			case 2:
			{
				if (direction == 0)
				{
					position++;
				}
				else
				{
					position = 1;
				}
				Pin_1_Write(0);
				Pin_2_Write(1);
				Pin_3_Write(0);
				Pin_4_Write(0);
			}
			break;
			case 3:
			{
				if (direction == 0)
				{
					position++;
				}
				else
				{
					position = 2;
				}
				Pin_1_Write(0);
				Pin_2_Write(0);
				Pin_3_Write(0);
				Pin_4_Write(1);
			}
			break;
			case 4:
			{
				position = 0; //Reset position
			}
			break;
			default:
			{
			}
			break;
			
		}
	}
	else if (stepMode == FULLSTEP)
	{
		switch(position)
		{
			case 0:
			{
				if (direction == 0)
				{
					position++;
				}
				else
				{
					position = 3;
				}
				Pin_1_Write(1);//A
				Pin_2_Write(0);//A'
				Pin_3_Write(1);//B
				Pin_4_Write(0);//B'
			}
			break;
			case 1:
			{
				if (direction == 0)
				{
					position++;
				}
				else
				{
					position = 0;
				}
				Pin_1_Write(0);//A
				Pin_2_Write(1);//A'
				Pin_3_Write(1);//B
				Pin_4_Write(0);//B'
			}
			break;
			case 2:
			{
				if (direction == 0)
				{
					position++;
				}
				else
				{
					position = 1;
				}
				Pin_1_Write(0);
				Pin_2_Write(1);
				Pin_3_Write(0);
				Pin_4_Write(1);
			}
			break;
			case 3:
			{
				if (direction == 0)
				{
					position++;
				}
				else
				{
					position = 2;
				}
				Pin_1_Write(1);
				Pin_2_Write(0);
				Pin_3_Write(0);
				Pin_4_Write(1);
			}
			break;
			case 4:
			{
				position = 0; //Reset position
			}
			break;
			
			default:
			{
			}
			break;
			
		}
	}
	else if (stepMode == HALFSTEP)
	{
		switch(position)
		{
			case 0:
			{
				if (direction == 0)
				{
					position++;
				}
				else
				{
					position = 7;
				}
				Pin_1_Write(1);//A
				Pin_2_Write(0);//A'
				Pin_3_Write(1);//B
				Pin_4_Write(0);//B'
			}
			break;
			case 1:
			{
				if (direction == 0)
				{
					position++;
				}
				else
				{
					position = 0;
				}
				Pin_1_Write(0);//A
				Pin_2_Write(0);//A'
				Pin_3_Write(1);//B
				Pin_4_Write(0);//B'
			}
			break;
			case 2:
			{
				if (direction == 0)
				{
					position++;
				}
				else
				{
					position = 1;
				}
				Pin_1_Write(0);
				Pin_2_Write(1);
				Pin_3_Write(1);
				Pin_4_Write(0);
			}
			break;
			case 3:
			{
				if (direction == 0)
				{
					position++;
				}
				else
				{
					position = 2;
				}
				Pin_1_Write(0);
				Pin_2_Write(1);
				Pin_3_Write(0);
				Pin_4_Write(0);
			}
			break;
			case 4:
			{
				if (direction == 0)
				{
					position++;
				}
				else
				{
					position = 3;
				}
				Pin_1_Write(0);
				Pin_2_Write(1);
				Pin_3_Write(0);
				Pin_4_Write(0);
			}
			break;
			case 5:
			{
				if (direction == 0)
				{
					position++;
				}
				else
				{
					position = 4;
				}
				Pin_1_Write(0);
				Pin_2_Write(0);
				Pin_3_Write(0);
				Pin_4_Write(1);
			}
			break;
			case 6:
			{
				if (direction == 0)
				{
					position++;
				}
				else
				{
					position = 5;
				}
				Pin_1_Write(1);
				Pin_2_Write(0);
				Pin_3_Write(0);
				Pin_4_Write(1);
			}
			break;
			case 7:
			{
				if (direction == 0)
				{
					position++;
				}
				else
				{
					position = 6;
				}
				Pin_1_Write(1);
				Pin_2_Write(0);
				Pin_3_Write(0);
				Pin_4_Write(1);
			}
			break;
			case 8:
			{
				position = 0; //Reset position
			}
			break;
			default:
			{
			}
			break;
			
		}
	}
	else if (stepMode == SNGCLOCK)
	{
		switch(position)
		{
			case 0:
			{
				position++;
				Pin_1_Write(1);//A
				Pin_2_Write(0);//A'
				Pin_3_Write(1);//B
				Pin_4_Write(0);//B'
			}
			break;
			case 1:
			{
				position++;
				Pin_1_Write(0);//A
				Pin_2_Write(1);//A'
				Pin_3_Write(1);//B
				Pin_4_Write(0);//B'
			}
			break;
			case 2:
			{
				position++;
				Pin_1_Write(0);
				Pin_2_Write(1);
				Pin_3_Write(0);
				Pin_4_Write(1);
			}
			break;
			case 3:
			{
				position++;
				Pin_1_Write(1);
				Pin_2_Write(0);
				Pin_3_Write(0);
				Pin_4_Write(1);
			}
			break;
			case 4:
			{
				position = 0;
				stepMode = STOP; //Stop after single step
			}
			break;
			
			default:
			{
			}
			break;
			
		}
	}
	else if (stepMode == SNGCNTCLOCK)
	{
		switch(position)
		{
			case 0:
			{
				position++;
				Pin_1_Write(1);//A
				Pin_2_Write(0);//A'
				Pin_3_Write(0);//B
				Pin_4_Write(1);//B'
			}
			break;
			case 1:
			{
				position++;
				Pin_1_Write(0);//A
				Pin_2_Write(1);//A'
				Pin_3_Write(0);//B
				Pin_4_Write(1);//B'
			}
			break;
			case 2:
			{
				position++;
				Pin_1_Write(0);
				Pin_2_Write(1);
				Pin_3_Write(1);
				Pin_4_Write(0);
			}
			break;
			case 3:
			{
				position++;
				Pin_1_Write(1);
				Pin_2_Write(0);
				Pin_3_Write(1);
				Pin_4_Write(0);
			}
			break;
			case 4:
			{
				position = 0;
				stepMode = STOP; //Stop after single step
			}
			break;
			
			default:
			{
			}
			break;
			
		}
	}
}