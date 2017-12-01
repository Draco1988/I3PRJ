
#include "project.h"
#include <stdlib.h>
#include <stdio.h>
volatile uint8 received = 0; //Varaible to store received data
volatile uint8 intFlag = 0; //Variable to indicate if there have been an interrupt
volatile uint8 numberPrinted = 0;

CY_ISR_PROTO(ISR_SPI); //Interrupt prototype
CY_ISR(ISR_SPI) //Interrupt service routine
{
    received = SPI_Slave_ReadRxData(); //Storing the received data
    intFlag = 1; //Indicating that an interrupt has occurred
    SPI_Slave_ClearRxBuffer(); //Clearing the RX buffer
    SPI_Slave_ClearFIFO(); //Clearing the FIFO register
}

int main(void)
{
    CyGlobalIntEnable; //Enable global interrupts. 

    UART_Slave_Start(); //Starting UART on the slave
    
    UART_Slave_PutString("\r\n\r\n ---------- Connection Established ---------- \r\n\r\n"); //Printing to the UART
    
    ISR_SPI_StartEx(ISR_SPI); //Initialising the ISR
    
    SPI_Slave_Start(); // Starting the SPI Slave
    char test[100];
    //char testchar[1];
    char sluk[8];
    
    for(;;)
    {
        SPI_Slave_WriteTxData('a');
        CyDelay(200);
        //itoa(received,testchar,10);
        //If an interrupt has occurred
        //if(intFlag == 1)
        //{
         //   intFlag = 0; //Reset to next interrupt
       
            //Looking at what is recevied
           // snprintf(test,100,"%d Den sendte integer er: %d\r\n",++numberPrinted ,received );
            //UART_Slave_PutString(test);               
      
     //   }

    }
}

 //[] END OF FILE */
