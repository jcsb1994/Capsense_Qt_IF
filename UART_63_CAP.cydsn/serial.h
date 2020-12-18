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
#ifndef SERIAL_H
#define SERIAL_H

#include "project.h"
#include "stdio.h"
#include "matrix_config.h"


#define MINIMUM_PACKET_BYTE_SIZE 5  // PW (2 bytes), length, label and end bytes
#define MATRIX_DATA_PACKET_BYTE_SIZE (ROW_TAXELS_NB*COL_TAXELS_NB)*2 + MINIMUM_PACKET_BYTE_SIZE // minimum + 2 bytes per taxel

    
/*##########################################################################################
SERIAL ENUMS AND STRUCTS
    
msg_added_bytes
    This enum contains bytes used around the actual information
    when messages are exchanged between slave (device) and master (computer).
    
request
    Requests are messages from master to slave (Computer to PSoC).
    
response 
    Responses are messages from slave to master. All possible responses are created in
    main and can be sent with send_response(); described below.
    
##########################################################################################*/  
    
enum msg_added_bytes
{
       password_h = 'M',
       password_l = 'C', 
       end_char = '\n'
};

enum request   
{
    handshake = 'h',
    start_publishing = 'a',
    stop_publishing = 's',
};

struct response
{
 char size;
 char label;
 char value;
};


/*##########################################################################################
SERIAL FCTS
    
send_response
    Use predefined response struct instances to send responses to master.
    
send_data_response
    Only used for int data arrays (i.e. matrix raw counts) to send to master.
    
##########################################################################################*/

struct response create_new_response(uint8_t msg_size, char msg_label, uint8_t msg_value);

void send_response(struct response resp);

void send_data_response(struct response resp, uint data[ROW_TAXELS_NB*COL_TAXELS_NB]);    

// Reading functions

void read_serial_for_incoming_requests();

/* [] END OF FILE */
#endif // SERIAL_H