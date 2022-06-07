#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct Grid{
    char data;
    struct Grid *up;
    struct Grid *down;
    struct Grid *left;
    struct Grid *right;
    struct Grid *upLeft;
    struct Grid *upRight;
    struct Grid *downLeft;
    struct Grid *downRight;
};

/**
* Checks whether a grid can be moved to or not, depending on its data
* @param data the grid's data
* @returns whether the data in the grid is a character that a player can move to/overwrite
*/
bool validSpace(char data){
    return (data != 'P' && data != '.') && data != 'A';
}

/**
* Prints the scores for both players
* @param player the player's score
* @param computer the computer's score
*/
void printScore(int playerScore, int computerScore){
    printf("Current scores: \n");
    printf("Player: %i\n", playerScore);
    printf("Computer: %i\n \n", computerScore);
}

/**
* Prints the current state of the board
* @param grid the current board
*/
void printBoard(struct Grid *grid){
    printf("Current board: \n");
    int i, j;
    for(i = 0; i<6; i++){
        for(j = 0; j<6; j++)
            printf("%c ", (grid+6*i+j)->data);
        printf("\n");
    }
}

/**
* Generates the board at the start of the game
* @param grid the board that will be generated
* @returns the updated board
*/
struct Grid *boardGeneration(struct Grid *grid){
    int i;
    //Generates pre-determined values for the game board, since the values follow a pattern, a for loop is optimal
    for(i = 0; i<6; i++){

        //These cover the outer portion with 1s
        (grid+i)->data = '1';
        (grid+30+i)->data = '1';

        //The first and final columns would be all 1s
        if(i == 0 || i == 5){
            (grid+6+i)->data = '1';
            (grid+12+i)->data = '1';
            (grid+18+i)->data = '1';
            (grid+24+i)->data = '1';
            (grid+30+i)->data = '1';
        }

        //The middle 4 elements of the 2nd and 5th column would be all 2s
        if(i == 1 || i == 4){
            (grid+6+i)->data = '2';
            (grid+12+i)->data = '2';
            (grid+18+i)->data = '2';
            (grid+24+i)->data = '2';
        }

        //The middle 4 elements of the 3rd and 4th column would be either 2 or 3
        if(i == 2 || i==3){
            (grid+12+i)->data = '3';
            (grid+18+i)->data = '3';
            (grid+6+i)->data = '2';
            (grid+24+i)->data = '2';
        }
    }

