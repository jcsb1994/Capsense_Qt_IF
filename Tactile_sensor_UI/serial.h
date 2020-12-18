/* ========================================
 *
 * Keywords
 *  Message (msg): a set of bytes sent from slave or master to be read by the other
 *  Request (req): a message from master to slave
 *  Response (resp): a message from slave to master
 *  password: begins every message in this system. composed of 2 bytes: 'M' and 'C'
 *  label: unique identifier for messages. They tell the system what the message is about.
 *
 *
 * Msg sequence is:
 *  password
 *  msg length in bytes (password not counted)
 *  msg char label
 *  value (if any)
 *  end char (\n)
 *
 * ========================================
*/

#ifndef SERIAL_H
#define SERIAL_H


#include <QDebug>

#include <stdint.h>
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDateTime>
#include <QTimer>
#include <QByteArray>
#include <QThread>

#include <QString>

// 2-byte Password (MC) before messages are transfered
#define UART_PASSWORD ('M' << 8) + 'C'

#define RX_MSG_PASSWORD_BYTE_LENGTH 2
#define RX_MSG_TYPE_BYTE_LENGTH 1

#define MINIMUM_PACKET_BYTE_SIZE 5 // PW (2 bytes), length, label and end bytes

/*##########################################################################################
SERIAL ENUMs

msg_sequence
    Lists the meaning of all bytes contained in a message, in order

msg_added_bytes
    This enum contains bytes used around the actual information
    when messages are exchanged between slave (device) and master (computer).

request
    Messages from master (computer) to slave (PSoC).

response
    Lists all messages that can be received from the connected COM device. data is parsed by Sensor afterwards.

##########################################################################################*/

enum msg_sequence
{
    pw_high_byte_pos,
    pw_low_byte_pos,
    length_pos,
    label_pos,
    value_or_data_or_end_pos    // Is determined with the msg length value!
};

enum msg_added_bytes
{
    password_h = 'M',
    password_l = 'C',
    end_char = '\n'
};

struct request
{
    uint8_t size;
    char label;
    uint8_t value;
};






class Serial : public QSerialPort
{
    Q_OBJECT

public:
    Serial();
    ~Serial();


public slots:

    /*##########################################################################################
    INTERFACE SLOTS (serial doesnt decide when to call those)



    ##########################################################################################*/
    void connect();
    void disconnect();

private slots:

    /*##########################################################################################
    READ SLOTS

    serialRead()
    stores reveived bytes from comport in qbytearray buffer.
    Reads password and isolates rxMsg too (parsed after in sensor signal slot)

    ##########################################################################################*/

    void serialRead();
    // void clearUntilNextMsg(); // wait until reaches msg end char (\n) or new password (M)
    void clear_until_next_response();

    /*##########################################################################################
    WRITE SLOTS

    write_txMsg
    sends a char msg along with the password and end char

    ##########################################################################################*/

    void write_request(request req);
    // void readPassword();   //in serial read, either look for password or msg
    // void readMsg();
    // void readTaxelData();  // when msg is 'T', wait for data


signals:
    void need_to_send_request(request req);
    void response_received(QByteArray complete_response_meaningful_bytes);


private:
    QTimer *serialTimer;
    QByteArray *serialBuffer;

    request handshake_req = {MINIMUM_PACKET_BYTE_SIZE, 'h', 0};
    request start_publishing_req = {MINIMUM_PACKET_BYTE_SIZE, 'a', 0};
    request stop_publishing_req = {MINIMUM_PACKET_BYTE_SIZE, 's', 0};


};

#endif // SERIAL_H
