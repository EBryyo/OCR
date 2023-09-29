#include <stdio.h>
#include <string.h>
#include <stddef.h>

int read_board(char file[], unsigned int res[9][9])
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
				res[y][x] = 0;
				x++;
				break;
			default:
				res[y][x] = ch - '0';
				x++;
				break;
		}
		lastch = ch;
	}

	fclose(textfile);
	return 0;
}

void write_board(char file[], unsigned int res[9][9])
{
	FILE* ptr;
	char* name = strcat(file,".result");
	ptr = fopen(name,"w");
	for (size_t y = 0; y < 9; y++)
	{
		if (y == 3 || y == 6)
			fprintf(ptr,"\n");
		for(size_t x = 0; x < 9;x++)
		{
			if (x == 3 || x == 6)
				fprintf(ptr," ");
			fprintf(ptr,"%u",res[y][x]);
		}
		fprintf(ptr,"\n");
	}
	fclose(ptr);
}
