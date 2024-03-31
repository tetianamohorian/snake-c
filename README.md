# Snake
### 1.  Description

* Purpose:

- This C program simulates a classic snake game.
- The player controls the snake's movement to eat food and avoid obstacles.
- The game ends when the snake hits its own body, the walls, or runs out of food.


* Key Features:

- Dynamic memory allocation for the snake's body.
- Collision detection with the snake's body, walls, and food.
- Different game states (running, end of game due to snake collision, end of game due to food shortage).


### 2. How to translate and run the program ?

- Compile the program
    ````c
    make
    ````

- Run the program using the command: 
    ````c
    ./snake
    ````


### 3. How the program is programmed?

* Libraries:

- The code uses the stdlib.h library for dynamic memory allocation.

* Key Programming Concepts:
    - Dynamic memory allocation and deallocation for the snake's body segments.
    - Linked lists to represent the snake's body.
    - Collision detection using a simple algorithm.
    - State machine to manage different game states.


### 4. Links to source code and websites that were used in the solution

-   [GitHub Game World](https://github.com/hladek/world)

