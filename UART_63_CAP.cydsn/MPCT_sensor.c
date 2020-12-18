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

#include "MPCT_sensor.h"




    
bool get_taxel_raw_count_iterator(uint32 *taxel_raw_values)
{
    static uint curr_elem;

                switch(curr_elem)
            {

                case RX0_TX0:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX0_TX0_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                case  RX0_TX1:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX0_TX1_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                case RX0_TX2:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX0_TX2_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                case RX0_TX3:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX0_TX3_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                case RX0_TX4:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX0_TX4_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                
                case RX1_TX0:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX1_TX0_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                case RX1_TX1:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX1_TX1_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                case RX1_TX2:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX1_TX2_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                case RX1_TX3:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX1_TX3_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                case RX1_TX4:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX1_TX4_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                
                case RX2_TX0:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX2_TX0_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                case RX2_TX1:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX2_TX1_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                case RX2_TX2:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX2_TX2_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                case RX2_TX3:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX2_TX3_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                case RX2_TX4:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX2_TX4_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                
                case RX3_TX0:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX3_TX0_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                case RX3_TX1:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX3_TX1_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                case RX3_TX2:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX3_TX2_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                case RX3_TX3:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX3_TX3_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                case RX3_TX4:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX3_TX4_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                
                case RX4_TX0:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX4_TX0_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                case RX4_TX1:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX4_TX1_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                case RX4_TX2:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX4_TX2_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                case RX4_TX3:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX4_TX3_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;
                case RX4_TX4:
                CapSense_GetParam(CapSense_TOUCHPAD0_RX4_TX4_RAW0_PARAM_ID, &taxel_raw_values[curr_elem]);
                break;

                default:
                break;
            }

            if(curr_elem < RX4_TX4)
            {
                curr_elem++;
                return 0;
            }
            else
            {
                curr_elem = 0;
                return 1;
            }
            
}



/* [] END OF FILE */
