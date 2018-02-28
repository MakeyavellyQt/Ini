#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ini.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Ini::loadGeometry(this, "MainWindow");
    Ini::loadMenu(ui->menuBar, "MainWindow");
}

void MainWindow::closeEvent(QCloseEvent *)
{
    Ini::saveGeometry(this, "MainWindow");
    Ini::saveMenu(ui->menuBar, "MainWindow");
}

MainWindow::~MainWindow()
{
    delete ui;
}
