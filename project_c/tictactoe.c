// source: tictactoe.c
// A program that determines the outcome of a tic tac toe game

// Name: Derek Dao
// CSID: ddao@moon.cs.torontomu.ca

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match = 0;  // Global variable used to keep track of the outcome of the game

void checkWinner( char win[]){				// function that determines whether there is a match
    if ( strcmp(win, "XXX") == 0){                      // in the gameboard
        match = 4;
    }

    else if ( strcmp(win, "OOO" ) == 0){
	match = 5;
    }
}

int main(int argc, char *argv[]){
    int *sequence;
    sequence = (int*) calloc(9, sizeof(int));    	// holds the file argument

// Error Checking Section:
    if ( argc == 3){

        if( strcmp(argv[1], "X") == 0 || strcmp(argv[1], "O") == 0){

            if( fopen(argv[2], "r") != NULL ){
                FILE *fptr;
                fptr = fopen(argv[2], "r");

                for (int i = 0; i < 9; i++){
                    if ( fscanf(fptr, "%d", &sequence[i]) != 1) {
                       fprintf(stderr, "Arg2: File must contain integers 1-9\n");
                       return 3;
                    }
                }
                fclose(fptr);
            }
            else{
                fprintf(stderr,"Arg2: Must be a readable file\n");
		return 2;
            }
        }
        else{
            fprintf(stderr, "Arg 1: must be X or O\n");
            return 1;
        }
    }
    else{
        fprintf(stderr, "Please enter exactly 2 arguments!\n");
        return 1;
    }


// Gameplay Section:
    char *player2;                        		// assign player 2 either X or O
    if ( strcmp(argv[1], "X") == 0 ){
         player2 = "O";
    }
    else{
       	 player2 = "X";
    }

    char *placements;					// array that holds the X and O markers
    placements = (char*) calloc(9, sizeof(char));

    char *pattern;					// A match variable use to determine if XXX or OOO exists in the game
    pattern = (char*) calloc(3, sizeof(char));

    int num;

    for (int j = 0; j < 9; j++){
         num = sequence[j];

         if ( j % 2 == 0){                		// Decides who places their marker first, and places it in the
             placements[num-1] = *argv[1];              // indicated location taken from the file argument
         }
         else{
	     placements[num-1] = *player2;
 	 }

         for (int m = 0; m < 9; m += 3){            	// check horizontal matches 
             for (int z = 0; z < 3; z++){
                 pattern[z] = placements[m+z];
             }
               checkWinner(pattern);
         }

         for (int n = 0; n < 3; n++){ 		    	//check vertical matches
              for (int y = 0; y < 3; y++){
                pattern[y] = placements[n + (3*y)];
              }
              checkWinner(pattern);
         }

         for (int p = 0; p < 3; p++){           	// check diagonal in position 1,5,9
	      pattern[p] = placements[p*4];
              checkWinner(pattern);
         }

         for (int q = 0; q<3; q++){            		// check diagonal in position 3,5,7
              pattern[q] = placements[2 + (q*2)];
              checkWinner(pattern);
         }

         if ( j == 8 && match != 4 && match != 5 ){     // checks the game for a tied outcome
             match = 6;
         }

         else if (match == 4 || match == 5){

             for (int b = 0; b < 9; b++){		// Turns remaining empty slots to -
                 if ( placements[b] == '\0' ){
                      placements[b] = '-';
                 }
             }

             break;
         }
    }

// prints out the outcome of the tic tac toe game
    printf("------------------\n");
    printf("%c | %c | %c\n", placements[0], placements[1],placements[2]);
    printf("%c | %c | %c\n", placements[3], placements[4],placements[5]);
    printf("%c | %c | %c\n", placements[6], placements[7],placements[8]);
    printf("------------------\n");

// free allocated memory
    free(sequence);
    free(placements);
    free(pattern);


// announces outcome of game
    if (match == 4){
         printf("X is the winner!\n");
         return 4;
    }
    else if (match == 5){
         printf("O is the winner!\n");
         return 5;
    }
    else if (match == 6){
         printf("The game ends in a tie.\n");
         return 6;
    }
}
