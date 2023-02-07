#include <stdio.h>
#include <stdlib.h>

void printGrid();
void check(int row, int col);
void flag(int row, int col);
void checkWin();
char cellGrid[10][10];
char userView[10][10];
int indicate;
int gameStatus = 1;
char temp;
int winStatus;
int count = 0;

int main() {
    char command;
    int row;
    int col;
    srand(2);

    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            cellGrid[x][y] = '*';
        }
    }

    for (int a = 0; a < 10; a++) {
        int x = rand() % 10;
        int y = rand() % 10;
        cellGrid[x][y] = 'M';
    }

    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            if (cellGrid[x][y] != 'M') {
                cellGrid[x][y] = 0 + 48;
            }
        }
    }

    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            indicate = 0;
            if (cellGrid[x][y] != 'M') {
                for (int a = -1; a <= 1;a++) {
                    for (int b = -1; b <= 1; b++) {
                        if (cellGrid[x + a][y + b] == 'M' ) {
                            if (y + b >= 0 && y+b <= 10 && x+a >= 0 && x+a <=10) {
                                indicate++;
                            }
                        }
                    }
                }
                cellGrid[x][y] = indicate + 48;
            }
        }
    }

    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            userView[x][y] = '*';
        }
    }

    do {
        printGrid();
        printf("Enter 'c' for check cell, 'f' for flag cell.\n");
        printf("Enter command & cell row col: ");
        scanf("%c %d %d", & command, & row, & col);
        if (command == 'c')
            check(row, col);
        if (command == 'f')
            flag(row, col);
    } while (gameStatus);
    
    winStatus = gameStatus;
    checkWin();

}

void printGrid() {
  printf("\n");
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            printf("%c  ", userView[x][y]);
        }
      printf("\n");
    }
}

void check(int row, int col) {
  
  if (cellGrid[row][col] == 'M') {
    userView[row][col] = 'M';
    gameStatus = 0;
    printf("You hit a mine, game over.\n");
    return 0;
  } 
  else {
    count++;
    userView[row][col] = cellGrid[row][col];
    if (cellGrid[row][col] == '0') {
      userView[row][col] = '0';
      
      if (row != 9 && col != 0 && cellGrid[row+1][col-1] != userView[row+1][col-1]) {
        check(row+1,col-1);
      }
      
      if (row != 9 && cellGrid[row+1][col] != userView[row+1][col]) {
        check(row+1,col);
      }
      
      if (row != 9 && col != 9 && cellGrid[row+1][col+1] != userView[row+1][col+1]) {
        check(row+1,col-1);
      }
      ////
      
      
      if (col != 0 && cellGrid[row][col-1] != userView[row][col-1]) {
        check(row,col-1);
      }
      
      if (col != 9 && cellGrid[row][col+1] != userView[row][col-1]) {
        check(row,col+1);
      }
      /////
      
      
      if (row != 0 && col != 0 && cellGrid[row-1][col-1] != userView[row-1][col-1]) {
        check(row-1,col-1);
      }
      
      if (row != 0 && cellGrid[row-1][col] != userView[row-1][col]) {
        check(row-1,col);
      }
      
      if (row != 0 && col != 9 && cellGrid[row-1][col+1] != userView[row-1][col+1]) {
        check(row-1,col+1);
      }
      
    }
    return 1;
  }
}


void flag(int row, int col) {
    userView[row][col] = 'F';
}

void checkWin() {
  if (count == 90) {
    printf("Congratulations! You win!\n");
    gameStatus=0;
    return 1;
  } else {
    return 0;
  }
}