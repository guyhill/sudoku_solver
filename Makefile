solver.exe: solver.c
	gcc -ggdb -O3 -o $@ $^

clean:
	del solver.exe