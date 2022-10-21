#include "createfieldwindow.h"
#include "ui_createfieldwindow.h"

#include <QPushButton>
#include <QDebug>

CreateFieldWindow::CreateFieldWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CreateFieldWindow)
{
    ui->setupUi(this);

    generateButtons();
}

void CreateFieldWindow::generateButtons() {


    QGridLayout &Field = *ui->fieldGrid;

    ButtonField = new QPushButton**[10];
    for (int i = 0; i != 10; ++i)
        ButtonField[i] = new QPushButton*[10];

    for (int i = 0; i != 10; ++i)
        for (int j = 0; j != 10; ++j) {
            QPushButton *Btn = new QPushButton;
            Btn->setFixedSize(50, 50);
            Btn->setText(QString::number(i) + ' ' + QString::number(j));
            ButtonField[i][j] = Btn;
            Field.addWidget(Btn, i, j);
            connect(Btn, SIGNAL(clicked()), this, SLOT(buttonClicked()));
        }
}

//TODO create smth to change color by click.
void CreateFieldWindow::buttonClicked() {
    QObject *Sender = QObject::sender();
    QPushButton *Btn = static_cast<QPushButton*>(Sender);

    Btn->setStyleSheet("background-color: red");
}

CreateFieldWindow::~CreateFieldWindow()
{
    for (int i = 0; i != 10; ++i)
        for (int j = 0; j != 10; ++j)
            delete ButtonField[i][j];

    for (int i = 0; i != 10; ++i)
        delete[] ButtonField[i];
    delete[] ButtonField;

    delete ui;
}

