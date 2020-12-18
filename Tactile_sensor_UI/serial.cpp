#include "serial.h"

Serial::Serial()
{
    qDebug() << "serial created";

    serialTimer = new QTimer;

    serialBuffer = new QByteArray;
    serialBuffer->resize(1000);

    qDebug() << "start msg size: " << start_publishing_req.size;

    // Configure the serial port
    setBaudRate(QSerialPort::Baud115200);
    setDataBits(QSerialPort::Data8);
    setFlowControl(QSerialPort::NoFlowControl);
    setParity(QSerialPort::NoParity);
    setStopBits(QSerialPort::OneStop);


    //reading connects
    QObject::connect(this, SIGNAL(readyRead()), this, SLOT(serialRead()));
    QObject::connect(serialTimer, SIGNAL(timeout()), this, SLOT(serialRead()));

    //writing connects
    QObject::connect(this, SIGNAL(need_to_send_request(request)), this, SLOT(write_request(request)));
}

Serial::~Serial()
{
    delete serialTimer;
    delete serialBuffer;
    qDebug() << "serial destro";
}


void Serial::serialRead()
{
    if(!isOpen())
        return;

    //int resp_start_pos;
    int resp_length;
    //int resp_label;
    QByteArray complete_response_cleaned_msg;

    if(bytesAvailable() < 1)        // might not always be useful. still could clear buffer
        return;

    //qDebug() << "serial data is available in windows buffer!";
    //qDebug() << "reading all: " << this->readLine();

    serialBuffer->append(readAll());
    //qDebug() << serialBuffer->toHex();  //remet etoil
    //return;
    // Make sure buffer is not empty
    if (serialBuffer->count() < 3) {    // 1er start byte (txt ou data), 2e: longueur du msg  (JE DOIS AJOUTER CA)
        //qDebug() << "Buffer is empty";
        return;
    }

    // First byte
    if (serialBuffer->at(msg_sequence::pw_high_byte_pos) == (char)msg_added_bytes::password_h)  // both bytes should be checked in same if
    {
        //qDebug() << "pw high byte found";

    }
    else
    {
        clear_until_next_response();
        qDebug() << "pw high byte NOT found" << serialBuffer->toHex().at(msg_sequence::pw_high_byte_pos);
        return;
    }

    if (serialBuffer->at(msg_sequence::pw_low_byte_pos) == (char)msg_added_bytes::password_l)
    {
        //qDebug() << "pw full found";
        resp_length = serialBuffer->at(msg_sequence::length_pos);  // enlever le +3 quand psoc est arrange
        //qDebug() << resp_length;
    }

    else
    { // password was corrupted or incomplete
        qDebug() << "low byte pw corrupted or incomplete" << (char)serialBuffer->at(msg_sequence::pw_low_byte_pos);
        //qDebug() << serialBuffer->toHex();
        clear_until_next_response();
        return;
    }

    if (serialBuffer->count() < resp_length || resp_length == 0) {  // si size est 0, defensive code, et si pas comlet, return et attend complet
        qDebug() << "Not enough bytes in buffer:" << serialBuffer->count() << " < " << resp_length;
        return;
    }

    // Last byte    //avant de pogner le mssage, on check si le last byte est bon. sinon, tout est discarte
    if (serialBuffer->at(resp_length - 1) != (char)msg_added_bytes::end_char)
    {
        qDebug() << "Last byte is wrong: " << serialBuffer->at(resp_length - 1);
        clear_until_next_response();
        return;
    }

    // Extract valid message and remove it from buffer

    //resp_label = serialBuffer->at(msg_sequence::label_pos);
    //qDebug() << "msg label: " << resp_label;


    complete_response_cleaned_msg = serialBuffer->mid(msg_sequence::label_pos, resp_length - 1);
    qDebug() << "cleaned msg: " << complete_response_cleaned_msg;

    emit response_received(complete_response_cleaned_msg);

    clear_until_next_response(); // Erase until next response message
}



/*        validMessage = buffer.mid(3,size-4);
        buffer.remove(0,size);
        emit serialMessageReceived(QString(validMessage));
    }



    if(serialBuffer->count() < 4)
        return;

    if(serialBuffer->indexOf(msg_added_bytes::password_h) != -1)
    {
        qDebug() << "pw high byte found at " << serialBuffer->indexOf(msg_added_bytes::password_h);
        resp_start_pos = serialBuffer->indexOf(msg_added_bytes::password_h);
        serialBuffer->remove(0, resp_start_pos);
        qDebug() << "after removal: " << serialBuffer->indexOf(msg_added_bytes::password_h);
    }

    else
    {
        serialBuffer->clear();
        return;
    }

   // if (serialBuffer->count() < (RX_MSG_PASSWORD_BYTE_LENGTH + RX_MSG_TYPE_BYTE_LENGTH))
   //     return;

    if(serialBuffer->at(1) == msg_added_bytes::password_l)
    {
        qDebug() << "pw complete!";
        serialBuffer->remove(0, rxMsg_start_pos);
    }
    // else need to add a clear until next PW a bit just like above.

    int rxMsg_type = serialBuffer->at(2);

    emit response_received(rxMsg_type);
    qDebug() << "rxMsg type: " << rxMsg_type;

    //serialBuffer->clear(); //for debugging
}
*/

void Serial::clear_until_next_response()
{
    static int start_index;
    //bool complete_pw_flag;


    start_index = serialBuffer->indexOf(msg_added_bytes::password_h,1);
    /*  do
    {
        start_index = serialBuffer->indexOf(msg_added_bytes::password_h);

        if(start_index+1 == msg_added_bytes::password_l)
        {
            qDebug() << "Erased and next found at: " << start_index;
            complete_pw_flag = 1;
        }

        else if (start_index == -1)
        {
            qDebug() << "pw not found in buffer";
            return;
        }

        else
        {
            qDebug() << "could not complete pw: " << start_index;
            serialBuffer->remove(0, start_index+1);
        }


    } while(!complete_pw_flag);*/


    if (start_index == -1) // If pw not found, erase all buffer
        start_index = serialBuffer->size();

    serialBuffer->remove(0, start_index);
}




void Serial::write_request(request req)
{
    qDebug() << "sending a char: " << req.label;
    putChar(msg_added_bytes::password_l);
    putChar(msg_added_bytes::password_h);
    putChar(req.size);
    putChar(req.label);
    if(req.size > 2)       //if size is more than a label byte and an end byte
        putChar(req.value);
    putChar(msg_added_bytes::end_char);
}


void Serial::connect()
{
    open(QSerialPort::ReadWrite);
    clear();
    serialBuffer->clear();

    serialTimer->start(1);

    emit need_to_send_request(handshake_req);  //request handshake when attempting connect
}

void Serial::disconnect()
{
    close();
    serialTimer->stop();
    qDebug() << "serial closed";

}


