//
// Created by  bar cohen on 01/12/2022.
//             ID: 209499284
//

#include "Minesweeper.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

bool initBoard(GameBoard *g, int rows, int cols, int level) { //returns true upon success
    /*
     * A function that create The board and initialize the Struct game board.
     * param: The parameter rows and columns of the board, the totalMines in the board, and pointer to the board
     * return: return True if initialize succeed Else return False.
     */

    if (rows > 0 && rows <= MAX_BOARD_DIM && cols > 0 && cols <= MAX_BOARD_DIM && level >= EASY && level <= HARD) {

        //Initialize property
        g->rows = rows;
        g->cols = cols;

        //Initialize the board game :Create the 2D array
        g->board = (Tile **) malloc(sizeof(Tile *) * (rows));
        for (int i = 0; i < rows; ++i) {
            g->board[i] = (Tile *) malloc(sizeof(Tile) * cols);
        }
        populateMines(g, level);
    } else {
        printf("Error enter invalid rows or columns or level , pls enter again");

        //TODO: check what to do if the input is invalid
    }

}

void init_visibileity(GameBoard *g) {
    /*
     * A function that initialize all tiles property_isVisible to false
    * param: The parameter pointer to the board
    * return: null
    */
    for (int i = 0; i < g->rows; ++i) {
        for (int j = 0; j < g->cols; ++j) {
            g->board[i][j].isVisible = FALSE; // change the property to false
        }
    }
}


void plus_one_mines(GameBoard *g, int row, int col) {
    /*
     * A function that update all The cells neighboring property if there is neighbor mine
     * param: The parameter pointer to the board , and the row and column
     * return: null
   */

    if (0 <= (row - 1) <= g->rows && 0 <= (col) <= g->cols) { //one cell up  [ *g->board[row - 1][col] ]
        g->board[row - 1][col].numOfMines++;
    }

    if (0 <= (row + 1) <= g->rows && 0 <= (col) <= g->cols) { // one cell down [  *g->board[row + 1][col] ]
        g->board[row + 1][col].numOfMines++;
    }
    if (0 <= (row) <= g->rows && 0 <= (col + 1) <= g->cols) { //one column right [ *g->board[row][col + 1] ]
        g->board[row][col + 1].numOfMines++;
    }
    if (0 <= (row) <= g->rows && 0 <= (col - 1) <= g->cols) { //one column left [ *g->board[row][col - 1]]
        g->board[row][col - 1].numOfMines++;
    }

    if (0 <= (row - 1) <= g->rows &&
        0 <= (col - 1) <= g->cols) { //Diagonal top right [ *g->board[row - 1][col - 1]]
        g->board[row - 1][col - 1].numOfMines++;
    }

    if (0 <= (row + 1) <= g->rows &&
        0 <= (col - 1) <= g->cols) { //Diagonal down right [ *g->board[row + 1][col - 1]]
        g->board[row + 1][col - 1].numOfMines++;
    }

    if (0 <= (row - 1) <= g->rows &&
        0 <= (col + 1) <= g->cols) { //Diagonal top left [ *g->board[row - 1][col + 1]]
        g->board[row - 1][col + 1].numOfMines++;
    }
    if (0 <= (row + 1) <= g->rows &&
        0 <= (col + 1) <= g->cols) { //Diagonal down left [ *g->board[row + 1][col + 1]]
        g->board[row + 1][col + 1].numOfMines++;
    }

}


void populateMines(GameBoard *g, int level) {
    /*
     * A function that determine The number of mine on board according to the level that chosen.
     * param: The parameter pointer to the board , and the level of the game
     * return: null
   */

    srand(time(NULL)); //to change the random numbers
    int rows = g->rows; // get the rows
    int cols = g->cols; // get the cols
    init_visibileity(g);// init to initialize all tiles property_isVisible to false, that they are inadvisable

    switch (level) { // determine how much mine to put inside the board according the level that chosen
        case EASY:
            g->totalMines = ((rows * cols * EASY_LEVEL_PERCENT) / 100);
            break;
        case MEDIUM:
            g->totalMines = ((rows * cols * MEDIUM_LEVEL_PERCENT) / 100);
            break;
        case HARD:
            g->totalMines = ((rows * cols * HARD_LEVEL_PERCENT) / 100);
            break;
    }
    for (int i = 0; i < g->totalMines; ++i) { // for that random the mine inside the board
        int row = rand() % (g->rows - 1); // rand row between 1-20
        int col = rand() % (g->cols - 1); // rand col between 1-20
        g->board[row][col].isMine = TRUE; // change the property to false
        plus_one_mines(g, row, col);// update all the neighboring cells plus one mine of neighbor
    }
}

void printBoard(GameBoard *g, int cursorCoords[2]) {
    for (int i = 0; i < g->rows; ++i) {
        for (int j = 0; j < g->cols; ++j) {
            printf("%d ", g->board[i][j].isMine);
        }
        printf("\n");
    }
}



