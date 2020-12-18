/*
Main window creates a separate window for operating sensors, sensor, and serial.
the sensor window can read from sensor to display data
serial gives data to sensor, sensor parses the data and holds data related to the sensor

Mainwindow talks to sensor:
changes serial com port, opens (readwrite) serial and closes it

sensorWindow talks to sensor:
gets data from sensor and puts them in LCDs
gets taxel nb from serial
gets row and col nb from serial. builds matrix in the sensorLayout

*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "launched_sensor_dialog.h"  // This dialog window is launched when device is connected
#include "sensor.h"         // MainWindow interfaces with the sensor class to show data on screen

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:       //tous les get/set
    // Add a fct for refreshing screen when refreshtimer is out
    // Add a fct for initial screen display
    // Add a fct for creating the lcd ui widgets

private slots:

    void on_pushButton_clicked(); // debug only

    QPalette palette_setup();

    void update_sensor_connection_status(char new_status);
    void lauch_sensor_window();
    void close_sensor_window();

private:
    Ui::MainWindow *ui;
    Sensor *mySensor;

    Launched_sensor_dialog *sensorWindow;
};

#endif // MAINWINDOW_H
