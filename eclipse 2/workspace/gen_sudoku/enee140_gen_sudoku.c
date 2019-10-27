/*
 * enee140_gen_sudoku.c
 *
 *  Created on: May 2, 2015
 *      Author: rodrigopimenta
 */

#include "enee140_sudoku.h"
#include <string.h>

int main(int argc, char *argv[]){

	//Program needs 2 arguments and executable. Any other number would be an improper command line size.
	/*if(argc != 3){
	printf("Improper Command Line Size: %d", argc);
	}*/

	/* For BONUS:
	 * //Program needs 2 or 3 arguments and executable. Any other number would be an improper command line size.
	 * if(argc != 3 || argc !=4){
		printf("Improper Command Line Size: %d", argc);
	}*/
		if(argc==3){
		char filename[12]="";
		//Copy argument 1 into string filename.
		strcpy(filename,argv[1]);
		//Copy argument 2 into integer option. If argument 2 is not a number it will return 0.
		int option = atoi(argv[2]);
		/* For BONUS:
		 * int difficulty = atoi(argv[3]);
		 */

		int board[9][9];
		if((option & (1 << 0)) == 0){
			printf("Bit 0 is 0\n");
			srand(time(NULL));
			//For BONUS:
			/*int blanks;
			if(difficulty==1){
				//Random number between 31-45.
				int random = rand()%15;
				blanks = random+=31;
			}
			else if(difficulty==2){
				//Random number between 46-51.
				int random = rand()%6;
				blanks = random+=46;
			}
			else {
				//Random number between 52-61.
				int random = rand()%10;
				blanks = random+=52;
			}*/
			//Randomly generate number of blanks between 31 to 61.
			int random = rand()%31;
			int blanks = random+=31;


			printf("Blanks is %d\n", blanks);
			new_sudoku_board(board,blanks);
		}
		else{
			printf("Bit 0 is 1\n");
			int result=read_sudoku_board(filename, board);
			if(result == -1){
				printf("Error Creating Sudoku Board - File I/O");
				return 0;
			}
			else if(result == -2){
				printf("Error Creating Sudoku Board - Invalid Character Encountered");
				return 0;
			}
			else if(result == -3){
				printf("Error Creating Sudoku Board - Invalid File Format");
				return 0;
			}
		}
		if((option & (1 << 1)) != 0){
			printf("Bit 1 is 1\n");
			transform_permute_rows(board);
		}
		if((option & (1 << 2)) != 0){
			printf("Bit 2 is 1\n");
			transform_permute_bands(board);
		}
		if((option & (1 << 3)) != 0){
			printf("Bit 3 is 1\n");
			transform_permute_columns(board);
			printf("Function transform_permute_columns() is implemented");
		}
		if((option & (1 << 4)) != 0){
			printf("Bit 4 is 1\n");
			transform_permute_stacks(board);
			printf("Function transform_permute_stacks() is implemented");
		}
		if((option & (1 << 5)) != 0){
			printf("Bit 5 is 1\n");
			transform_flip_main_diagonal(board);
		}
		if((option & (1 << 6)) != 0){
			printf("Bit 6 is 1\n");
			transform_flip_minor_diagonal(board);
		}
		if((option & (1 << 7)) != 0){
			printf("Bit 7 is 1\n");
			print_sudoku_board(board);
		}
		if((option & (1 << 8)) != 0){
			printf("Bit 8 is 1\n");
			write_sudoku_board(filename, board);
		}
	}
		//BONUS
		if(argc==4){
				char filename[12]="";
				//Copy argument 1 into string filename.
				strcpy(filename,argv[1]);
				//Copy argument 2 into integer option. If argument 2 is not a number it will return 0.
				int option = atoi(argv[2]);

				int difficulty = atoi(argv[3]);


				int board[9][9];
				if((option & (1 << 0)) == 0){
					printf("Bit 0 is 0\n");
					srand(time(NULL));

					int blanks;
					if(difficulty==1){
						//Random number between 31-45.
						int random = rand()%15;
						blanks = random+=31;
					}
					else if(difficulty==2){
						//Random number between 46-51.
						int random = rand()%6;
						blanks = random+=46;
					}
					else {
						//Random number between 52-61.
						int random = rand()%10;
						blanks = random+=52;
					}

					printf("Blanks is %d\n", blanks);
					new_sudoku_board(board,blanks);
				}
				if((option & (1 << 7)) != 0){
							printf("Bit 7 is 1\n");
							print_sudoku_board(board);
						}
		}
	return 0;
}