    //Sets the pointers for adjacent grids to point to each other
    for(i = 0; i<5; i++){
        //All of the pointers here are set to point to each other to keep them in 1 loop for convenience's sake
        //We don't set some pointers for the outer edges of the board yet, for example we don't want to set the final row to point down to a certain value, which is why i only runs to 4
        //Pointers arithmetics are used here to easily access adjacent grids
        (grid+6*i)->down = grid+6*(i+1);
        (grid+6*i+1)->down = grid+6*(i+1)+1;
        (grid+6*i+2)->down = grid+6*(i+1)+2;
        (grid+6*i+3)->down = grid+6*(i+1)+3;
        (grid+6*i+4)->down = grid+6*(i+1)+4;
        (grid+6*i+5)->down = grid+6*(i+1)+5;

        (grid+6*(i+1))->up = grid+6*i;
        (grid+6*(i+1)+1)->up = grid+6*i+1;
        (grid+6*(i+1)+2)->up = grid+6*i+2;
        (grid+6*(i+1)+3)->up = grid+6*i+3;
        (grid+6*(i+1)+4)->up = grid+6*i+4;
        (grid+6*(i+1)+5)->up = grid+6*i+5;

        (grid+6*i)->downRight = grid+6*(i+1)+1;
        (grid+6*i+1)->downRight = grid+6*(i+1)+2;
        (grid+6*i+2)->downRight = grid+6*(i+1)+3;
        (grid+6*i+3)->downRight = grid+6*(i+1)+4;
        (grid+6*i+4)->downRight = grid+6*(i+1)+5;

        (grid+6*(i+1)+1)->upLeft = grid+6*i;
        (grid+6*(i+1)+2)->upLeft = grid+6*i+1;
        (grid+6*(i+1)+3)->upLeft = grid+6*i+2;
        (grid+6*(i+1)+4)->upLeft = grid+6*i+3;
        (grid+6*(i+1)+5)->upLeft = grid+6*i+4;

        (grid+i)->right = grid+i+1;
        (grid+6+i)->right = grid+6+i+1;
        (grid+12+i)->right = grid+12+i+1;
        (grid+18+i)->right = grid+18+i+1;
        (grid+24+i)->right = grid+24+i+1;
        (grid+30+i)->right = grid+30+i+1;

        (grid+i+1)->left = grid+i;
        (grid+6+i+1)->left = grid+6+i;
        (grid+12+i+1)->left = grid+12+i;
        (grid+18+i+1)->left = grid+18+i;
        (grid+24+i+1)->left = grid+24+i;
        (grid+30+i+1)->left = grid+30+i;

        (grid+6*(i+1))->upRight = grid+6*i+1;
        (grid+6*(i+1)+1)->upRight = grid+6*i+2;
        (grid+6*(i+1)+2)->upRight = grid+6*i+3;
        (grid+6*(i+1)+3)->upRight = grid+6*i+4;
        (grid+6*(i+1)+4)->upRight = grid+6*i+5;

        (grid+6*i+1)->downLeft = grid+6*(i+1);
        (grid+6*i+2)->downLeft = grid+6*(i+1)+1;
        (grid+6*i+3)->downLeft = grid+6*(i+1)+2;
        (grid+6*i+4)->downLeft = grid+6*(i+1)+3;
        (grid+6*i+5)->downLeft = grid+6*(i+1)+4;
    }

    //Sets the pointers for the outer edges of the game board to point to NULL
    for(i = 0; i<6; i++){
        (grid+i)->up = NULL;
        (grid+i)->upLeft = NULL;
        (grid+i)->upRight = NULL;

        (grid+6*i)->left = NULL;
        (grid+6*i)->upLeft = NULL;
        (grid+6*i)->downLeft = NULL;

        (grid+6*i+5)->right = NULL;
        (grid+6*i+5)->upRight = NULL;
        (grid+6*i+5)->downRight = NULL;

        (grid+30+i)->down = NULL;
        (grid+30+i)->downLeft = NULL;
        (grid+30+i)->downRight = NULL;
    }
    return grid;
}

/**
* Checks if a certain grid is null
* @param grid the grid that will be checked
* @returns either an invalid character if the grid is null or the grid's data
*/
char checkNull(struct Grid *grid){
    if(grid == NULL)
        return '.';
    return grid->data;
}

/**
* Checks if a player can move during their turn
* @param grid the grid the player is currently in
* @returns if the player can move during that turn
*/
bool availableMove(struct Grid *grid){
    char up, down, left, right, upLeft, upRight, downLeft, downRight;

    //Checking if any of the surrounding spaces are NULL spaces, if they are we set them to an invalid character like '.' for the validSpace function
    up = checkNull(grid->up);
    down = checkNull(grid->down);
    left = checkNull(grid->left);
    right = checkNull(grid->right);
    upLeft = checkNull(grid->upLeft);
    upRight = checkNull(grid->upRight);
    downLeft = checkNull(grid->downLeft);
    downRight = checkNull(grid->downRight);

    //Setting the NULL characters to '.' allow validSpace to access them so we do not get an error
    //If none of the 8 spaces are invalid, there is an available move
    if(!validSpace(up) && !validSpace(down) && !validSpace(left) && !validSpace(right) && !validSpace(upLeft) && !validSpace(upRight) && !validSpace(downLeft) && !validSpace(downRight))
        return false;
    return true;
}

