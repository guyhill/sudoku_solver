solver3_mensa.exe: solver3_mensa.c
	gcc -ggdb -O3 -o $@ $^

solver3.exe: solver3.c
	gcc -ggdb -O3 -o $@ $^

solver2.exe: solver2.c
	gcc -ggdb -O3 -o $@ $^

solver.exe: solver.c
	gcc -ggdb -O3 -o $@ $^

debug: solver.c solver2.c
	gcc -ggdb -DDEBUG -o solver.exe solver.c
	gcc -ggdb -DDEBUG -o solver2.exe solver2.c
	gcc -ggdb -DDEBUG -o solver3.exe solver3.c
	gcc -ggdb -DDEBUG -o solver3_mensa.exe solver3_mensa.c

clean:
	del solver.exe solver2.exe solver3.exe solver3_mensa.exe