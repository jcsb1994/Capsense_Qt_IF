#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QPalette>
#include <QColor>

#include <QSignalMapper>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Main Window
    ui->setupUi(this);

    QPalette pal = palette_setup();
    this->setPalette(pal);
    ui->connect_button->setPalette(pal);

    update_sensor_connection_status(sensor_connection_status::not_connected);


    // Sensor (interfacing between the UI windows and serial data)
    mySensor = new Sensor;

    // sensor window
    sensorWindow = new Launched_sensor_dialog(mySensor, this);
    sensorWindow->setPalette(pal);
    connect(ui->launch_button, SIGNAL(clicked()),this, SLOT(lauch_sensor_window()));
    connect(sensorWindow, SIGNAL(rejected()), this, SLOT(close_sensor_window()));
//tjrs garder en tete si ce qui est dans le slot peut tre split en + slots pr etre utilises independamment



    // Timers


    // Serial
    connect(ui->connect_button, SIGNAL(clicked()), mySensor, SLOT(connect()));
    connect(ui->disconn_button, SIGNAL(clicked()), mySensor, SLOT(disconnect()));


    connect(ui->launch_button, SIGNAL(clicked()), sensorWindow, SLOT(generateLCDs()));


    connect(ui->com_spinBox, SIGNAL(valueChanged(QString)), mySensor, SLOT(changeComPort(const QString&)));

    /*
    QSignalMapper* msgSignalMapper = new QSignalMapper (this) ;
    connect(ui->connect_button, SIGNAL(clicked()), msgSignalMapper, SLOT(map()));
    connect(ui->launch_button, SIGNAL(clicked()), msgSignalMapper, SLOT(map()));
    msgSignalMapper -> setMapping (ui->connect_button, start_publishing_msg) ;
    msgSignalMapper -> setMapping (ui->launch_button, stop_publishing_msg) ;
    connect(msgSignalMapper, SIGNAL(mapped(int)), mySensor, SLOT(sendToDevice(int)));
    */


    connect(mySensor, SIGNAL(connection_status_change_required(char)),
            this, SLOT(update_sensor_connection_status(char)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mySensor;

    delete sensorWindow;
}


// ajouter une var privee a sensor pr garder statut.
//associer mon enum dans public de sensor
//quand statut change emit et main peut changer ui
void MainWindow::update_sensor_connection_status(char new_status)
{
    switch (new_status)
    {
    case sensor_connection_status::not_connected:
        ui->connect_button->setEnabled(true);
        ui->disconn_button->setEnabled(false);
        ui->launch_button->setEnabled(false);
        ui->conn_status_label->setText("Not connected");
        break;
    case sensor_connection_status::connected:
        ui->connect_button->setEnabled(false);
        ui->disconn_button->setEnabled(true);
        ui->launch_button->setEnabled(true);
        ui->conn_status_label->setText("Connected");
        break;
    case sensor_connection_status::disconnected:
        ui->connect_button->setEnabled(true);
        ui->disconn_button->setEnabled(false);
        ui->launch_button->setEnabled(false);
        ui->conn_status_label->setText("Disconnected");
        break;
    case sensor_connection_status::sensor_window_launched:
        ui->connect_button->setEnabled(false);
        ui->disconn_button->setEnabled(false);
        ui->launch_button->setEnabled(false);
        ui->conn_status_label->setText("Sensor window opened");
        break;
    default:
        break;
    }
}


QPalette MainWindow::palette_setup()
{
    // Style test
    //this->setStyleSheet("background-color: yellow;");
    QPalette pal = palette();
    QColor col = QColor(200,100,100,255);
    pal.setColor(QPalette::Background, col);
    pal.setColor(QPalette::Button, col);
    return pal;
}


void MainWindow::lauch_sensor_window()
{
    sensorWindow->launch();
    update_sensor_connection_status(sensor_connection_status::sensor_window_launched);
}

void MainWindow::close_sensor_window()
{
    update_sensor_connection_status(sensor_connection_status::connected);
}


// debug
void MainWindow::on_pushButton_clicked()
{
    //mySensor->parse_sensor_response(response::connection_attempt_successful);
}
