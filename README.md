# Game-of-Life

## Contents

1. Description

2. Controls

3. Log



## 1. Description

This is an implementation of Conway's Game of Life using C++ and Qt. Conway's Game of Life is one of the most famous examples of a cellular automaton.
It was devised in 1970 by John Horton Conway. It consists of a rectangular grid of cells which may each exist in one of two states, which are commonly
described as living and nonliving. For any particular cell, the cell's neighborhood is defined to be the eight cells immediately surrounding that cell
in the grid. Given a particular arrangement of cells, the next generation of the game is calculated as follows: every living cell which has exactly
two or three living neighbors will remain living. A living cell with less than two or more than three living neighbors will become nonliving. A nonliving
cell with exactly three living neighbors will become living. A nonliving cell which does not have exactly three living neighbors will remain nonliving.
In my implementation, the edges of the grid are stitched together to form a toroidal array, so that a pattern which progresses past one edge will reappear
from the opposite edge.
For more information about Conway's Game of Life, here is a link to the Wikipedia page: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life



## 2. Controls

* Press 'R' to reset the game to a random state

* Press 'C' to clear the game to a blank state

* Press the spacebar to pause/unpause the game

* Click on a cell to change its state



## 3. Log

### 3/8/19
My plan is to make an implementation of Conway's Game of Life (Wikipedia Link: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) in Qt.
Some things I had to think about were how I would draw the cells, and how I would make the game and the graphics update periodically.
In order to learn about these topics, I looked at the Qt example on timers (link: https://doc.qt.io/archives/qt-4.8/timers.html) and the 
analog clock example (link: https://doc.qt.io/archives/qt-4.8/qt-widgets-analogclock-example.html). My plan had originally been to have
a widget which would display the game as well as some buttons at the bottom for resetting the game and displaying some example patterns.
However, I think it would look better without the buttons, so my plan is as follows:
I will create a widget to display the game. I will use the paintEvent function to draw the graphics, and a timer to make the game update
periodically. Additionally, I will make it so that you can press certain buttons on the keyboard to do things like reset the game,
clear the game world, and pause/unpause the game. On top of this, I will make it so that you can place and remove cells by clicking on them.

### 3/11/19
Last time I fleshed out much of the header file. Today I implemented the functions declared so far in the header. Among those were functions
for randomizing the world, clearing it (killing all the cells), computing the next generation, drawing the game to the screen, and a few helper
functions for getting screen coordinates from cell indices and vice versa. In order to define the paintEvent function for drawing to the screen,
I had to look at the documentation for QPaintEvent (https://doc.qt.io/qt-5/qpaintevent.html), QPainter (https://doc.qt.io/qt-5/qpainter.html), 
QBrush (https://doc.qt.io/archives/qt-4.8/qbrush.html), and the Basic Drawing Example (https://doc.qt.io/qt-5/qtwidgets-painting-basicdrawing-example.html).
From these resources, I was able to figure out how to define my paintEvent function. I did it by iterating over every cell and drawing a colored
rectangle at the screen coordinates corresponding to that cell. I faced a bug while working with this paintEvent function due to the fact that
I was confusing QPaint with QBrush, and thus passing the wrong parameter to the fillRect function. Once I had defined these functions, I needed
to set up the timer to make the game update periodically. I had to read some of the documentation on timers (https://doc.qt.io/archives/qt-4.8/timers.html).
Once I got the timer working, I saw that the game was not behaving properly. My first thought was that I may have made a mistake in defining the rules
of the game, but this did not appear to be the case. I realized that my problem was that I was updating the game world while calculating the next generation.
In order to properly compute the next generation of the game, I needed to keep the current generation unchanged and have a separate array which I would
update by applying the rules to each cell in the current generation. In order to implement this, I changed the game world from a two dimensional array to a
three dimensional array, where the third dimension would allow me to have two arrays, one of which would serve as the 'canvas' onto which I would compute
the next generation and then swap with the other array. After fixing that, the game was behaving properly. The next step is to set up the user
input. I intend to make it so that the user can press keys on the keyboard to clear the world, randomize the world, and pause/unpause the game.
Additionally, they will be able to click on cells on the screen to change their state.

### 3/13/19
Today I focused on implementing the user input features. Among these were the ability to press 'C' to clear the game, 'R' to reset it, spacebar
to pause/unpause it, and the ability to click on a cell to change its state. I started with the keyboard input. In order to learn about getting
keyboard input in Qt, I looked at the documentation on QKeyEvent (https://doc.qt.io/qt-5/qkeyevent.html). I learned I could define a keyPressEvent
function which I could use to check when a key is pressed and what the identity of the key pressed is, and define the game's behavior accordingly.
There was a minor bug where I used event->key instead of event->key() to get the identity of the key being pressed. Once the keyboard input was
working, I moved on to implementing the mouse features. I started by reading the Qt documentation on Mouse Events (https://doc.qt.io/qt-5/qtquick-input-mouseevents.html).
From this I gathered I could define a mousePressEvent function which behaved very similarly to the keyPressEvent function. My mousePressEvent
function gets the coordinates where the left mouse button is pressed and converts those into indices for the cells array in the game, and
adjusts the value of the cell at that location. A subtle bug I experienced with this was that changing the value of the cell in only the current
generation, not the next, could lead the game to behave incorrectly. This was easily fixed by making it so that the cell's state is changed in both
the current and the next generation of the game. After this, I changed the colors of the game a bit to a scheme which I found more aesthetically pleasing.
