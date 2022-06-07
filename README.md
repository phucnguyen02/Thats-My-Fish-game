# Thats-My-Fish-game
Simulation of the That's My Fish game

This implementation for the game "Hey, That's my Fish" involves the usage of linked lists to create the game board. 
Each grid on the board would have 8 pointers pointing to 8 of its neighbors in different directions, along with a data value for itself.
Setting up the pointers properly would allow me to easily access the grid's neighbors, similar to traversing a linked list. 
The player would input a direction and distance, the board would then update itself accordingly, filling the path taken with '.'s and a 'P' at the destination, while also updating the player score for every grid that they traveled to. 
I have also implemented a way to make the computer player choose the most optimal path by getting the maximum values achieved from taking paths in 8 separate directions (going to the furthest valid grid), and then picking the one that would give the most points. 
