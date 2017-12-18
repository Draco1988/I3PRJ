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
#include "RPICom.h"
void sendValue(char c)
{
    SPI_Slave_WriteTxData(c); //Sende SPI besked med værdien c
}
/* [] END OF FILE */
