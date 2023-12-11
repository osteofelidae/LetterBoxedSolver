// DEPENDENCIES
#include <stdio.h>
#include <string.h>

#include "letterboxed.h"


// FUNCTIONS
int in(  // Check if char in array
	char c,  // Char to check for
	char carr[],  // Array of characters
	int len  // Length of carr
	) {

	for (int i = 0; i < len; i++) {  // Iterate through list
		if (carr[i] == c) {  // If char is in list
			return 1;  // Return a positive
		}
	}
	return 0;  // If not, return a negative
}

int checkl(  // Check if 2 letters are valid
	char c1,  // First char
	char c2,  // Second char
	char sides[N_SIDES][N_LETTERS],  // Sides of puzzle
	int prev  // Previous side
	) {

	if (c1 == c2) {return -1;}  // Return false if same char

	// TODO make more efficient - separate handling of prev = -1 and prev = some value

	for(int i = 0; i < N_SIDES; i++) {  // Iterate through top level of list

		if (((prev == -1) || (i == prev)) && (in(c1, sides[i], N_LETTERS))) {  // If first or previous side and c1 in current side

			for(int j = 0; j < N_SIDES; j++) {  // Iterate through top level of list

				if ((j != i) && (in(c2, sides[j], N_LETTERS))) {  // If it is not the side of c1 and c2 in sides

					return j;  // Return the side which the thing was on

				}
			}
		}
	}
	return -1;  // Return negative
}

int checkw(  // Check if word is valid
	char *word,  // Word to check
	char sides[N_SIDES][N_LETTERS]  // Sides of puzzle
	) {

	int l = strlen(word);  // Length of word
	int s1 = -1;  // Side of previous char
	int s2;  // Side of current char

	for (int i = 1; i < l; i++) {  // Iterate through word

		s2 = checkl(word[i-1], word[i], sides, s1);  // Index of current letter or -1 if invalid

		//printf("c1:%c c2:%c s1:%i, s2:%i\n", word[i-1], word[i], s1, s2);
		
		if (s2 != -1) {s1 = s2;}  // If valid, set previous char
		else {return 0;}  // If invalid, return negative
	}
	return 1;  // Return positive
}

void check(  // Check all words in a file
	FILE *wordlist,  // Wordlist file pointer
	FILE *results,  // Results file pointer
	char sides[N_SIDES][N_LETTERS]  // Sides of puzzle
	) {

	char *line = NULL;  // One line of text

    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, wordlist)) != -1) {  // While next line exists
        
        line[strlen(line)-2] = '\0';  // Remove newline

        //printf("%s %d\n", line, strlen(line));
        
       	if (read > L_WORD+1 && checkw(line, sides)) {  // If valid word
       		
       		fprintf(results, "%s\n", line);  // Append word to outlist

       	}

    }

}

int ind(  // Get index of an element in an array
	char c,  // Element
	char arr[],  // Array
	int len  // Length of array
	) {

	for (int i = 0; i < len; i++) {  // Iterate through array
		if (arr[i] == c) {return i;}  // If element is found, return the index
	}
	return -1;  // Return -1

}

int clines(  // Count number of lines in file
	FILE *file  // Input file
	) {

	int count = 0;

	char *line = NULL;  // One line of text
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) {  // While next line exists

    	count++;

    }

    return count;

}

int pairw(
	char *w1,  // First word
	char *w2,  // Second word
	char letters[N_SIDES*N_LETTERS]  // All valid characters
	) {

	if (w1[0] != w2[strlen(w2)-1] && w2[0] != w1[strlen(w1)-1]) {return 0;}  // If invalid start and end characters, return negative

	int inde = -1;
	int counts[N_SIDES*N_LETTERS];  // How many times each letter appears
	for (int i = 0; i < N_SIDES*N_LETTERS; i++) {counts[i] = 0;}

	for (int i = 0; i < strlen(w1); i++) {  // Iterate through word 1
		inde = ind(w1[i], letters, N_SIDES*N_LETTERS);  // Find index of current letter in letters
		if (inde != -1) {  // if exists
			counts[inde] += 1;  // Add 1
		}
	}
	for (int i = 0; i < strlen(w2); i++) {  // Iterate through word 2
		inde = ind(w2[i], letters, N_SIDES*N_LETTERS);  // Find index of current letter in letters
		if (inde != -1) {  // if exists

			counts[inde] += 1;  // Add 1
		}
	}

	for (int i = 0; i < N_SIDES*N_LETTERS; i++) {
		//printf("%d: %d\n", i, counts[i]);
		if (counts[i] == 0) {return 0;}
	}

	return 1;

}

void pair(  // Pair words in a file
	FILE *valid,  // Valid words file pointer - output of check()
	FILE *results,  // Results file pointer
	char sides[N_SIDES][N_LETTERS]  // Sides of puzzle
	) {

	char letters[N_SIDES*N_LETTERS];  // All valid characters

	for (int i = 0; i < N_SIDES; i++) {  // Get all valid letters from puzzle sides
		for (int j = 0; j < N_LETTERS; j++) {
			letters[i*N_LETTERS + j] = sides[i][j];
		}
	}

	char *line = NULL;  // One line of text
	char curr[S_WORD];  // Current word being considered
    size_t len = 0;

    int nlines = clines(valid);  // Number of lines
    rewind(valid);

    for (int i = 0; i < nlines; i++) {  // Iterate nlines times
    	for (int j = 0; j < nlines; j++) {  // Iterate through file

    		getline(&line, &len, valid);  // Get line into *line
	    	line[strlen(line)-1] = '\0';  // Remove newline

	    	//printf("Curr: %s; Line: %s; i: %i; j: %i\n", curr, line, i, j);
    		
    		if (j > i) {  // If in scope

    			//fprintf(temp, "Curr: %s; Line: %s; i: %i; j: %i; pairw: %i\n", curr, line, i, j);

	    		if (pairw(curr, line, letters)) {  // If valid pair

	    			fprintf(results, "%s, %s\n", curr, line);  // Append words to outlist

	    		}

	    	} else if (j == i) {strcpy(curr, line);}  // If new word time, set current word to cursor
    	}
    	rewind(valid);
    }
}