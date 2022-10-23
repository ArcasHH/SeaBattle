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

    num4 = 1;
    num3 = 2;
    num2 = 3;
    num1 = 4;
}

void CreateFieldWindow::generateButtons() {
    QGridLayout &Field = *ui->fieldGrid;

    ButtonField = new FieldCell**[10];
    for (int i = 0; i != 10; ++i)
        ButtonField[i] = new FieldCell*[10];

    for (int i = 0; i != 10; i++)
        for (int j = 0; j != 10; j++) {
            FieldCell *Btn = new FieldCell(i, j);
            Btn->setFixedSize(50, 50);
            Btn->setText(QString::number(i) + QString::number(j));
            Btn->setStyleSheet("background-color: grey");
            ButtonField[i][j] = Btn;
            Btn->available = true;
            Field.addWidget(Btn, i, j);
            connect(Btn, SIGNAL(clicked()), this, SLOT(buttonClicked()));
        }
}

void CreateFieldWindow::buttonClicked() {
    QObject *Sender = QObject::sender();
    FieldCell *Btn = static_cast<FieldCell*>(Sender);
    //qDebug() << "Pressed: " << Btn->x << ' ' << Btn->y;
    int size = 0;
    bool a = true;
    int i = Btn->x;
    int j = Btn->y;
    int num;

    //создай структуру Number_of_ships с int length и int amount/ num.length заменит size
                                                                  //amount будет содержать кол-во короблей, которые можно поставить
    if( ui->radioButton_4->isChecked()){
        size = 4;
        num = num4;
    }
    if( ui->radioButton_3->isChecked()){
        size = 3;
        num = num3;
    }
    if( ui->radioButton_2->isChecked()){
        size = 2;
        num = num2;
    }
    if( ui->radioButton_1->isChecked()){
        size = 1;
        num = num1;
    }

    if( (i + size > 10 && ui->radioButton_vertical->isChecked())
            || (j + size > 10 && ui->radioButton_gorizontal->isChecked()) || num <=0)//выход из функции
        return ;

    if(ui->radioButton_vertical->isChecked() && size != 0 && size > 0){
        for (int n = 0; n != size; n++) {
            if(!ButtonField[i+n][j]->available)
                a = false;
        }
        if(a){
            for (int n = 0; n != size; n++) {
                ButtonField[i+n][j]->setStyleSheet("background-color: red");
            }
            for (int n = -1; n != size+1; n++) {
                if(i + n >= 0){
                    if( j - 1 >= 0 && i + n <= 9)
                        ButtonField[i+n][j-1]->available = false;
                    if(i + n <= 9)
                        ButtonField[i+n][j]->available = false;
                    if( j + 1 <= 9 && i + n <= 9)
                        ButtonField[i+n][j+1]->available = false;
                }
            }
            num = num - 1;
        }
    }
    else if(ui->radioButton_gorizontal->isChecked()  && size != 0 && size > 0){
        bool a = true;

        for (int n = 0; n != size; n++) {
            if(!ButtonField[i][j+n]->available)
                a = false;
        }
        if(a){
            for (int n = 0; n != size; ++n) {
                ButtonField[i][j+n]->setStyleSheet("background-color: red");
                ButtonField[i][j+n]->available = false;
            }
            for (int n = -1; n != size+1; n++) {
                if(j + n >= 0){
                    if( i - 1 >= 0 && j + n <= 9)
                        ButtonField[i-1][j+n]->available = false;
                    if(j + n <= 9)
                        ButtonField[i][j+n]->available = false;
                    if( i + 1 <= 9 && j + n <= 9)
                        ButtonField[i+1][j+n]->available = false;
                }
            }
            num = num - 1;
        }
    }
    QString new_label;
    if( ui->radioButton_4->isChecked()){
        num4 = num;
        new_label = QString::number(num4, 'g', 20);
        ui->label_4->setText(new_label);
    }
    if( ui->radioButton_3->isChecked()){
        num3 = num;
        new_label = QString::number(num3, 'g', 20);
        ui->label_3->setText(new_label);
    }
    if( ui->radioButton_2->isChecked()){
        num2 = num;
        new_label = QString::number(num2, 'g', 20);
        ui->label_2->setText(new_label);
    }
    if( ui->radioButton_1->isChecked()){
        num1 = num;
        new_label = QString::number(num1, 'g', 20);
        ui->label_1->setText(new_label);
    }

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

void CreateFieldWindow::on_pushButton_clear_clicked()
{
    ui->label_accept->setText("");
    num4 = 1;
    num3 = 2;
    num2 = 3;
    num1 = 4;
    ui->label_4->setText(QString::number(num4, 'g', 20));
    ui->label_3->setText(QString::number(num3, 'g', 20));
    ui->label_2->setText(QString::number(num2, 'g', 20));
    ui->label_1->setText(QString::number(num1, 'g', 20));
    for (int i = 0; i != 10; ++i)
        for (int j = 0; j != 10; ++j){
             ButtonField[i][j]->setStyleSheet("background-color: grey");
             ButtonField[i][j]->available = true;
        }
}

void CreateFieldWindow::on_pushButton_exit_clicked(){
    close();
}

void CreateFieldWindow::on_pushButton_accept_clicked()
{
    if(num4 + num3 + num2 + num1 ==0)
        ui->label_accept->setText("УРА");//прописать другое окно
    else
        ui->label_accept->setText("НЕТЬ");//прописать предупреждение

}

