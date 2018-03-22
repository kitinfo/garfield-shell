PREFIX ?= /usr/local
.PHONY: all windows install

export GARFIELD_TOOLS_VERSION=0.3

all:
	-mkdir -p bin
	$(MAKE) -C garfield-snack
	$(MAKE) -C garfield-user
	$(MAKE) -C shell
	$(MAKE) -C doc
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
	install -m 0755 bin/garfield-shell "$(DESTDIR)$(PREFIX)/bin"
	install -m 0755 bin/garfield-snack "$(DESTDIR)$(PREFIX)/bin"
	install -m 0755 bin/garfield-user "$(DESTDIR)$(PREFIX)/bin"
	$(MAKE) -C doc install

clean:
	$(RM) -r bin/
	$(MAKE) -C doc clean
