#include "life.h"
#include "ui_life.h"
#include <QPainter>
#include <ctime>

life::life(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::life),
    timer(new QTimer(this)) //initialize the timer
{
    ui->setupUi(this);

    setMinimumSize(max_sz * cell_sz, max_sz * cell_sz); //set the min and max sizes of the widget
    setMaximumSize(max_sz * cell_sz, max_sz * cell_sz);
    setSizeIncrement(cell_sz, cell_sz); //the size of the window will increment by cell sizes

    randomize(); //randomize the cells

    connect(timer, SIGNAL(timeout()), this, SLOT(nextGeneration())); //connect the timer to the nextGeneration function

    resize(max_sz * cell_sz, max_sz * cell_sz); //set the size of the widget

    timer->start(100); //update 10 times per second
}

void life::clear(){
    for(size_t i = 0; i < max_sz; ++i){ //iterate over all the cells
        for(size_t j = 0; j < max_sz; ++j){
            cells[0][i][j] = 0; //make each cell nonliving
            cells[1][i][j] = 0;
        }
    }
}

void life::randomize(){
    std::srand(std::time(0)); //seed the random number generator
    for(size_t i = 0; i < max_sz; ++i){ //iterate over all the cells
        for(size_t j = 0; j < max_sz; ++j){
            cells[0][i][j] = std::rand() % 2; //set the cell to a random value
            cells[1][i][j] = 0; //just make the next generation empty for now
        }
    }
}

void life::nextGeneration(){
    if(!paused){ //don't do anything if the game is paused
    for(size_t i = 0; i < max_sz; ++i){ //iterate over all the cells
        for(size_t j = 0; j < max_sz; ++j){
            int total = 0; //initialize a total count of the living neighbors

            //count the number of living neighbors
            if(cells[0][(i-1+max_sz)%max_sz][(j-1+max_sz)%max_sz]){ //we use these indexes to make the world wrap around at the edges
                ++total;
            }
            if(cells[0][(i-1+max_sz)%max_sz][(j+max_sz)%max_sz]){
                ++total;
            }
            if(cells[0][(i-1+max_sz)%max_sz][(j+1+max_sz)%max_sz]){
                ++total;
            }
            if(cells[0][(i+max_sz)%max_sz][(j-1+max_sz)%max_sz]){
                ++total;
            }
            if(cells[0][(i+max_sz)%max_sz][(j+1+max_sz)%max_sz]){
                ++total;
            }
            if(cells[0][(i+1+max_sz)%max_sz][(j-1+max_sz)%max_sz]){
                ++total;
            }
            if(cells[0][(i+1+max_sz)%max_sz][(j+max_sz)%max_sz]){
                ++total;
            }
            if(cells[0][(i+1+max_sz)%max_sz][(j+1+max_sz)%max_sz]){
                ++total;
            }

            if(cells[0][i][j]){ //if the current cell is living
                if((total != 2) && (total != 3)){ //apply the rules
                    cells[1][i][j] = 0;
                }
            } else{ //the current cell is nonliving
                if(total == 3){ //apply the rules
                    cells[1][i][j] = 1;
                }
            }
        }
    }

    //now that we have calculated the next generation, we will set the current generation to the next
    for(size_t i = 0; i < max_sz; ++i){ //iterate over all the cells
        for(size_t j = 0; j < max_sz; ++j){
            cells[0][i][j] = cells[1][i][j]; //set the current generation to the next
        }
    }

    update(); //redraw the game
    }
}

void life::paintEvent(QPaintEvent *event){
    QPainter paint(this);
    QColor amber(255, 191, 0); //r:255 g:191 b:0 gives amber
    QColor dark_amber(136, 48, 0); //r:136 g:48 b:0 gives dark amber
    for(size_t i = 0; i < max_sz; ++i){ //iterate over every cell
        for(size_t j = 0; j < max_sz; ++j){
            QRectF cell(getCoord(i), getCoord(j), cell_sz, cell_sz); //calculate the rectangle to fill for the cell
            if(cells[0][i][j]){ //if the cell is living
                paint.fillRect(cell, QBrush(amber)); //paint living cells amber
            }
            else{ //the cell is not living
                paint.fillRect(cell, QBrush(dark_amber)); //paint nonliving cells dark amber
            }
        }
    }
}

void life::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_R){ //if the R key is pressed
        randomize(); //randomize the world
        update(); //redraw
    }
    if(event->key() == Qt::Key_C){ //if the C key is pressed
        clear(); //clear the world
        update(); //redraw
    }
    if(event->key() == Qt::Key_Space){ //if the spacebar is pressed
        paused = !paused; //change the value of paused
    }
}

size_t life::getIndex(int c){
    return (size_t) c / cell_sz; //compute the index corresponding to the given coordinate
}

int life::getCoord(size_t i){
    return (int) i * cell_sz; //compute the screen coordinate for the given index
}

life::~life()
{
    delete ui;
    delete timer; //must deallocate the memory for the timer
}
