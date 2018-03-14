PG_INCLUDES=-I$(shell pg_config --includedir)
ifeq ($(PG_INCLUDES),-I)
	PG_INCLUDES=
endif

GARFIELD_TOOLS_VERSION ?= $(shell git show-ref -s HEAD)

.PHONY: all windows

all:
	$(CC) -o garfield-snack -Wall $(PG_INCLUDES) -DTOOL_VERSION='"$(GARFIELD_TOOLS_VERSION)"' garfield-snack.c -lpq

windows:
	cc -o garfield-snack.exe -DTOOL_VERSION='"$(GARFIELD_TOOLS_VERSION)"' -lpq -ladvapi32 -lws2_32 -Wall garfield-snack.c
