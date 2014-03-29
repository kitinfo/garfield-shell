#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <libpq-fe.h>

#ifndef _WIN32
	#include <arpa/inet.h>
#else
	#include <winsock2.h>
#endif

int usage(char* fn);

bool beVerbose=false;

//operation modes
#include "mode_list.c"
#include "mode_balance.c"
#include "mode_history.c"

int module_main(PGconn* db, int argc, char** argv){
	int i;
	if(!strcmp(argv[0],"list")||!strcmp(argv[0],"search")||!strcmp(argv[0],"find")){
		i=mode_list(db,argc,argv);
	}
	else if(!strcmp(argv[0],"balance")){
		i=mode_balance(db,argc,argv);
	}
	else if(!strcmp(argv[0],"history")){
		i=mode_history(db,argc,argv);
	}
	else{
		printf("No such mode \"%s\".\n",argv[0]);
		i=usage("garfield-user");
	}
	return i;
}

#include "../garfield-common/module-argparse.c"

int usage(char* fn){
	printf("garfield-user shell utility\n");
	printf("Interact with the user subsystem of Garfield\n\n");

	//options
	meta_usage(fn);

	//modes
	printf("\nAvailable modes:\n");
	printf("\tbalance\t\t\tPrint connecting users balance\n");
	printf("\tlist <id|name>\t\tSearch user by name\n");
	printf("\thistory\t\t\tDisplay account history\n");
	printf("\tstats\t\t\tDisplay account statistics\n");
	printf("\tdeposit\t\t\tAdd funds to snack account balance\n");

	return -1;
}