/**
* Checks if the path the player is taking has any '.'s on the way, or if the path goes out of bounds
* @param direction the direction the player is going in
* @param distance the distance the player is taking
* @param grid the grid the player is currently in
* @returns whether the path can be taken
*/
bool validPath(char *direction, int distance, struct Grid *grid){

    struct Grid *curGrid = grid;

    //Traversing each of the 8 directions similar to traversing a linked list, while making sure that we reach the destination within the given distance, and that there's no NULL grids
    //or no grids that are already occupied with '.' or another player
    if(strcmp(direction, "UP") == 0){
        while(curGrid != NULL && distance != 0){
            //Checking whether the next grid is null or the next grid can't be reached, so we can break out of the while loop to handle the distance condition up next
            if(curGrid->up == NULL || !validSpace((curGrid->up)->data)) break;
            curGrid = curGrid->up;
            distance--;
        }
    }
    else if(strcmp(direction, "DOWN") == 0){
        while(curGrid != NULL && distance != 0){
            if(curGrid->down == NULL || !validSpace((curGrid->down)->data) ) break;
            curGrid = curGrid->down;
            distance--;
        }
    }
    else if(strcmp(direction, "LEFT") == 0){
        while(curGrid != NULL && distance != 0){
            if(curGrid->left == NULL || !validSpace((curGrid->left)->data)) break;
            distance--;
            curGrid = curGrid->left;
        }
    }
    else if(strcmp(direction, "RIGHT") == 0){
        while(curGrid != NULL && distance != 0){
            if(curGrid->right == NULL || !validSpace((curGrid->right)->data)) break;
            distance--;
            curGrid = curGrid->right;
        }
    }
    else if(strcmp(direction, "UPLEFT") == 0){
        while(curGrid != NULL && distance != 0){
            if(curGrid->upLeft == NULL || !validSpace((curGrid->upLeft)->data)) break;
            distance--;
            curGrid = curGrid->upLeft;
        }
    }
    else if(strcmp(direction, "UPRIGHT") == 0){
        while(curGrid != NULL && distance != 0){
            if(curGrid->upRight == NULL || !validSpace((curGrid->upRight)->data)) break;
            distance--;
            curGrid = curGrid->upRight;
        }
    }
    else if(strcmp(direction, "DOWNLEFT") == 0){
        while(curGrid != NULL && distance != 0){
            if(curGrid->downLeft == NULL || !validSpace((curGrid->downLeft)->data)) break;
            distance--;
            curGrid = curGrid->downLeft;
        }
    }
    else if(strcmp(direction, "DOWNRIGHT") == 0){
        while(curGrid != NULL && distance != 0){
            if(curGrid->downRight == NULL || !validSpace((curGrid->downRight)->data)) break;
            distance--;
            curGrid = curGrid->downRight;
        }
    }

    //If we reached an invalid space before running out of distance, we either hit a '.' or another player on the way or we're going out of bounds, so this is an invalid path
    if(distance != 0) return false;
    return true;
}

