#include <stdio.h>
#include <stdbool.h>
#include <libpq-fe.h>

int usage(char* fn){
	printf("garfield-user utility\n");
	return -1;
}

bool beVerbose=false;

//operation mdoes

int module_main(PGconn* db, int argc, char** argv){
	printf("Mode is %s\n",argv[0]);
	return 0;
}

#include "../garfield-common/module-argparse.c"