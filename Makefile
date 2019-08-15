solver.exe: solver.c
	gcc -ggdb -O3 -o $@ $^

debug: solver.c
	gcc -ggdb -DDEBUG -o solver.exe $^
clean:
	del solver.exe