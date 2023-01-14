#ifndef WordsLib
#define WordsLib

#define WORD_LIST_FILE "words.txt"
#define MAX_WORDS 20
#define MAX_WORD_LENGTH 20

void printWords(int wordAmount);
int loadWords(void);
void fillCrossword(int wordAmount, int index, char (*solution)[BOARD_MAX][BOARD_MAX+1], int **usedWords);

#endif