#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <QFile>
#include <QMessageBox>
/*#define PROCPATH "/proc/calc/"
#define SYSPATH "/sys/class/calc/"
#define FILESYSTEM SYSPATH */
#define FILE1 "/sys/class/calc/fnum"
#define FILE2 "/sys/class/calc/snum"
#define FILE3 "/sys/class/calc/operation"
#define FILE4 "/sys/class/calc/result"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    const char *num1, *num2;
    char *buf, res[6];
    QString oper;

    QFile num1f(FILE1);
    if (!num1f.open(QIODevice::WriteOnly)) {
        QMessageBox mbox;
        mbox.setText("Ошибка при открытии файла");
        mbox.exec();;
    }

    QFile num2f(FILE2);
    if (!num2f.open(QIODevice::WriteOnly)) {
        QMessageBox mbox;
        mbox.setText("Ошибка при открытии файла");
        mbox.exec();;
    }

    QFile operf(FILE3);
    if (!operf.open(QIODevice::WriteOnly)) {
        QMessageBox mbox;
        mbox.setText("Ошибка при открытии файла");
        mbox.exec();;
    }

    QFile resf(FILE4);
    if (!resf.open(QIODevice::ReadOnly)) {
        QMessageBox mbox;
        mbox.setText("Ошибка при открытии файла");
        mbox.exec();;
    }

    num1 = ui->lineEdit->text().toStdString().c_str();
    num2 = ui->lineEdit_2->text().toStdString().c_str();

    if (ui->sum->isChecked())
        oper = "sum";
    if (ui->sub->isChecked())
        oper = "sub";
    if (ui->mul->isChecked())
        oper = "mul";
    if (ui->div->isChecked())
        oper = "div";

    num1f.write(num1, strlen(num1));
    num2f.write(num2, strlen(num2));
    buf = oper.toLocal8Bit().data();
    operf.write(buf, strlen(buf));

    num1f.close();
    num2f.close();
    operf.close();

    resf.read(res, sizeof(res));
    ui->label_4->setText(res);
    resf.close();
}
