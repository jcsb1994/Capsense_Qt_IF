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
#include "stdio.h"
#include "matrix_config.h"
#include "MPCT_sensor.h"
#include "serial.h"


#define LED_PWM_PERIOD 100 // Set in PWM blocks
#define MAX_TOUCHPAD_POS 100 // Setup in the advanced tab of capsense block. 

static bool print_counter_flag; // Global marker for when counter rdy to send

void led_counter_int_handler()  // Custom function for handling interrupts from print_counter
{
    Cy_TCPWM_ClearInterrupt(print_counter_HW, print_counter_CNT_NUM, CY_TCPWM_INT_ON_TC);
    //Cy_GPIO_Inv(redLed_PORT, redLed_NUM);
    print_counter_flag++;
}

void led_write_from_coord()
{
            int coord =  CapSense_GetXYCoordinates(CapSense_TOUCHPAD0_WDGT_ID);
            
            uint16_t xPos = (uint16_t)(coord & 0x00FF);
            uint16_t yPos = (uint16_t)(coord >> 16);
            
            uint32 xCompareValue = (xPos/65535)*LED_PWM_PERIOD;
            uint32 yCompareValue = (yPos/65535)*LED_PWM_PERIOD;
            
            Cy_TCPWM_PWM_SetCompare0(xPWM_HW, xPWM_CNT_NUM, xCompareValue);
            Cy_TCPWM_PWM_SetCompare0(yPWM_HW, yPWM_CNT_NUM, yCompareValue); 
}



void printf_counter_setup() 
{
    Cy_SysInt_Init(&counterInt_cfg, led_counter_int_handler);
    NVIC_EnableIRQ(counterInt_cfg.intrSrc); /* Enable the core interrupt */

    (void)Cy_TCPWM_Counter_Init(print_counter_HW, print_counter_CNT_NUM, &print_counter_config); 
    Cy_TCPWM_Enable_Multiple(print_counter_HW, print_counter_CNT_MASK); /* Enable the counter instance */

    Cy_TCPWM_TriggerStart(print_counter_HW, print_counter_CNT_MASK);
}

void i2c_setup()
{
        EZI2C_Start();
    EZI2C_SetBuffer1((uint8_t *)&CapSense_dsRam,
                        sizeof(CapSense_dsRam),
                        sizeof(CapSense_dsRam));
}

void capsense_setup()
{
    CapSense_Start();
    CapSense_InitializeAllBaselines();
    CapSense_ScanAllWidgets();
}







int main(void)
{
    __enable_irq(); /* Enable global interrupts. */

    struct response handshake_resp = create_new_response(MINIMUM_PACKET_BYTE_SIZE, 'a', 0);
    struct response matrix_dimensions_resp = create_new_response(3, 'd', MATRIX_DIMENSIONS_BYTE);    
    struct response taxels_data_resp = create_new_response(MATRIX_DATA_PACKET_BYTE_SIZE, 't', 0);
  
    uint32 taxel_raw_values[ROW_TAXELS_NB*COL_TAXELS_NB];

    

    bool sending_flag; // Marks when sending data or not
    sending_flag = 0;
    

    //uint curr_elem;     // Saves which sensor we are at now
    bool touchpad_readings_flag;    // Marks when all 25 sensors are read

    // Init code
    printf_counter_setup();
    UART_Start();
    setvbuf(stdin,NULL,_IONBF,0);  //This sets NO buffering for stdin
    i2c_setup();    
    capsense_setup();    
    // Capsense LED PWMs
    xPWM_Start();
    yPWM_Start();
    
    for(;;)
    {
            CapSense_ProcessAllWidgets(); // Process all widgets 
            CapSense_RunTuner();    // To sync with Tuner application           

            touchpad_readings_flag = get_taxel_raw_count_iterator(taxel_raw_values);

            //read_serial_for_incoming_requests();
            //printf(" fine\n\r");
            /*
            char received_char;
            if(touchpad_readings_flag) 
                {
                    
                    if (UART_GetNumInRxFifo() > 0) {
                           received_char = getchar();
                        printf("%c", received_char);
                        switch(received_char)
                        {
                        case '1':
                          Cy_GPIO_Inv(redLed_PORT, redLed_NUM);
                          sending_flag = 1;
                          break;
                        case '0':
                          Cy_GPIO_Inv(redLed_PORT, redLed_NUM);
                          sending_flag = 1;
                          break;       
                        case 'h':
                        break;
                        default:
                          break;
                        }    
                    }
                }
*/
            
            if (/*sending_flag &&*/ print_counter_flag && touchpad_readings_flag) 
            {
                print_counter_flag = 0;
                touchpad_readings_flag = 0;
                
                //send_response(handshake_resp);
                //send_response(matrix_dimensions_resp);
                send_data_response(taxels_data_resp, taxel_raw_values);
                
                printf("\r\n");
                //CyDelay(500);
                
                //debug instead:
                //putchar('M');
                //putchar('C');
                //p/utchar('a');
                //putchar('\n');
                //printf("%c", 'M');
                //printf("%c", 'C');
                //printf("%c", 'a');  // For raw counts
                //printf("%c", '\n');
                
                /*
                for (int i = 0; i < 25; i++)
                {
                    printf("\n");
                    printf("%c", 97 + i);
                    printf("%c", &taxel_raw_values[i] >> 8);
                    printf("%c", &taxel_raw_values[i] & 0x00ff);  // For raw counts
                    printf("\r");
                } */
                
            }       

            
            /* Start next scan */
            CapSense_UpdateAllBaselines();
            CapSense_ScanAllWidgets();
    }
}

/* [] END OF FILE */
