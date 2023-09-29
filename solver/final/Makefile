solver: main.c sudoku.o file-tools.o
	gcc -o solver -Wall -Wextra -Werror main.c file-tools.o sudoku.o

file-tools.o: file-tools.c
	gcc -Wall -Wextra -Werror -c file-tools.c

sudoku.o: sudoku.c
	gcc -c -Wall -Wextra -Werror sudoku.c

clean:
	rm -f *.o
	rm -f ${DEP}
	rm -f ${PRG}
	rm solver
	rm -f *.gch
