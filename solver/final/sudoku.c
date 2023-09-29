#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int check_line (size_t* x, size_t* y, unsigned int tab[][9])
{ 
	//checks if line is valid
	
	unsigned int cur = tab[*y][*x];
	for(size_t X = 0; X < 9; X++)
	{
		if (X != *x && tab[*y][X] == cur)
			return 0;
	}
	return 1;
}

unsigned int check_column (size_t* x, size_t* y, unsigned int tab[][9])
{
	//checks if column is valid
	
	unsigned int cur = tab[*y][*x];
	for(size_t Y = 0; Y < 9; Y++)
	{
		if (Y != *y && tab[Y][*x] == cur)
			return 0;
	}
	return 1;
}

unsigned int check_box (size_t* x, size_t* y, unsigned int tab[][9])
{
	//checks if box is valid
	
	unsigned int cur = tab[*y][*x];
	size_t xbias = (*x / 3) * 3;
	size_t ybias = (*y / 3) * 3;
	
	for (size_t i = ybias; i < ybias + 3; i++)
	{
		for (size_t j = xbias; j < xbias + 3; j++)
		{
			if(!(j == *x && i == *y) && tab[i][j] == cur)
				return 0;
		}
	}
	return 1;
}

void next (size_t* x, size_t* y, unsigned int ref[][9])
{
	//moves pos to the next mutable position
	do {
		*x = (*x + 1) % 9;
		*y += !(*x);
	} while (ref[*y][*x]);
}

void prev (size_t* x, size_t* y, unsigned int ref[][9])
{
	//moves pos to the previous mutable position
	do {
		if (!*x)
		{
			*y = *y - 1;
			*x = 8;
		}
		else
			*x = *x - 1;
	} while (ref[*y][*x]);
}

unsigned int possible (size_t* x, size_t* y, unsigned int tab[][9])
{ 
	//returns 0 if the current state of the board is impossible, else not 0
	//printf("exec: possible\n");
	return (check_line(x, y, tab) && check_column(x, y, tab))
		&& check_box(x, y, tab);
}

void mv_next (size_t* x, size_t* y, unsigned int tab[][9], unsigned int ref[][9])
{ 
	//moves the program forward in the board

	if (possible(x, y, tab))
	{
		next(x, y, ref);
		tab[*y][*x]++;
	}
	else tab[*y][*x]++;
}

void mv_prev (size_t* x, size_t* y, unsigned int tab[][9], unsigned int ref[][9])
{ 
	//backtracks to next iterable state

	do {
		tab[*y][*x] = 0;
		prev(x, y, ref);
	} while (tab[*y][*x] == 9);
	tab[*y][*x]++;
}


void solve (unsigned int tab[][9])
{
	//solving process
	unsigned int ref[9][9];
	//deep copy of tab,
	//as to know which cells are immutable and which are not.
	for(size_t x = 0; x < 9; x++)
		for(size_t y = 0; y < 9; y++)
			ref[x][y] = tab[x][y];
	size_t posx = 0;
	size_t posy = 0;
	//array representing the current position
	while(1)
	{
			//iteration
		
		if (posy > 8)
		{
			posy = 8;
			posx = 8;
			if (possible(&posx, &posy, tab))
				break;
			else
			{
				if (ref[8][8])
					prev(&posx, &posy,ref);
				mv_prev(&posx, &posy,tab,ref);
			}
		}
		if (!possible(&posx, &posy, tab) && tab[posy][posx] == 9)
			mv_prev(&posx, &posy, tab,ref);
		else
			mv_next(&posx ,&posy, tab,ref);
	}
}
