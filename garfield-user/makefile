PG_INCLUDES=-I$(shell pg_config --includedir)
ifeq ($(PG_INCLUDES),-I)
	PG_INCLUDES=
endif

CFLAGS+=-Wall
LDFLAGS+=-lpq

GARFIELD_TOOLS_VERSION ?= $(shell git show-ref -s HEAD)

.PHONY: all windows

all:
	$(CC) $(CPPFLAGS) $(CFLAGS) -o garfield-user $(PG_INCLUDES) -DTOOL_VERSION='"$(GARFIELD_TOOLS_VERSION)"' garfield-user.c $(LDFLAGS)

windows:
	cc -o garfield-user.exe -DTOOL_VERSION='"$(GARFIELD_TOOLS_VERSION)"' -lpq -ladvapi32 -lws2_32 -Wall garfield-user.c
