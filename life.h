#ifndef LIFE_H
#define LIFE_H

#include <QWidget>

namespace Ui {
class life;
}

class life : public QWidget
{
    Q_OBJECT

public:
    explicit life(QWidget *parent = nullptr);
    ~life();

private:
    Ui::life *ui;
};

#endif // LIFE_H
