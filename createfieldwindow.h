#ifndef CREATEFIELDWINDOW_H
#define CREATEFIELDWINDOW_H

#include <QMainWindow>

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

public slots:
    void buttonClicked();

private:
    Ui::CreateFieldWindow *ui;

    QPushButton ** *ButtonField;


};
#endif // CREATEFIELDWINDOW_H
