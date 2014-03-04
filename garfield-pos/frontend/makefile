PG_INCLUDES=-I$(shell pg_config --includedir)
ifeq ($(PG_INCLUDES),-I)
	PG_INCLUDES=
endif


.PHONY: all

all:
	$(CC) -Wall -g $(PG_INCLUDES) garfield-pos.c -o garfield-pos -lpq
