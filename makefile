INSTALLPATH=/usr/local/bin
.PHONY: all windows install

all:
	-mkdir -p bin
	@cd garfield-snack && make
	@cd garfield-user && make
	@cd shell && make
	mv garfield-snack/garfield-snack bin/
	mv garfield-user/garfield-user bin/
	mv shell/garfield-shell bin/

windows:
	mkdir bin
	cd garfield-snack && make windows
	cd garfield-user && make windows
	mv garfield-snack/garfield-snack.exe bin/
	mv garfield-user/garfield-user.exe bin/

install:
	install -m 0755 bin/garfield-shell $(INSTALLPATH)
	install -m 0755 bin/garfield-snack $(INSTALLPATH)
	install -m 0755 bin/garfield-user $(INSTALLPATH)
