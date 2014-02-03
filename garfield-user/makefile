PG_INCLUDES=-I$(shell pg_config --includedir)
ifeq ($(PG_INCLUDES),-I)
	PG_INCLUDES=
endif

.PHONY: all windows

all:
	$(CC) -o garfield-user -Wall $(PG_INCLUDES) garfield-user.c -lpq

windows:
	cc -o garfield-user.exe -lpq -ladvapi32 -Wall garfield-user.c
