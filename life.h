#ifndef LIFE_H
#define LIFE_H

#include <QWidget>
#include <QPaintEvent>
#include <QTimer>
#include <QKeyEvent>

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
    void clear(); //clear the game world
    void randomize(); //randomize the game world
    void nextGeneration(); //compute the next generation of the game

protected:
    void paintEvent(QPaintEvent *event); //the function for drawing the game
    void keyPressEvent(QKeyEvent *event); //will allow us to use keyboard input

private:
    Ui::life *ui;
    static const size_t max_sz = 100; //the max size of the widget
    static const size_t min_sz = 10; //the min size of the widget
    static const size_t cell_sz = 10; //the size of a cell when it is drawn
    //size_t border_x = max_sz; //to support resizing the window, we will keep track of the edges of the
    //size_t border_y = max_sz; //portion of the world being displayed

    bool cells[2][max_sz][max_sz]; //the game world
    //we need two layers to the array because we need to keep the current generation to calculate the next

    QTimer* timer; //the timer which will make the game run
    bool paused = false; //keep track of whether the game is paused

    size_t getIndex(int c); //will take a coordinate and give the corresponding index of cells[][]
    int getCoord(size_t i); //will take an index of cells[][] and give the corresponding coordinate for drawing
};

#endif // LIFE_H