/**
* Adds up the score for taking a path in a direction with a distance, while also updating the board to fill the path taken with '.'s
* @param direction the direction the player is going in
* @param distance the distance the player is taking
* @param grid the grid the player's currently in
* @param player the current player (human or computer)
* @returns the total score from taking that path
*/
int pathScore(char *direction, int distance, struct Grid *grid, char player){
    int pathSum = 0;
    struct Grid *curGrid = grid;
    //Traversing each of the 8 directions similar to traversing a linked list, while adding up the score obtained from traveling in a certain direction and updating the board
    //with '.'s as we go along.
    if(strcmp(direction, "UP") == 0){
        while(curGrid != NULL && distance != 0){
            //Because we know this is a valid path we're taking, we do not need to check whether we have hit an invalid space or not, so we proceed
            //We convert the data in a grid from char to int by subtracting '0' from it, due to their ASCII values
            pathSum += (curGrid->up)->data - '0';
            curGrid->data = '.';
            (curGrid->up)->data = player;
            distance--;
            curGrid = curGrid->up;
        }
    }
    else if(strcmp(direction, "DOWN") == 0){
        while(curGrid != NULL && distance != 0){
            pathSum += (curGrid->down)->data - '0';
            curGrid->data = '.';
            (curGrid->down)->data = player;
            distance--;
            curGrid = curGrid->down;
        }
    }
    else if(strcmp(direction, "LEFT") == 0){
        while(curGrid != NULL && distance != 0){
            pathSum += (curGrid->left)->data - '0';
            curGrid->data = '.';
            (curGrid->left)->data = player;
            distance--;
            curGrid = curGrid->left;
        }
    }
    else if(strcmp(direction, "RIGHT") == 0){
        while(curGrid != NULL && distance != 0){
            pathSum += (curGrid->right)->data - '0';
            curGrid->data = '.';
            (curGrid->right)->data = player;
            distance--;
            curGrid = curGrid->right;
        }
    }
    else if(strcmp(direction, "UPLEFT") == 0){
        while(curGrid != NULL && distance != 0){
            pathSum += (curGrid->upLeft)->data - '0';
            curGrid->data = '.';
            (curGrid->upLeft)->data = player;
            distance--;
            curGrid = curGrid->upLeft;
        }
    }
    else if(strcmp(direction, "UPRIGHT") == 0){
        while(curGrid != NULL && distance != 0){
            pathSum += (curGrid->upRight)->data - '0';
            curGrid->data = '.';
            (curGrid->upRight)->data = player;
            distance--;
            curGrid = curGrid->upRight;
        }
    }
    else if(strcmp(direction, "DOWNLEFT") == 0){
        while(curGrid != NULL && distance != 0){
            pathSum += (curGrid->downLeft)->data - '0';
            curGrid->data = '.';
            (curGrid->downLeft)->data = player;
            distance--;
            curGrid = curGrid->downLeft;
        }
    }
    else if(strcmp(direction, "DOWNRIGHT") == 0){
        while(curGrid != NULL && distance != 0){
            pathSum += (curGrid->downRight)->data - '0';
            curGrid->data = '.';
            (curGrid->downRight)->data = player;
            distance--;
            curGrid = curGrid->downRight;
        }
    }
    return pathSum;
}

/**
* Updates the X coordinate of a player based on direction and distance
* @param direction the direction a player's going in
* @param distance the distance a player's taking
* @param posX the current X position of a player
*/
void updateX(char *direction, int distance, int* posX){
    //Incrementing the X position whenever a player moves right
    if(strcmp(direction, "RIGHT") == 0 || strcmp(direction, "UPRIGHT") == 0 || strcmp(direction, "DOWNRIGHT") == 0)
        *posX += distance;

    //Decrementing the X position whenever a player moves left
    if(strcmp(direction, "LEFT") == 0 || strcmp(direction, "UPLEFT") == 0 || strcmp(direction, "DOWNLEFT") == 0)
        *posX -= distance;
}

/**
* Updates the Y coordinate of a player based on direction and distance
* @param direction the direction a player's going in
* @param distance the distance a player's taking
* @param posY the current Y position of a player
*/
void updateY(char *direction, int distance, int* posY){
    //Decrementing the Y position whenever a player moves up
    if(strcmp(direction, "UP") == 0 || strcmp(direction, "UPRIGHT") == 0 || strcmp(direction, "UPLEFT") == 0)
        *posY -= distance;

    //Incrementing the y position whenever a player moves down
    if(strcmp(direction, "DOWN") == 0 || strcmp(direction, "DOWNRIGHT") == 0 || strcmp(direction, "DOWNLEFT") == 0)
        *posY += distance;
}

