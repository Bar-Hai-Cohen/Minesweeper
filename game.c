//
// Created by   bar cohen on 13/12/2022.
//

#include <stdio.h>
#include "mineSweeper.h"
#include "getch.h"
#include "colorPrint.h"


int main() {
    int row, col, level;

    printf("Enter a number of row:");
    scanf("%d", &row);
    printf("Enter a number of columns:");
    scanf("%d", &col);
    printf("Enter level of game:");
    scanf("%d", &level);
    GameBoard g;
    int cur[2] = {0, 0};
    initBoard(&g, row, col, level); //returns true upon success
    char c = getch();
    printBoard(&g, cur);
    while (c != 'q') {
        c = getch();
        switch (c) {
            case LEFT:
                if (cur[1] - 1 >= 0) {
                    cur[1] -= 1;
                }
                break;

            case RIGHT:
                if (cur[1] + 1 < g.cols) {
                    cur[1] += 1;
                }
                break;

            case UP:
                if (cur[0] - 1 >= 0) {
                    cur[0] -= 1;
                }
                break;

            case DOWN:
                if (cur[0] + 1 < g.rows) {
                    cur[0] += 1;
                }
                break;

            case CLICK_TILE:
                clickTile(&g, cur[0], cur[1]);

                break;
            case FLAG_TILE:
                flagTile(&g, cur[0], cur[1]);
                break;
            case QUIT:
                break;
        }
        if (g.isMineClicked) {
            printf("oops..you click on mine");
            break;
        }
        if (g.hiddenTiles == g.totalMines) {
            printf("You won!");
            break;
        }
        printBoard(&g, cur);
    }


}
