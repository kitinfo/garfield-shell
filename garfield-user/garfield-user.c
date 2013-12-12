#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <libpq-fe.h>

int usage(char* fn){
	printf("garfield-user utility\n");
	return -1;
}

bool beVerbose=false;

//operation modes
#include "mode_list.c"

int module_main(PGconn* db, int argc, char** argv){
	int i;
	if(!strcmp(argv[0],"list")){
		i=mode_list(db,argc,argv);
	}
	else{
		printf("No such mode \"%s\".\n",argv[0]);
		i=usage("garfield-user");
	}
	return i;
}

#include "../garfield-common/module-argparse.c"