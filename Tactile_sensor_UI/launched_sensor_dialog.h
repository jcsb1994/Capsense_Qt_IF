#ifndef LAUNCHED_SENSOR_DIALOG_H
#define LAUNCHED_SENSOR_DIALOG_H

#include <QDialog>
#include <QDebug>

#include "sensor.h" // The sensor dialog interfaces with sensor to get data and print it

#include "taxel_lcd.h"  // uses taxel LCDs to generate the UI

namespace Ui {
class Launched_sensor_dialog;
}

class Launched_sensor_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Launched_sensor_dialog(Sensor *sensor, QWidget *parent = nullptr);
    ~Launched_sensor_dialog();

public slots:
    void launch();

private slots:
    void generateLCDs();
    void on_Launched_sensor_dialog_rejected();

private:
    Ui::Launched_sensor_dialog *ui;
    Sensor *pMainSensor;
    Taxel_LCD *myLCDs;
    QTimer *uiRefreshTimer;
};

#endif // LAUNCHED_SENSOR_DIALOG_H
