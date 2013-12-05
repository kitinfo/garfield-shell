PG_INCLUDES=-I$(shell pg_config --includedir)
ifeq ($(PG_INCLUDES),-I)
	PG_INCLUDES=
endif


.PHONY: all windows

all:
	$(CC) -o garfield-snack -lpq -Wall $(PG_INCLUDES) garfield-snack.c

windows:
	cc -o garfield-snack.exe -lpq -ladvapi32 -lws2_32 -Wall garfield-snack.c
