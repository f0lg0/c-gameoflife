#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define ROWS 30
#define COLS 80

typedef int Board[ROWS][COLS];

/** 
 * randomly populates the board with either a 0 or a 1 
 * @param board a 2D Array of size [ROWS][COLS]
*/
void populateBoard(Board board) {
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
         	board[i][j] = rand() % 2;  
}

/** 
 * counts the neighbors of a cell
 * @param board a 2D Array of size [ROWS][COLS]
 * @param x x position of a cell on the board
 * @param y y position of a cell on the board
*/
int countNeighbors(Board board, int x, int y) {
	int sum = 0;

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {

			int row = (x + i + ROWS) % ROWS;
			int col = (y + j + COLS) % COLS;

			sum += board[row][col];
		}
	}

	sum -= board[x][y];

	return sum;
}

/** 
 * computes the next generation of cells following the game's rules
 * @param board a 2D Array of size [ROWS][COLS]
 * @param next another 2D Array of size [ROWS][COLS] where we will compute the new values
*/
void computeNewGen(Board board, Board next) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			int state = board[i][j];

			int neighbors = countNeighbors(board, i, j);

			if (state == 0 && neighbors == 3) {
				next[i][j] = 1;
			} else if (state == 1 && (neighbors < 2 || neighbors > 3)) {
				next[i][j] = 0;
			} else {
				next[i][j] = board[i][j];
			}
			
		}
	}
}

/** 
 * prints the board using special characters
 * @param board a 2D Array of size [ROWS][COLS]
*/
void printBoard(Board board) {
   	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (board[i][j] == 1) {
				printf("█");
			} else {
				printf("░");
			}
			
		}
		printf("\n");
	}
}

int main() {
	srand(time(0)); 

	/**
	 * * gen 0: 
	 * generating a randomly populated board 
	*/
	Board board;
	populateBoard(board);

	/**
	 * * gen 0:
	 * copying board cells to another board (next)
	 * we will compute the next gen in "next"
	*/
	Board next;
	memcpy(next, board, sizeof(board));

	/**
	 * * gen 0:
	 * creating pointers to the boards
	 * this way we avoid using memcpy later on in the code 
	*/
	Board *pboard = &board;
	Board *pnext = &next; 

	while (1) {
		system("clear");
		printBoard(pboard);

		// computing the next gen
		computeNewGen(pboard, pnext);
		
		/**
		 * swapping the boards: "board" gets the computed value
		 * which is "next" and "next" gets the old value of "board". 
		 * We don't really need to assign to "next" those specific values, we could even 
		 * make it point to an empty board. Swapping them avoids allocating more memory. 
		*/
		Board *temp = pboard;
		pboard = pnext;
		pnext = temp;

		usleep(1000000/4); // lowering the frame rate
	}	

	return 0;
}