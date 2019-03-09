#ifndef LIFE_H
#define LIFE_H

#include <QWidget>
#include <QPaintEvent>

namespace Ui {
class life;
}

class life : public QWidget
{
    Q_OBJECT

public:
    explicit life(QWidget *parent = nullptr);
    ~life();

public slots:
    void nextGeneration(); //compute the next generation of the game
    void clear(); //clear the game world
    void randomize(); //randomize the game world

protected:
    void paintEvent(QPaintEvent *event); //the function for drawing the game

private:
    Ui::life *ui;
    static const size_t grid_sz = 50; //the max size of the widget
    static const size_t cell_sz = 10; //the size of a cell

    bool cells[grid_sz][grid_sz]; //the game world

    size_t getIndex(int c); //will take a coordinate and give the corresponding index of cells[][]
    int getCoord(int i); //will take an index of cells[][] and give the corresponding coordinate for drawing
};

#endif // LIFE_H
