#include "launched_sensor_dialog.h"
#include "ui_launched_sensor_dialog.h"

Launched_sensor_dialog::Launched_sensor_dialog(Sensor *sensor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Launched_sensor_dialog),
    pMainSensor(sensor)
{
    ui->setupUi(this);
    //this->setStyleSheet("background-color: lightGray;");

    uiRefreshTimer = new QTimer(this);
    connect(uiRefreshTimer, SIGNAL(timeout()), this, SLOT(REFRESHSCREEN()));

}


Launched_sensor_dialog::~Launched_sensor_dialog()
{
    delete ui;
        delete uiRefreshTimer;
}

void Launched_sensor_dialog::launch()
{
    //hide(); //will hide mainw when lauched
    this->show();

}

void Launched_sensor_dialog::generateLCDs()
{
    myLCDs = new Taxel_LCD[pMainSensor->getTaxelNb()];

    int Tcounter = 0;
    for(int i = 0; i < pMainSensor->getRowNb(); i++)
    {
        for(int j = 0; j < pMainSensor->getColNb(); j++)
        {
            ui->sensorLayout->addWidget(&myLCDs[Tcounter], j, i);
            Tcounter++;
            qDebug() << Tcounter << "is" << i << "and" << j;
        }
    }

}

void Launched_sensor_dialog::on_Launched_sensor_dialog_rejected()
{
    qDebug() << "rejected";
    delete [] myLCDs;
}
