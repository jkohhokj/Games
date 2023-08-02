# Games

Quick overview of each major program.

### Physics Engine: 

> A 2D physics engine that applies conservation of momentum for object collision. Movement can be absolute or by acceleration for linear and rotational motion.

Unit Class: square object with different properties and methods that change location and acceleration which is blit on the screen.

Rotator Function: rotates a point around another point.

Momentum Function: calculates decceleration of friction on objects.

permDead Function: eliminates all forces on Unit.

Sticker Function: increases friction across an area.

pushOut Function: applies normal force to Unit (makes sure Units don't go into each other).

throwOut Function: reverses direction of acceleration.

bouncelessCollision Function: applies pushOut function on 2 Units.

permStick Function: combines 2 Units together.

draggingCollision Function: moves 2 Units together.

Bouncing Function: bounces 2 Units together.

detectOverlap Function: checks mask overlap of 2 Units.

drawAttributes Function: Draws the masks for each Unit.

Main Function: Initializes each Unit and connects keyboard inputs while applying collisions.

### Snake (original):

> Replica of the Snake game in Tetris, built off a tutorial.

Class Apple: Pygame sprite as a rectangle for prize.

Class Segment: Pygame sprite as a rectangle for each segment of snake.

Main Function: 

> Ask for screen size 
>
> Initialize screen
>
> Create a matrix of locations of segments
>
> Check for collision with itself and walls
>
> Check input commands
>
> Propogate movement of segments
>
> Blit grid and snake segments

### Tetris (tetrisbutitworks.py):

> Replica of the classic Tetris game, all code is original

Class Subpiece: subpiece that comprises a Tetromino

Class Piece: 4 subpieces that comprise Tetromino that can

 - apply gravity
 - move linearly
 - rotate
 
random_shape_gen Function: returns a Piece that is randomly generated

gravity Function: changes the speed that Tetrominoes fall in correlation to level

draw_it Function: draws grid pieces

kill_it Function: Appends user controlled Piece to block of immovable objects and initialized new user controlled Piece

check_line Function: Checks if new lines have been made, removes them, and scores points

move_down_line_list Function: 

### Bridger:

> Meant as a macro hack that clicks when a certain image appears, doesn't work 100%.

Uses PIL to render and parse video screen to click mouse buttons when conditions are met.


### Gaze Tracking:

> Project I prototyped for a hospital, they eventually ended up outsourcing to a company. It detects reaction time between eye gazes and records it for medical purposes. Built off the cv2 and dlib open source libraries, I only implemented the timing and recording system.

### Miscellaneous:
> Random projects I've worked on from scripts to assignments, the rest don't really belong anywhere and are kinda just dumped here.
