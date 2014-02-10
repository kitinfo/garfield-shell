INSTALLPATH=/usr/local/bin
.PHONY: all windows install

all:
	-mkdir -p bin
	@cd garfield-snack && make
	@cd shell && make
	mv garfield-snack/garfield-snack bin/
	mv shell/garfield-shell bin/

windows:
	mkdir bin
	cd garfield-snack && make windows
	mv garfield-snack/garfield-snack.exe bin/

install:
	install -m 0755 bin/garfield-shell $(INSTALLPATH)
	install -m 0755 bin/garfield-snack $(INSTALLPATH)
