#include "life.h"
#include "ui_life.h"

life::life(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::life)
{
    ui->setupUi(this);

    setMinimumSize(max_sz * cell_sz, max_sz * cell_sz); //set the min and max sizes of the widget
    setMaximumSize(max_sz * cell_sz, max_sz * cell_sz);
    setSizeIncrement(cell_sz, cell_sz); //the size of the window will increment by cell sizes

    randomize(); //randomize the cells

    resize(max_sz * cell_sz, max_sz * cell_sz); //set the size of the widget
}

void life::clear(){
    for(size_t i = 0; i < max_sz; ++i){ //iterate over all the cells
        for(size_t j = 0; j < max_sz; ++j){
            cells[i][j] = 0; //make each cell nonliving
        }
    }
}

void life::randomize(){
    std::srand(std::time(0)); //seed the random number generator
    for(size_t i = 0; i < max_sz; ++i){ //iterate over all the cells
        for(size_t j = 0; j < max_sz; ++j){
            cells[i][j] = std::rand() % 2; //set the cell to a random value
        }
    }
}

void life::nextGeneration(){
    for(size_t i = 0; i < max_sz; ++i){ //iterate over all the cells
        for(size_t j = 0; j < max_sz; ++j){
            int total = 0; //initialize a total count of the living neighbors

            //count the number of living neighbors
            if(cells[(i-1+max_sz)%max_sz][(j-1+max_sz)%max_sz]){ //we use these indexes to make the world wrap around at the edges
                ++total;
            }
            if(cells[(i-1+max_sz)%max_sz][(j+max_sz)%max_sz]){
                ++total;
            }
            if(cells[(i-1+max_sz)%max_sz][(j+1+max_sz)%max_sz]){
                ++total;
            }
            if(cells[(i+max_sz)%max_sz][(j-1+max_sz)%max_sz]){
                ++total;
            }
            if(cells[(i+max_sz)%max_sz][(j+1+max_sz)%max_sz]){
                ++total;
            }
            if(cells[(i+1+max_sz)%max_sz][(j-1+max_sz)%max_sz]){
                ++total;
            }
            if(cells[(i+1+max_sz)%max_sz][(j+max_sz)%max_sz]){
                ++total;
            }
            if(cells[(i+1+max_sz)%max_sz][(j+1+max_sz)%max_sz]){
                ++total;
            }

            if(cells[i][j]){ //if the current cell is living
                if((total != 2) && (total != 3)){ //apply the rules
                    cells[i][j] = 0;
                }
            } else{ //the current cell is nonliving
                if(total == 3){ //apply the rules
                    cells[i][j] = 1;
                }
            }
        }
    }
}

void life::paintEvent(QPaintEvent *event){
    QPainter paint(this);
    for(size_t i = 0; i < max_sz; ++i){ //iterate over every cell
        for(size_t j = 0; j < max_sz; ++j){
            QRectF cell(getCoord(i), getCoord(j), cell_sz, cell_sz); //calculate the rectangle to fill for the cell
            if(cells[i][j]){ //if the cell is living
                paint.fillRect(r, QBrush(255, 191, 0)); //r:255 g:191 b:0 gives amber
            }
            else{ //the cell is not living
                paint.fillRect(r, QBrush(136, 48, 0)); //r:136 g:48 b:0 gives dark amber
            }
        }
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
}
