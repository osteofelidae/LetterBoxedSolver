// DEPENDENCIES
#include <stdio.h>
#include <string.h>

#include "letterboxed.h"


// MACROS
#define WORDLIST "wordlists/english_scrabble.txt"
#define INTER "results/possiblewords.txt"
#define OUTFILE "results/results.txt"


// FUNCTIONS
void freset(  // Reset file contents
	char *path  // File path
	) {

	FILE *file = fopen(path, "w");
	fprintf(file, "\n");
	fclose(file);

}


// MAIN
int main(
	int argc,
	char *argv[]
	) {

	char sides[4][3] = {{'a'}};  // Initialize
	char *outpath = OUTFILE;

	for (int i = 1; i < argc; i++) {  // Iterate through command line args
		
		if (strcmp(argv[i], "-s") == 0) {  // Sides

			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 3; k++) {
					sides[j][k] = argv[i+j+1][k];
				}
			}

			i += 4;
		} else if (strcmp(argv[i], "-o") == 0) {  // Output file
			outpath = argv[i+1];
			i += 1;
		}
	}

	freset(INTER);
	freset(OUTFILE);
	FILE *wordlist = fopen(WORDLIST, "r");  // Wordlist
	FILE *inter = fopen(INTER, "a");  // Possible words
	check(wordlist, inter, sides);  // Get possible words
	fclose(wordlist);
	fclose(inter);

	FILE *possible = fopen(INTER, "r");
	FILE *outfile = fopen(outpath, "a");
	pair(possible, outfile, sides);  // Get pairs
	fclose(possible);
	fclose(outfile);

}
/*
int main(
	int argc,
	char *argv[]
	) {

	// TODO UI

	char sides[4][3] = {
		{'p', 'k', 'a'},
		{'i', 'b', 'o'},
		{'r', 's', 'w'},
		{'t', 'c', 'd'}
	};

	char letters[N_SIDES*N_LETTERS];  // All valid characters

	for (int i = 0; i < N_SIDES; i++) {  // Get all valid letters from puzzle sides
		for (int j = 0; j < N_LETTERS; j++) {
			letters[i*N_LETTERS + j] = sides[i][j];
		}
	}

	//printf("Pairw: %i\n", pairw("jaywalker", "rough", letters));
	//printf("%i\n", checkw("ware", sides));

	FILE *infile = fopen("wordlists/english_scrabble.txt", "r");
	FILE *outfile = fopen("results.txt", "a");

	check(infile, outfile, sides);

	fclose(infile);
	fclose(outfile);

	//return -1;

	FILE *infile1 = fopen("results.txt", "r");
	FILE *outfile1 = fopen("results2.txt", "a");

	//printf("%i lines\n", clines(infile));

	pair(infile1, outfile1, sides);

	fclose(infile1);
	fclose(outfile1);

}
*/