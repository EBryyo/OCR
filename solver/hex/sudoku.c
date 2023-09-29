#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int check_line (size_t* x, size_t* y, int tab[][16])
{
	//checks if line is valid

	int cur = tab[*y][*x];
	for(size_t X = 0; X < 16; X++)
	{
		if (X != *x && tab[*y][X] == cur)
			return 0;
	}
	return 1;
}

int check_column (size_t* x, size_t* y, int tab[][16])
{
	//checks if column is valid

	int cur = tab[*y][*x];
	for(size_t Y = 0; Y < 16; Y++)
	{
		if (Y != *y && tab[Y][*x] == cur)
			return 0;
	}
	return 1;
}

int check_box (size_t* x, size_t* y, int tab[][16])
{
	//checks if box is valid

	int cur = tab[*y][*x];
	size_t xbias = (*x / 4) * 4;
	size_t ybias = (*y / 4) * 4;
	
	for (size_t i = ybias; i < ybias + 4; i++)
	{
		for (size_t j = xbias; j < xbias + 4; j++)
		{
			if(!(j == *x && i == *y) && tab[i][j] == cur)
				return 0;
		}
	}
	return 1;
}

void next (size_t* x, size_t* y, int ref[][16])
{
	//moves pos to the next mutable position

	do {
		*x = (*x + 1) % 16;
		*y += !(*x);
	} while (ref[*y][*x] >= 0);
}

void prev (size_t* x, size_t* y, int ref[][16])
{
	//moves pos to the previous mutable position
	do {
		if (!*x)
		{
			*y = *y - 1;
			*x = 15;
		}
		else 
			*x = *x - 1;
	} while (ref[*y][*x] >= 0);
}

int possible (size_t* x, size_t* y, int tab[][16])
{
	//returns 0 if the current state of the board is impossible, else not 0
	//printf("exec: possible\n");
	return (check_line(x, y, tab) && check_column(x, y, tab)) && check_box(x, y, tab);
}

void mv_next (size_t* x, size_t* y, int tab[][16], int ref[][16])
{
	//moves the program forward in the board
	if (possible(x, y, tab))
	{
		next(x, y,ref);
		tab[*y][*x]++;
	}
	else tab[*y][*x]++;
}

void mv_prev (size_t* x, size_t* y, int tab[][16], int ref[][16])
{ //done
	//backtracks to next iterable state
	do {
		tab[*y][*x] = -1;
		prev(x, y,ref);
	} while (tab[*y][*x] == 15);
	tab[*y][*x]++;
}


void solve (int tab[][16])
{
	//solving process
	int ref[16][16]; 
	//deep copy of tab,
	//as to know which cells are immutable and which are not.
	for(size_t x = 0; x < 16; x++)
		for(size_t y = 0; y < 16; y++)
			ref[x][y] = tab[x][y];
	size_t posx = 0;
	size_t posy = 0;
	while(1)
	{
		if (posy > 15)
		{
			posx = 15;
			posy = 15;
			if (possible(&posx, &posy, tab))
				break;
			else 
			{
				if (ref[15][15])
					prev(&posx, &posy, ref);
				mv_prev(&posx, &posy, tab,ref);
			}
		}
		if (!possible(&posx, &posy, tab) && tab[posy][posx] == 15)
			mv_prev(&posx, &posy, tab,ref);
		else 
			mv_next(&posx, &posy, tab,ref);
	}
	
}
