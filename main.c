#include <stdio.h>
#include <stdlib.h>
#include "BoardLib.h"
#include "WordsLib.h"

extern boardData Board;

void makeCopy(char (*solution)[BOARD_MAX][BOARD_MAX+1]){
    for(int i = 0; i < BOARD_MAX; ++i){
        for(int j = 0; j < BOARD_MAX+1; ++j){
            (*solution)[i][j] = Board.board[i][j];
        } 
    }
}

int main(){
    loadBoard();
    // printBoard(Board.board);
    analyzeBoard();
    // printAnalysis();
    int wordAmount = loadWords();
    char solution[BOARD_MAX][BOARD_MAX+1];
    makeCopy(&solution);
    // printBoard(solution);
    printf("\n");
    // printWords(wordAmount);
    int *usedWords = (int*)malloc(Board.locationAmount * sizeof(int));
    fillCrossword(wordAmount, 0, &solution, &usedWords);
    printf("\n");
    if(checkIfSolved(solution)){
        printBoard(solution);
        printBoardWithEmptySpaces(solution);
    }
    else{
        printf("The crossword cannot be solved with the words provided!\n");
    }
    free(usedWords);
    return 0;
}