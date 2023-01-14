#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "BoardLib.h"
#include "WordsLib.h"

extern boardData Board;
char words[MAX_WORDS][MAX_WORD_LENGTH+1]; 

void printWords(int wordAmount){
    for(int i = 0; i < wordAmount; ++i){
        printf("%s", words[i]);
    }
    printf("\n");
}

int loadWords(void){
    FILE *wordList;
    if((wordList = fopen(WORD_LIST_FILE, "r")) == NULL){
        printf("%s file does not exist. Please create it.\n", WORD_LIST_FILE);
        return 0;
    }
    int wordAmount;
    for(wordAmount = 0; !feof(wordList); ++wordAmount){
        fgets(words[wordAmount], MAX_WORD_LENGTH+2, wordList);
    }
    printf("Words loaded successfully!\n");
    return wordAmount;
}

int doesntFit = 0;
void clearEntry(char (*solution)[BOARD_MAX][BOARD_MAX+1], int index){
    if(Board.locations[index].direction == 'H'){
        for(int i = Board.locations[index].x; i < Board.locations[index].x + Board.locations[index].letters; ++i){
            if(!isalpha((*solution)[Board.locations[index].y+1][i]) && !isalpha((*solution)[Board.locations[index].y-1][i])){
                (*solution)[Board.locations[index].y][i] = '0';
            }
        }
    }
    else{
        for(int i = Board.locations[index].y; i < Board.locations[index].y + Board.locations[index].letters; ++i){
            if(!isalpha((*solution)[Board.locations[index].y][i+1]) && !isalpha((*solution)[Board.locations[index].y][i-1])){
                (*solution)[i][Board.locations[index].x] = '0';
            }
        }
    }
    doesntFit = 0;
}

int filled = 0;
void fillCrossword(int wordAmount, int index, char (*solution)[BOARD_MAX][BOARD_MAX+1], int **usedWords){
    for(int i = 0; i < wordAmount; ++i){
        int wordIsInUse = 0;
        for(int z = 0; z < index; ++z){
            if(i == (*usedWords)[z]){
                wordIsInUse = 1;
                break;
            }
        }
        if(wordIsInUse){
            wordIsInUse = 0;
            continue;
        }
        if(strlen(words[i])-1 == Board.locations[index].letters){
            unsigned short put = 0;
            if(Board.locations[index].direction == 'H'){
                for(int z = 0; z < 2; ++z){
                    for(int j = Board.locations[index].x; j < Board.locations[index].x + Board.locations[index].letters; ++j){
                        if(put){
                            (*solution)[Board.locations[index].y][j] = words[i][j - Board.locations[index].x];
                            doesntFit = 0;
                        }
                        if(Board.board[Board.locations[index].y][j] != '0' && (*solution)[Board.locations[index].y][j] != words[i][j - Board.locations[index].x]){
                            doesntFit = 1;
                            return;
                        }
                    }    
                    put = 1;
                }
            }
            else{
                for(int z = 0; z < 2; ++z){
                    for(int j = Board.locations[index].y; j < Board.locations[index].y + Board.locations[index].letters; ++j){
                        if(put){
                            (*solution)[j][Board.locations[index].x] = words[i][j - Board.locations[index].y];
                            doesntFit = 0;                            
                        }
                        if(Board.board[j][Board.locations[index].x] != '0' && (*solution)[j][Board.locations[index].x] != words[i][j - Board.locations[index].x]){
                            doesntFit = 1;
                            return;
                        }
                    }
                    put = 1; 
                }
            }
            if(!doesntFit && index < Board.locationAmount){
                (*usedWords)[index] = i;
                fillCrossword(wordAmount, index + 1, solution, usedWords);
            }
            else{
                filled = 1;
            }
            if(filled){
                return;
            }
        }
    }
    if(doesntFit){
        clearEntry(solution, index);
    }
}
