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
    generateShipInfo();
    ui->radioButton_gorizontal->setChecked(true);
}

void CreateFieldWindow::generateShipInfo() {
    QVBoxLayout &ShipInfo = *ui->shipInfoLayout;

    int const Max = 4;
    for (int i = 0; i != Max; ++i) {
        ShipDescription *Ship = new ShipDescription(i+1);
        connect(Ship, SIGNAL(toggled(bool)), this, SLOT(shipSelected(bool)));
        ShipInfo.addWidget(Ship, i);
    }
}

void CreateFieldWindow::shipSelected(bool State) {
    QObject *Sender = QObject::sender();
    ShipDescription *Ship = static_cast<ShipDescription*>(Sender);
    if (State) {
        SelectedShip = Ship;
    }
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
            Btn->setStyleSheet("background-color: white");
            ButtonField[i][j] = Btn;
            Btn->available = true;
            Field.addWidget(Btn, i, j);
            connect(Btn, SIGNAL(clicked()), this, SLOT(buttonClicked()));
        }
}


bool CreateFieldWindow::checkConditions(int i, int j, int Size, bool IsHorizontal) {

    if (IsHorizontal) {
        for (int n = j; n != j + Size; ++n)
            if (!ButtonField[i][n]->available)
                return false;
    } else {
        for (int n = i; n != i + Size; ++n)
            if (!ButtonField[n][j]->available)
                return false;
    }
    return true;
}

void CreateFieldWindow::buttonClicked() {
    QObject *Sender = QObject::sender();
    FieldCell *Btn = static_cast<FieldCell*>(Sender);
    int i = Btn->x;
    int j = Btn->y;

    // If this cell is not available.
    if (!Btn->available)
        return;
    // If ship is not selected yet.
    if (!SelectedShip)
        return;
    // If there is no available ships.
    if (!SelectedShip->Count)
        return;

    int Size = SelectedShip->Size;

    bool IsHorizontal = ui->radioButton_gorizontal->isChecked();

    // If out of boundaries.
    if( (i + Size > 10 && !IsHorizontal)
            || (j + Size > 10 && IsHorizontal))
        return ;

    if (!checkConditions(i, j, Size, IsHorizontal))
        return;

    // Do drawing.
    SelectedShip->decreaseCount();
    if (IsHorizontal) {
        for (int n = j; n != j + Size; ++n)
            ButtonField[i][n]->setStyleSheet("background-color: red");
    } else {
        for (int n = i; n != i + Size; ++n)
            ButtonField[n][j]->setStyleSheet("background-color: red");
    }

    // Disable neighbour cells.
    if (IsHorizontal) {
        if (i != 0) {
            int start = j == 0 ?  j : j - 1;
            int end = (j+Size) == 10 ? j+Size : j+Size+1;
            for (int n = start; n != end; ++n) {
                ButtonField[i-1][n]->available = false;
                ButtonField[i-1][n]->setStyleSheet("background-color: grey");
            }
        }
        if (i != 9) {
            int start = j == 0 ?  j : j - 1;
            int end = (j+Size) == 10 ? j+Size : j+Size+1;
            for (int n = start; n != end; ++n) {
                ButtonField[i+1][n]->available = false;
                ButtonField[i+1][n]->setStyleSheet("background-color: grey");
            }
        }
        if (j != 0) {
            ButtonField[i][j-1]->available = false;
            ButtonField[i][j-1]->setStyleSheet("background-color: grey");
        }
        if (j+Size != 10) {
            ButtonField[i][j+Size]->available = false;
            ButtonField[i][j+Size]->setStyleSheet("background-color: grey");
        }
    } else {
        if (j != 0) {
            int start = i == 0 ?  i : i - 1;
            int end = (i+Size) == 10 ? i+Size : i+Size+1;
            for (int n = start; n != end; ++n) {
                ButtonField[n][j-1]->available = false;
                ButtonField[n][j-1]->setStyleSheet("background-color: grey");
            }
        }
        if (j != 9) {
            int start = i == 0 ?  i : i - 1;
            int end = (i+Size) == 10 ? i+Size : i+Size+1;
            for (int n = start; n != end; ++n) {
                ButtonField[n][j+1]->available = false;
                ButtonField[n][j+1]->setStyleSheet("background-color: grey");
            }
        }
        if (i != 0) {
            ButtonField[i-1][j]->available = false;
            ButtonField[i-1][j]->setStyleSheet("background-color: grey");
        }
        if (i+Size != 10) {
            ButtonField[i+Size][j]->available = false;
            ButtonField[i+Size][j]->setStyleSheet("background-color: grey");
        }
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
    for (int i = 0; i != 10; ++i)
        for (int j = 0; j != 10; ++j) {
            ButtonField[i][j]->setStyleSheet("background-color: white");
            ButtonField[i][j]->available = true;
        }
    QVBoxLayout &ShipInfo = *ui->shipInfoLayout;
    for (int i = 0; i != ShipInfo.count(); ++i) {
        QWidget *W = ShipInfo.itemAt(i)->widget();
        if (!W)
            qDebug() << "Strange null";
        else {
            ShipDescription* SD = static_cast<ShipDescription*>(W);
            SD->restore();
        }
    }
}

void CreateFieldWindow::on_pushButton_exit_clicked(){
    close();
}

void CreateFieldWindow::on_pushButton_accept_clicked()
{
    int AvShipsCount = 0;
    QVBoxLayout &ShipInfo = *ui->shipInfoLayout;
    for (int i = 0; i != ShipInfo.count(); ++i) {
        QWidget *W = ShipInfo.itemAt(i)->widget();
        if (!W)
            qDebug() << "Strange null";
        else {
            ShipDescription* SD = static_cast<ShipDescription*>(W);
            AvShipsCount += SD->Count;
        }
    }


    if(!AvShipsCount)
        ui->label_accept->setText("УРА");//прописать другое окно
    else
        ui->label_accept->setText("НЕТЬ");//прописать предупреждение

}

