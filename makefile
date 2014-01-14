INSTALLPATH=/usr/local/bin
.PHONY: all windows install

all:
	-mkdir -p bin
	@cd garfield-snack && make
	@cd garfield-shell-mono && make
	mv garfield-snack/garfield-snack bin/
	mv garfield-shell-mono/Shell.exe bin/garfield-shell

windows:
	mkdir bin
	cd garfield-snack && make windows
	mv garfield-snack/garfield-snack.exe bin/

install:
	install -m 0755 bin/garfield-shell $(INSTALLPATH)
	install -m 0755 bin/garfield-snack $(INSTALLPATH)
