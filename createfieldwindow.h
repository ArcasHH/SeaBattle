#ifndef CREATEFIELDWINDOW_H
#define CREATEFIELDWINDOW_H

#include <QMainWindow>
#include "FieldCell.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CreateFieldWindow; }
class QPushButton;
QT_END_NAMESPACE

class CreateFieldWindow : public QMainWindow
{
    Q_OBJECT

public:
    CreateFieldWindow(QWidget *parent = nullptr);
    void generateButtons();
    ~CreateFieldWindow();
    int num4;
    int num3;
    int num2;
    int num1;

public slots:
    void buttonClicked();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_accept_clicked();

private:
    Ui::CreateFieldWindow *ui;

    FieldCell ** *ButtonField;


};
#endif // CREATEFIELDWINDOW_H
