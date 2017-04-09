#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // setup the app icon
    QPixmap iconImage;

    iconImage.load(":/images/groundstation_icon64.png");
    QIcon winIcon;
    winIcon.addPixmap(iconImage);
    this->setWindowIcon(winIcon);
    this->setWindowTitle("Ground Station");

    // status label initialization
    ui->motor1_valbar->setMinMax(800, 2000);
    ui->motor1_valbar->setLeftLabel("motor1");
    ui->motor1_valbar->setFromLeft(false);
    ui->motor1_valbar->setBarColor(QColor::fromRgb(255, 160, 128));

    ui->motor2_valbar->setMinMax(800, 2000);
    ui->motor2_valbar->setLeftLabel("motor2");
    ui->motor2_valbar->setFromLeft(true);
    ui->motor2_valbar->setBarColor(QColor::fromRgb(255, 160, 128));

    ui->motor3_valbar->setMinMax(800, 2000);
    ui->motor3_valbar->setLeftLabel("motor3");
    ui->motor3_valbar->setFromLeft(true);
    ui->motor3_valbar->setBarColor(QColor::fromRgb(255, 160, 128));

    ui->motor4_valbar->setMinMax(800, 2000);
    ui->motor4_valbar->setLeftLabel("motor4");
    ui->motor4_valbar->setFromLeft(false);
    ui->motor4_valbar->setBarColor(QColor::fromRgb(255, 160, 128));

    ui->ch5_valbar->setMinMax(800, 2000);
    ui->ch5_valbar->setLeftLabel("CH5");
    ui->ch5_valbar->setFromLeft(true);
    ui->ch5_valbar->setBarColor(QColor::fromRgb(255, 160, 128));

    ui->ch6_valbar->setMinMax(800, 2000);
    ui->ch6_valbar->setLeftLabel("CH6");
    ui->ch6_valbar->setFromLeft(true);
    ui->ch6_valbar->setBarColor(QColor::fromRgb(255, 160, 128));

    ui->ch7_valbar->setMinMax(800, 2000);
    ui->ch7_valbar->setLeftLabel("CH7");
    ui->ch7_valbar->setFromLeft(true);
    ui->ch7_valbar->setBarColor(QColor::fromRgb(255, 160, 128));

    ui->ch8_valbar->setMinMax(800, 2000);
    ui->ch8_valbar->setLeftLabel("CH8");
    ui->ch8_valbar->setFromLeft(true);
    ui->ch8_valbar->setBarColor(QColor::fromRgb(255, 160, 128));

    // status bar initialization
    labelStatus = new QLabel(this);
    labelVersion = new QLabel(this);

    labelStatus->setText("Status: not connected");
    labelStatus->setContentsMargins(5, 1, 5, 1);

    labelVersion->setText("Version 0.1");
    labelVersion->setContentsMargins(5, 1, 5, 1);

    ui->statusBar->addWidget(labelStatus, 1);
    ui->statusBar->addWidget(labelVersion, 1);





}

MainWindow::~MainWindow()
{
    delete ui;
}
