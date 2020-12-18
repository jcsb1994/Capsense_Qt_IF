/* ========================================
 *
 * Keywords
 *
 * Sensor = slave = PSoC device
 *
 * ========================================
*/

#ifndef SENSOR_H
#define SENSOR_H

#include "serial.h"  // Sensor operates with Serial to receive data
#include <QDebug>
#include <QTimer>
#include <QString>


/*##########################################################################################
SENSOR COMMUNICATION ENUMs

sensor_connection_status
    Lists possible connection status between master and slave.  Diffrent status
    changes display of the main window UI.

response
    All the response types are given by the label byte in incoming response messages

##########################################################################################*/

enum sensor_connection_status
{
    not_connected,  // Initial state at start of program
    connected,
    disconnected,
    sensor_window_launched
};

enum response
{
    connection_attempt_successful = 'a',
    matrix_dimensions = 'd',
    taxels_data = 't'

};


class Sensor : public QObject       // All QT classes should inherit from a QObject
{
    Q_OBJECT

public:
    Sensor();
    ~Sensor();



public slots:

    /*##########################################################################################
    SERIAL CONNECTION SLOTS (controlled by mainwindow widgets)

    connectToDevice()
    opens the serial comm and sends a txMsg to the COM device. a reply is needed for the
    connection to be marked as succesful

    disconnectDevice()
    closes serial. Called when disconnect button is pressed.

    changeComPort()


    ##########################################################################################*/

    void connect();     // connects to sensor
    void disconnect();    // disconnects the sensor communication
    void changeComPort(const QString& com);


    /*##########################################################################################
    RX SLOTS

    parse_sensor_rxMsg()
    parsing rx msgs when received by serial and serial emits a signal with the msg received

    ##########################################################################################*/

    void parse_sensor_response(QByteArray cleaned_resp);


    /*##########################################################################################
    GET/SET SLOTS

    ##########################################################################################*/

    void setTaxelNb(const int nb)   {taxelNb = nb;}
    int getTaxelNb()                {return taxelNb;}

    void setRowNb(const int nb)     {rowTaxNb = nb;}
    int getRowNb()                  {return rowTaxNb;}

    void setColNb(const int nb)     {colTaxNb = nb;}
    int getColNb()                  {return colTaxNb;}


    /*##########################################################################################
    SIGNALS

    connection_status_change_required()


    ##########################################################################################*/

signals:
    void connection_status_change_required(char);


private:
    Serial *mySerial;

    //int sensorConnectionStatus;

    int rowTaxNb = 3;
    int colTaxNb = 4;
    int taxelNb =12;
    int sensorReadings[25]; // should be nothing in brackets
};

#endif // SENSOR_H
