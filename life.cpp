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
            cells[current][i][j] = std::rand() % 2; //set the cell to a random value
            cells[current == 1 ? 0 : 1][i][j] = 0; //just make the next generation empty for now
        }
    }
}

void life::nextGeneration(){
    if(!paused){ //don't do anything if the game is paused
    for(size_t i = 0; i < max_sz; ++i){ //iterate over all the cells
        for(size_t j = 0; j < max_sz; ++j){
            int total = 0; //initialize a total count of the living neighbors

            //count the number of living neighbors
            if(cells[current][(i-1+max_sz)%max_sz][(j-1+max_sz)%max_sz]){ //we use these indexes to make the world wrap around at the edges
                ++total;
            }
            if(cells[current][(i-1+max_sz)%max_sz][(j+max_sz)%max_sz]){
                ++total;
            }
            if(cells[current][(i-1+max_sz)%max_sz][(j+1+max_sz)%max_sz]){
                ++total;
            }
            if(cells[current][(i+max_sz)%max_sz][(j-1+max_sz)%max_sz]){
                ++total;
            }
            if(cells[current][(i+max_sz)%max_sz][(j+1+max_sz)%max_sz]){
                ++total;
            }
            if(cells[current][(i+1+max_sz)%max_sz][(j-1+max_sz)%max_sz]){
                ++total;
            }
            if(cells[current][(i+1+max_sz)%max_sz][(j+max_sz)%max_sz]){
                ++total;
            }
            if(cells[current][(i+1+max_sz)%max_sz][(j+1+max_sz)%max_sz]){
                ++total;
            }

            if(cells[current][i][j]){ //if the current cell is living
                if((total != 2) && (total != 3)){ //apply the rules
                    cells[current == 1 ? 0 : 1][i][j] = 0; //edit the next generation
                }
            } else{ //the current cell is nonliving
                if(total == 3){ //apply the rules
                    cells[current == 1 ? 0 : 1][i][j] = 1; //edit the next generation
                }
            }
        }
    }

    //now that we have calculated the next generation, we will set the current generation to the next
    current = current == 1 ? 0 : 1;

    update(); //redraw the game
    }
}

void life::paintEvent(QPaintEvent *event){
    QPainter paint(this);
    QColor living_color(255, 191, 0); //r:255 g:191 b:0 gives amber
    QColor non_living_color(216, 118, 0); //r:216 g:118 b:0 gives dark orange
    for(size_t i = 0; i < max_sz; ++i){ //iterate over every cell
        for(size_t j = 0; j < max_sz; ++j){
            QRectF cell(getCoord(i), getCoord(j), cell_sz, cell_sz); //calculate the rectangle to fill for the cell
            if(cells[current][i][j]){ //if the cell is living
                paint.fillRect(cell, QBrush(living_color)); //paint living cells
            }
            else{ //the cell is not living
                paint.fillRect(cell, QBrush(non_living_color)); //paint nonliving cells
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

void life::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){ //if the left mouse button is pressed
        size_t i = getIndex(event->pos().x()); //get the indexes of the cell clicked on
        size_t j = getIndex(event->pos().y());
        cells[current][i][j] = !cells[current][i][j]; //change the state of the cell
        cells[current == 1 ? 0 : 1][i][j] = cells[(current+1)%2][i][j]; //also change it in the next generation to be sure
        update();
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
