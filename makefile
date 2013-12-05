all:
	-mkdir bin
	cd garfield-snack && make
	cd shell && make
	mv garfield-snack/garfield-snack bin/
	mv shell/garfield-shell bin/

windows:
	mkdir bin
	cd garfield-snack
	make windows
	cd ..
	mv garfield-snack/garfield-snack.exe bin/

install:
