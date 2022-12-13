//
// Created by  bar cohen on 01/12/2022.
//             ID: 209499284
//

#include "mineSweeper.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "colorPrint.h"

//TODO: to check if we need to put if and end if

//TODO: i need to set all the mine no zero start or not ? // why to tzlil is make numbers and to me zero ?

//TODO : todo pre call for all the function that i write here

//TODO : to check why he fall somtimes

//TODO: check total mine


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
//        for(int i=0; i<g->rows;i++){
//            for(int j=0; j<g->cols;j++){
//                g->board[i][j].numOfMines=0;
//                g->board[i][j].isMine=FALSE;
//                g->board[i][j].isVisible=FALSE;
//                g->board[i][j].isFlagged=FALSE;
//            }
//        }
        populateMines(g, level);
    } else {
        printf("Error enter invalid rows or columns or level , pls enter again");

        //TODO: check what to do if the input is invalid
    }
    //TODO: free all the malloc

    return TRUE; // TODO: change

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
            g->board[i][j].numOfMines = 0;
            g->board[i][j].isMine = FALSE;
            g->board[i][j].isFlagged = FALSE;
        }
    }
}


void plus_one_mines(GameBoard *g, int row, int col) {
    /*
     * A function that update all The cells neighboring property if there is neighbor mine
     * param: The parameter pointer to the board , and the row and column
     * return: null
   */

    if (0 <= (row - 1) && (row - 1) <= g->rows && 0 <= (col) &&
        (col) <= g->cols) { //one cell up  [ *g->board[row - 1][col] ]
        g->board[row - 1][col].numOfMines++;
    }

    if (0 <= (row + 1) && (row + 1) <= g->rows && 0 <= (col) &&
        (col) <= g->cols) { // one cell down [  *g->board[row + 1][col] ]
        g->board[row + 1][col].numOfMines++;

    }
    if (0 <= (row) && (row) <= g->rows && 0 <= (col + 1) &&
        (col + 1) <= g->cols) { //one column right [ *g->board[row][col + 1] ]
        g->board[row][col + 1].numOfMines += 1;
    }
    if (0 <= (row) && (row) <= g->rows && 0 <= (col - 1) &&
        (col - 1) <= g->cols) { //one column left [ *g->board[row][col - 1]]
        g->board[row][col - 1].numOfMines++;
    }

    if (0 <= (row - 1) && (row - 1) <= g->rows &&
        0 <= (col - 1) && (col - 1) <= g->cols) { //Diagonal top right [ *g->board[row - 1][col - 1]]
        g->board[row - 1][col - 1].numOfMines++;
    }

    if (0 <= (row + 1) && (row + 1) <= g->rows &&
        0 <= (col - 1) && (col - 1) <= g->cols) { //Diagonal down right [ *g->board[row + 1][col - 1]]
        g->board[row + 1][col - 1].numOfMines++;
    }

    if (0 <= (row - 1) && (row - 1) <= g->rows &&
        0 <= (col + 1) && (col + 1) <= g->cols) { //Diagonal top left [ *g->board[row - 1][col + 1]]
        g->board[row - 1][col + 1].numOfMines++;
    }
    if (0 <= (row + 1) && (row + 1) <= g->rows &&
        0 <= (col + 1) && (col + 1) <= g->cols) { //Diagonal down left [ *g->board[row + 1][col + 1]]
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
        g->board[row][col].isMine = TRUE; // change the property to true
    }
    markNumbers(g);// update all the neighboring cells plus one mine of neighbor

}

void markNumbers(GameBoard *g) {
    /*
     * A function that update all The cells neighboring property if there is neighbor mine
     * param: The parameter pointer to the board
     * return: null
   */
    for (int i = 0; i < g->rows; ++i) {
        for (int j = 0; j < g->cols; ++j) {
            if (g->board[i][j].isMine) { // if the cell is mine
                plus_one_mines(g, i, j);// update all the neighboring cells plus one mine of neighbor
            }
        }
    }
}

void clickTile(GameBoard *g, int row, int col) {
    /*
     * A function that get some index on the tile and make "click" (some change)  on the tile
     * param: The parameter pointer to the board, the row and column
     * return: null
   */
    if (row >= 0 && row <= g->rows && col >= 0 && col <= g->cols) { // if the row and the column is inside the board
        if (g->board[row][col].isVisible) // if the tile is visible return
            return;
        if (!g->board[row][col].isVisible &&
            g->board[row][col].isFlagged)  // if the tile is invisible, and you flagged him (you think is mine)
            return;
        if (!g->board[row][col].isVisible &&
            g->board[row][col].isFlagged == FALSE) { // if the tile is invisible and not flagged
            if (g->board[row][col].isMine) { // if he mines
                g->isMineClicked = TRUE; //  you press mine "end game"
                return;
            }
            if (g->board[row][col].numOfMines >
                0) { //if there is number of neighbor mine just open and show the number of mine around him
                g->board[row][col].isVisible = TRUE;
                return;
            }

            if (g->board[row][col].numOfMines ==
                0) { //there is no neighbor mine around him so call this function to the neighbor of him
                clickTile(g, row - 1, col - 1);// up left
                clickTile(g, row - 1, col); // up
                clickTile(g, row - 1, col + 1);//up right
                clickTile(g, row, col + 1);// right
                clickTile(g, row + 1, col + 1);//down right
                clickTile(g, row + 1, col);//down
                clickTile(g, row + 1, col - 1);//down left
                clickTile(g, row, col - 1);//left
            }
        }
    } else {
        return;
    }
}

void flagTile(GameBoard *g, int row, int col) {
    /*
   * A function that check the specific tile ,if the tile is invisible and not flag, she will flag him
   * param: The parameter pointer to the board, row and column
   * return: null
 */
    if (row >= 0 && row <= g->rows && col >= 0 && col <= g->cols) { // if the row and the column is inside the board
        if (g->board[row][col].isVisible) // if he is visible return
            return;
        if (g->board[row][col].isVisible == FALSE &&
            g->board[row][col].isFlagged == FALSE) //if the tile is invisible and not flag, she will flag him
            g->board[row][col].isFlagged = TRUE;
        if (g->board[row][col].isVisible == FALSE &&
            g->board[row][col].isFlagged == TRUE) //if the tile is invisible and flag, she will remove the flag
            g->board[row][col].isFlagged = FALSE;

    } else { // if the row and col not in the area remove.
        return;
    }
}

void printBoard(GameBoard *g, int cursorCoords[2]) {
    for (int i = 0; i < g->rows; ++i) {
        for (int j = 0; j < g->cols; ++j) {
            if (i == cursorCoords[0] && j == cursorCoords[1]) {
                colorPrint(FG_Red, BG_White, ATT_Def, " #");
            } else if (!g->board[i][j].isVisible && g->board[i][j].isFlagged) {
                colorPrint(FG_Red, BG_White, ATT_Def, " F");
            } else if (g->board[i][j].isVisible && !g->board[i][j].isFlagged) {
                int mine = g->board[i][j].numOfMines;
                colorPrint(FG_Red, BG_White, ATT_Def, " %d", mine);
            } else if (!g->board[i][j].isVisible) {
                colorPrint(FG_Blue, BG_Blue, ATT_Def, "  ");
            }
        }
        printf("\n");
    }
}