/**
* Finds the optimal path/valid path with the maximum score for the computer to take based on every single path that the computer can take
* @param grid the grid the computer's currently in
* @param posX the current X position of the computer
* @param posY the current Y position of the computer
* @returns the total score from taking a path chosen from all the 8 possible paths that attain the maximum value from 8 different directions
*/
int findOptimalPath(struct Grid *grid, int* posX, int* posY){
    struct Grid *curGrid = grid;
    int distanceUp = 0;
    int distanceDown = 0;
    int distanceLeft = 0;
    int distanceRight = 0;
    int distanceUpLeft = 0;
    int distanceUpRight = 0;
    int distanceDownLeft = 0;
    int distanceDownRight = 0;
    int maximum = 0;

    //Traversing each of the 8 directions similar to traversing a linked list to find the farthest distance it takes to reach a valid grid
    while(curGrid != NULL){
        if(curGrid->up == NULL || !validSpace((curGrid->up)->data)) break;
        curGrid = curGrid->up;
        distanceUp++;
    }

    //Finding the maximum distance for each direction, that will lead us to the most optimal path for the computer
    if(maximum < distanceUp) maximum = distanceUp;
    curGrid = grid;
    while(curGrid != NULL){
        if(curGrid->down == NULL || !validSpace((curGrid->down)->data)) break;
        curGrid = curGrid->down;
        distanceDown++;
    }
    if(maximum < distanceDown) maximum = distanceDown;
    curGrid = grid;
    while(curGrid != NULL){
        if(curGrid->left == NULL || !validSpace((curGrid->left)->data)) break;
        curGrid = curGrid->left;
        distanceLeft++;
    }
    if(maximum < distanceLeft) maximum = distanceLeft;
    curGrid = grid;
    while(curGrid != NULL){
        if(curGrid->right == NULL || !validSpace((curGrid->right)->data)) break;
        curGrid = curGrid->right;
        distanceRight++;
    }
    if(maximum < distanceRight) maximum = distanceRight;
    curGrid = grid;
    while(curGrid != NULL){
        if(curGrid->upLeft == NULL || !validSpace((curGrid->upLeft)->data)) break;
        curGrid = curGrid->upLeft;
        distanceUpLeft++;
    }
    if(maximum < distanceUpLeft) maximum = distanceUpLeft;
    curGrid = grid;
    while(curGrid != NULL){
        if(curGrid->upRight == NULL || !validSpace((curGrid->upRight)->data)) break;
        curGrid = curGrid->upRight;
        distanceUpRight++;
    }
    if(maximum < distanceUpRight) maximum = distanceUpRight;
    curGrid = grid;
    while(curGrid != NULL){
        if(curGrid->downLeft == NULL || !validSpace((curGrid->downLeft)->data)) break;
        curGrid = curGrid->downLeft;
        distanceDownLeft++;
    }
    if(maximum < distanceDownLeft) maximum = distanceDownLeft;
    curGrid = grid;
    while(curGrid != NULL){
        if(curGrid->downRight == NULL || !validSpace((curGrid->downRight)->data) ) break;
        curGrid = curGrid->downRight;
        distanceDownRight++;
    }
    if(maximum < distanceDownRight) maximum = distanceDownRight;
    curGrid = grid;
    char *direction;

    //Choosing which direction to take based on the maximum distance
    if(maximum == distanceUp)
        direction = "UP";
    else if(maximum == distanceDown)
        direction = "DOWN";
    else if(maximum == distanceLeft)
        direction = "LEFT";
    else if(maximum == distanceRight)
        direction = "RIGHT";
    else if(maximum == distanceUpLeft)
        direction = "UPLEFT";
    else if(maximum == distanceDownLeft)
        direction = "DOWNLEFT";
    else if(maximum == distanceUpRight)
        direction = "UPRIGHT";
    else
        direction = "DOWNRIGHT";
    printf("Computer has gone %s with distance of %d \n", direction, maximum);

    //Updating the X and Y coordinates of the computer accordingly
    updateX(direction, maximum, posX);
    updateY(direction, maximum, posY);

    //Utilizing the pathScore function by passing in the direction and distance to calculate the maximum score the computer will achieve from taking a path
    return pathScore(direction, maximum, curGrid, 'A');
}

