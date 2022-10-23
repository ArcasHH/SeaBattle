#ifndef FIELDCELL_H
#define FIELDCELL_H

#include <QPushButton>
#include <QRadioButton>

struct FieldCell : public QPushButton {
    int x;
    int y;
    bool available;

public:
    FieldCell(int x_in, int y_in) : x{x_in}, y{y_in} {}
};

struct ShipDescription : public QRadioButton {
    int Size;
    int Count;
    ShipDescription(int Size_in) : Size{Size_in}, Count{5-Size} { updShip(); }

    void updShip() { setText("Length: " + QString::number(Size) + " Count: " + QString::number(Count));}
    void decreaseCount() { --Count; updShip(); }
    void restore() { Count = 5 - Size; updShip(); }
};

#endif // FIELDCELL_H
