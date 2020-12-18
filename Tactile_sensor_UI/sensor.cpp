#include "sensor.h"


Sensor::Sensor()
{
    mySerial = new Serial();
    qDebug() << "sensor created";
    qDebug() << "pw: " << bin << UART_PASSWORD;

    QObject::connect(mySerial, SIGNAL(response_received(QByteArray)), this, SLOT(parse_sensor_response(QByteArray)));
}

Sensor::~Sensor()
{
    delete mySerial;
     qDebug() << "sensor destro";
}




void Sensor::connect()
{
    mySerial->connect();
    // No signal emitted yet, Need to wait for successful attempt response from slave first.
}

void Sensor::disconnect()
{
    mySerial->disconnect();
    emit connection_status_change_required(sensor_connection_status::disconnected);
}

void Sensor::changeComPort(const QString& com)
{
    qDebug() << "old port: " << mySerial->portName();
    QString comPort = "COM" + com;
    mySerial->setPortName(comPort);
    qDebug() << "new port: " << mySerial->portName();
}




void Sensor::parse_sensor_response(QByteArray cleaned_resp)
{
    switch (cleaned_resp.at(0))
    {
    case response::connection_attempt_successful:
        qDebug() << "connection successful!";
        emit connection_status_change_required(sensor_connection_status::connected);

        break;

    default:
        break;
    }
}