int main(void){
    printf("Welcome to \"Hey, that's my Fish\"! Here is the game board you will be playing on: \n");
    printf("P is the position you will be starting with, A is the position the AI will be starting with. \n");
    printf("You may input the direction and the distance you would like to travel in, as long as the grid you're traveling to has a valid path and is not occupied \n");
    printf("Whoever collects the most points on the board wins. Good luck. \n");
    bool gameState = true;

    //Creates an empty game board
    struct Grid *grid = malloc(sizeof(struct Grid)*36);
    int i;

    boardGeneration(grid);

    //These keep track of the coordinates of both players
    int playerPosX = 1;
    int playerPosY = 1;
    int computerPosX = 4;
    int computerPosY = 4;

    //These keep track of the players' scores
    int playerScore = 1;
    int computerScore = 1;

    //These keep track of the players' current coordinates to work with pointers arithmetics easier
    int curPlayerPos = 6*playerPosY + playerPosX;
    int curComputerPos = 6*computerPosY+computerPosX;

    //These set both the players' current grids to their respective character, indicating the starting positions for both
    (grid+curPlayerPos)->data = 'P';
    (grid+curComputerPos)->data = 'A';

    //This bool checks whether it's currently the human player's turn or not
    bool playerTurn = true;

    //The loop that keeps on running until the game is over (when neither player has any valid move left)
    while(gameState){
        //Prints the current state of the game
        printScore(playerScore, computerScore);
        printBoard(grid);

        //This loop continues to run until the player has made a valid move or the player is unable to move from the current grid
        while(playerTurn){
            //Checks if the player has a valid move (if they're not surrounded by invalid characters). If yes, their turn is skipped.
            if(!availableMove(grid+curPlayerPos)){
                printf("Player doesn't have any valid moves. Their turn is skipped. \n ");
                playerTurn = false;
                break;
            }
            printf("Player's turn. Input your desired direction. \n");

            char *input = (char*) calloc(13, sizeof(char));

            //This takes in the input
            fgets(input, 13, stdin);

            //strtok is used here to separate the direction the player chooses from the distance they want to move in
            char *direction = strtok(input, " ");
            int distance = strtol(strtok(NULL, " "), NULL, 10);

            //This checks whether the player has inputted a valid path. If yes, the board and player score are updated accordingly, and the player's turn is over
            //If not, the loop repeats itself and allows the player to input again
            bool result = validPath(direction, distance, grid+curPlayerPos);
            if(!result){
                printf("Path is invalid, please choose another path. \n");
            }
            else{
                //Updates the player score based on the direction and distance taken, while also updating the game board by filling the path with '.'s and 'P' at the destination
                playerScore += pathScore(direction, distance, grid+curPlayerPos, 'P');

                //These update the player's current coordinates, and print them subsequently
                updateX(direction, distance, &playerPosX);
                updateY(direction, distance, &playerPosY);
                printf("Player's current position is (%d, %d) \n \n", playerPosY+1, playerPosX+1);
                curPlayerPos = 6*playerPosY + playerPosX;
                playerTurn = false;
                free(input);
            }
        }
        //Prints the current state of the game
        printScore(playerScore, computerScore);
        printBoard(grid);

        printf("Computer's turn.\n");

        //Checks if the computer has a valid move (if it isn't surrounded by invalid characters). If yes, their turn is skipped.
        //If no, their score and position will be updated accordingly.
        if(availableMove(grid+curComputerPos)){
            //This first finds the optimal path taken by considering all 8 directions, and finding the path with the maximum value
            //This also updates the computer score based on the direction and distance chosen, while also updating the game board by filling the path with '.'s and 'A' at the destination
            computerScore += findOptimalPath(grid+curComputerPos, &computerPosX, &computerPosY);
            curComputerPos = 6*computerPosY+computerPosX;
            printf("Computer's current position is (%d, %d) \n \n", computerPosY+1, computerPosX+1);
        }
        else
            printf("Computer doesn't have any valid moves. Their turn is skipped. \n ");

        //If the player has an available move, it's back to their turn
        if(availableMove(grid+curPlayerPos))
            playerTurn = true;

        //If neither player has an available move, the game ends
        if(!availableMove(grid+curComputerPos) && !availableMove(grid+curPlayerPos)){
            gameState = false;
            printf("Neither player has any valid moves left. The game is over. \n");
        }

    }
    //Prints the current game state
    printBoard(grid);
    printScore(playerScore, computerScore);

    //The final result of the game. Whoever has the higher score wins. This also accounts for a tie.
    if(playerScore > computerScore)
        printf("The player has won. \n");
    else if(playerScore < computerScore)
        printf("The computer has won. \n");
    else
        printf("Both the players are tied. \n");
    free(grid);
    return 0;
}

