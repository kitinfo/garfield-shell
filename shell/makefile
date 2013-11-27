all:
	tcc -o garfield-shell -Wall main.c linux.c

windows:
	tcc -o garfield-shell.exe -ladvapi32 -lws2_32 -Wall main.c

gcc:
	gcc -o garfield-shell -Wall main.c linux.c 
debug gcc:
	gcc -g -o garfield-shell -Wall main.c linux.c
