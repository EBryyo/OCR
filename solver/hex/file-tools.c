#include <stdio.h>
#include <string.h>
#include <stddef.h>

int read_board(char file[], int res[16][16])
{
	FILE *textfile;
	char ch;
	char lastch;
	textfile = fopen(file,"r");
	if (textfile == NULL)
		return 1;
	
	size_t x = 0;
	size_t y = 0;
	while((ch = fgetc(textfile))!= EOF)
	{
		switch (ch)
		{
			case '\n':
				if (lastch != '\n')
					y++;
				x = 0;
				break;
			case ' ':
				break;
			case '.':
				res[y][x] = -1;
				x++;
				break;
			default:
				if (ch >= '0' && ch <= '9')
					res[y][x] = ch - '0';
				else
					res[y][x] = ch - 'A' + 10;
				if (res[y][x] > 15) return 1;
				x++;
				break;
		}
		lastch = ch;
	}

	fclose(textfile);
	return 0;
}

void write_board(char file[], int res[16][16])
{
	FILE* ptr;
	char* name = strcat(file,".result");
	ptr = fopen(name,"w");
	for (size_t y = 0; y < 16; y++)
	{
		if (y == 4 || y == 8 || y == 12)
			fprintf(ptr,"\n");
		for(size_t x = 0; x < 16;x++)
		{
			if (x == 4 || x == 8 || x == 12)
				fprintf(ptr," ");
			int c = res[y][x];
			if (c <= 9)
				fprintf(ptr,"%c", c + '0');
			else
				fprintf(ptr,"%c", c + 'A' -10);
		}
		fprintf(ptr,"\n");
	}
	fclose(ptr);
}
