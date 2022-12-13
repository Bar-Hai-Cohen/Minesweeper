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
         //clearScreen();
//  TODO CHECK WHY THE GAME END IF WE CLICK \N
        c = getch();
        switch (c) {
            case 'a': //Left
                if (cur[1] - 1 >= 0) {
                    cur[1] -= 1;
                    //clearScreen();
                    //printBoard(&g, cur);
                }
                break;

            case 'd': //Right
                if (cur[1] + 1 <g.cols) {
                    cur[1] += 1;
//                    clearScreen();
                    //printBoard(&g, cur);
                }
                break;

            case 'w': //Up
                if (cur[0] - 1 >= 0) {
                    cur[0] -= 1;
//                    clearScreen();
                    //printBoard(&g, cur);
                }
                break;

            case 's': //Down
                if (cur[0] + 1<g.rows) {
                    cur[0] += 1;
//                    clearScreen();
                    //printBoard(&g, cur);
                }
                break;

            case '\n':
                clickTile(&g, cur[0], cur[1]);
//                clearScreen();
                //printBoard(&g, cur);
                break;
            case ' ':
                g.board[cur[0]][cur[1]].isFlagged=TRUE;
                //printBoard(&g,cur);
                break;
            case 'q':
                break;
        }
        if(g.isMineClicked){
            printf("loser!!!!");
            break;
        }
        for(int i=0;i<g.rows;i++){
            for(int j=0; j<g.cols;j++){
                if(g.board[i][j].isVisible || g.board[i][j].isFlagged){
                    if(i==g.rows-1 && j==g.cols){
                        printf("You are the champ!! just like tzlil!!");
                        c='q';
                    }
                }
                else break;
            }
        }
       printBoard(&g,cur);

    }


}


