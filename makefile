all:
	mkdir -p bin
	cd garfield-snack && make
	cd shell && make
	mv garfield-snack/garfield-snack bin/
	mv shell/garfield-shell bin/

windows:
	

gcc:
	

install:
