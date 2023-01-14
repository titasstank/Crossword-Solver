#ifndef BoardLib
#define BoardLib

#define BOARD_FILE "board.txt"
#define BOARD_MAX 10
#define MAX_LOCATIONS 10

typedef struct slots{
    unsigned letters;
    unsigned short x, y;
    char direction;
}slots;

typedef struct boardData{
    char board[BOARD_MAX][BOARD_MAX+1];
    unsigned rows, columns;
    unsigned locationAmount;
    slots locations[MAX_LOCATIONS];
}boardData;

void loadBoard(void);
void printBoard(char board[BOARD_MAX][BOARD_MAX+1]);
void printBoardWithEmptySpaces(char board[BOARD_MAX][BOARD_MAX+1]);
void assignData(int row, int column, char directions);
void analyzeBoard(void);
void printAnalysis(void);
int checkIfSolved(char board[BOARD_MAX][BOARD_MAX+1]);

#endif