// MACROS
#pragma once  // Pragma
#define N_SIDES 4  // Number of sides in puzzle
#define N_LETTERS 3  // Number of letters per side
#define L_WORD 3  // Minimum length of word
#define S_WORD 256  // Maximum length of word


// FUNCTIONS
int in(
	char,
	char [],
	int
	);

int checkl(
	char,
	char,
	char [N_SIDES][N_LETTERS],
	int
	);

int checkw(
	char *,
	char [N_SIDES][N_LETTERS]
	);

void check(
	FILE *,
	FILE *,
	char [N_SIDES][N_LETTERS]
	);

int pairw(
	char *,
	char *,
	char [N_SIDES*N_LETTERS]
	);

void pair(
	FILE *,
	FILE *,
	char [N_SIDES][N_LETTERS]
	);