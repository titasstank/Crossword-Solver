#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BoardLib.h"

boardData Board;

void loadBoard(){
    FILE *boardInputFile;
    if((boardInputFile = fopen(BOARD_FILE, "r")) == NULL){
        printf("File %s, does not exist, plese create it.\n", BOARD_FILE);
        return;
    }
    for(Board.rows = 0; !feof(boardInputFile) && Board.rows < BOARD_MAX; ++Board.rows){
        fgets(Board.board[Board.rows], BOARD_MAX+2, boardInputFile);
    }
    Board.columns = strlen(Board.board[0]);
    fclose(boardInputFile);
    printf("Board loaded sucesfully!\n");
}

void printBoard(char board[BOARD_MAX][BOARD_MAX+1]){
    for(int i = 0; i < Board.rows; ++i){
        printf("%s", board[i]);
    }
    printf("\n");
}

void printBoardWithEmptySpaces(char board[BOARD_MAX][BOARD_MAX+1]){
    for(int i = 0; i < Board.rows; ++i){
        for(int j = 0; j < Board.columns; ++j){
            printf("%c", board[i][j] == '1' ? ' ' : board[i][j]);
        }
    }
    printf("\n");
}

void assignData(int row, int column, char direction){
    Board.locations[Board.locationAmount].x = column;
    Board.locations[Board.locationAmount].y = row;
    Board.locations[Board.locationAmount].direction = direction;
    Board.locations[Board.locationAmount].letters = 0;
    if(direction == 'H'){
        for(int i = column; i < Board.columns; ++i, ++Board.locations[Board.locationAmount].letters){
            if(Board.board[row][i] != '0'){
                break;
            }
        }
    }
    else{
        for(int i = row, letters; i < Board.rows; ++i, ++Board.locations[Board.locationAmount].letters){
            if(Board.board[i][column] != '0'){
                break;
            }
        }
    }
    ++Board.locationAmount;
}

void analyzeBoard(void){
    for(int row = 0; row < Board.rows; ++row){
        for(int column = 0; column < Board.columns; ++column){
            if(Board.board[row][column] == '0'){
                if(Board.board[row][column+1] == '0' && Board.board[row][column-1] != '0'){
                    assignData(row, column, 'H');
                }
                if(Board.board[row+1][column] == '0' && Board.board[row-1][column] != '0'){
                    assignData(row, column, 'V');
                }
            }
        }
    }
    printf("Board analyzed sucessfully!\n");
}

void printAnalysis(void){
    for(int i = 0; i < Board.locationAmount; ++i){
        printf("%d) Location:\nLenght - %d\nStarting position - (%d, %d)\nDirection - %c\n\n", i, Board.locations[i].letters, Board.locations[i].x, Board.locations[i].y, Board.locations[i].direction);
    }
}

int checkIfSolved(char board[BOARD_MAX][BOARD_MAX+1]){
    for(int i = 0; i < Board.rows; ++i){
        for(int j = 0; j < Board.columns; ++j){
            if(board[i][j] == '0'){
                return 0;
            }
        }
    }
    return 1;
}