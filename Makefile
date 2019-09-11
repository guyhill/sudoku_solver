solver16.exe: solver16.cpp
	g++ -std=c++17 -mavx2 -mfma -O3 -o $@ $^

solver5.exe: solver5.c
	gcc -ggdb -O3 -o $@ $^

solver4.exe: solver4.c
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
	gcc -ggdb -DDEBUG -o solver4.exe solver4.c
	gcc -ggdb -DDEBUG -o solver5.exe solver5.c

clean:
	del solver.exe solver2.exe solver3.exe solver4.exe solver5.exe solver3_mensa.exe