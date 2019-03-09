# Game-of-Life

## 3/8/19
My plan is to make an implementation of Conway's Game of Life (Wikipedia Link: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) in Qt.
Some things I had to think about were how I would draw the cells, and how I would make the game and the graphics update periodically.
In order to learn about these topics, I looked at the Qt example on timers (link: https://doc.qt.io/archives/qt-4.8/timers.html) and the 
analog clock example (link: https://doc.qt.io/archives/qt-4.8/qt-widgets-analogclock-example.html). My plan had originally been to have
a widget which would display the game as well as some buttons at the bottom for resetting the game and displaying some example patterns.
However, I think it would look better without the buttons, so my plan is as follows:
I will create a widget to display the game. I will use the paintEvent function to draw the graphics, and a timer to make the game update
periodically. Additionally, I will make it so that you can press certain buttons on the keyboard to do things like reset the game,
clear the game world, and pause/unpause the game. On top of this, I will make it so that you can place and remove cells by clicking on them.
