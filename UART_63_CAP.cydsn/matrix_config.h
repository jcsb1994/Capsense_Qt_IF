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

#ifndef MATRIX_CONFIG_H
#define MATRIX_CONFIG_H

#define ROW_TAXELS_NB 0b101   
#define COL_TAXELS_NB 0b101
    
#define MATRIX_DIMENSIONS_BYTE (ROW_TAXELS_NB << 4) + COL_TAXELS_NB

enum taxels
{
RX0_TX0,
RX0_TX1,
RX0_TX2,
RX0_TX3,
RX0_TX4,

RX1_TX0,
RX1_TX1,
RX1_TX2,
RX1_TX3,
RX1_TX4,

RX2_TX0,
RX2_TX1,
RX2_TX2,
RX2_TX3,
RX2_TX4,

RX3_TX0,
RX3_TX1,
RX3_TX2,
RX3_TX3,
RX3_TX4,

RX4_TX0,
RX4_TX1,
RX4_TX2,
RX4_TX3,
RX4_TX4 
};
    


/* [] END OF FILE */
#endif // MATRIX_CONFIG_H