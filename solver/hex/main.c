#include "file-tools.h"
#include "sudoku.h"
#include <stddef.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	int tab[16][16];
	//for(size_t x = 0; x < 9; x++)
	//	for(size_t y = 0; y < 9; y++)
	//		tab[x][y] = 2;
	
	if (argc != 2)
	{
		printf("number of parameters must be 1.\n");
		return 1;
	}

	if (read_board(argv[1],tab))
	{
		printf("named file must exist and be correctly formatted.\n");
		return 1;
	}
	
	//printf("\033[20A");
	//printf("\033[20D");
	//display board
	//print_sudoku(tab);
	
	solve(tab);
	
	write_board(argv[1],tab);
	//print_sudoku(tab);
	return 0;
}
