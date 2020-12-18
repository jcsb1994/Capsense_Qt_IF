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

#include "serial.h"

struct response create_new_response(uint8_t msg_size, char msg_label,uint8_t msg_value)
{
    struct response x;
    x.size = msg_size;
    x.label = msg_label;
    x.value = msg_value;
    return x;
}

void send_response(struct response resp)
{
    
    putchar(password_h);
    putchar(password_l);
    putchar(resp.size);
    //printf("%x", resp.size);
    putchar(resp.label);
    if(resp.value && resp.size > MINIMUM_PACKET_BYTE_SIZE)
      putchar(resp.value);  
    putchar(end_char);
}


void send_data_response(struct response resp, uint data[ROW_TAXELS_NB*COL_TAXELS_NB])
{
    putchar(password_h);
    putchar(password_l);
    putchar(resp.size);
    putchar(resp.label);
    
    for (int i = 0; i < (ROW_TAXELS_NB*COL_TAXELS_NB); i++)
     {
        printf("%x", (int)(data[i] >> 8));    // printf version works on putty
        printf("%x", (int)(data[i] & 0x00ff));
        //putchar((int)(data[i] >> 8));
        //putchar((int)(data[i] & 0x00ff));
     }
    
    putchar(end_char);
}


void read_serial_for_incoming_requests()
{
    /*Cy_SCB_UART_ClearRxFifo()
    
    char uart_buffer[whatever size]
    const unsigned char password[2] = "MC";
    UAR
    
    if (UART_GetNumInRxFifo() < 5)
    {
        printf("exited\r\n");
        return;
    }
    else
    {
        printf("enough\r\n");
    } */
    #define RING_BUFFER_SIZE     (32u)
    
    // For errors..
    cy_en_scb_uart_status_t uart_status; // Stores current status, possible options in the cy_en_scb_uart_status_t enum
    cy_en_sysint_status_t sysint_status;
    
    
    //uint8_t serial_uart_buffer[RING_BUFFER_SIZE+1];
    /*
    // context struct is used to make sure we stay in scope? something like while using UART...
    Cy_SCB_UART_StartRingBuffer(UART_HW, serial_uart_buffer, RING_BUFFER_SIZE, &UART_context);
    
    uint32_t array[5];
    uint32_t num;
    
    array[0] = UART_GetArray(serial_uart_buffer, 1);
    num = UART_GetNumInRxFifo();
    
    printf("arr: %d\r\n", array[0]);
    printf("num: %d\r\n", num);
    printf("size: %d\r\n", num);
    
    //int mike = UART_GetNumInTxFifo();
    //rxfifo is 128
    //printf("%d\r\n", mike);
    */
    //if (UART_GetNumInRxFifo() < 3)
    //    return;
    char received_char;
    char serial_uart_buffer[128];
    UART_GetArray(serial_uart_buffer, 2);
    printf("received char 1: %c\r\n", serial_uart_buffer[0]);
    printf("received char 2: %c\r\n", serial_uart_buffer[1]);
    
    /*
    for (uint32_t i = 0; i < UART_GetNumInRxFifo(); i ++)
    {
    serial_uart_buffer = getchar();
    printf("received char %d: %c\r\n", i, received_char);
    
    }
    printf("done\r\n\n\n\n");
    */
    
    
    /*
     = getchar();
    if (received_char == 'M')
        printf("received M: %c\r\n", received_char);
    
   received_char = getchar();
    if (received_char == 'M')
        printf("received C: %c\r\n", received_char);
        
        received_char = getchar();
    if (received_char == 5)
        printf("received 5: %c\r\n", received_char);
    */
    
                      /*  received_char = getchar();
                        printf("received: %c\r\n", received_char);
                        switch(received_char)
                        {
                        case '1':
                          Cy_GPIO_Inv(redLed_PORT, redLed_NUM);

                          break;
                        case '0':
                          Cy_GPIO_Inv(redLed_PORT, redLed_NUM);

                          break;       
                        case 'h':
                        break;
                        default:
                          break;
                        }*/
    
    
}


/* [] END OF FILE */
