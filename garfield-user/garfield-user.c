#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <libpq-fe.h>

#define TOOL_NAME "garfield-user"

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
#include "mode_deposit.c"

int module_main(PGconn* db, int argc, char** argv){
	if(!strcmp(argv[0], "list") || !strcmp(argv[0], "search") || !strcmp(argv[0], "find")){
		return mode_list(db,argc,argv);
	}
	else if(!strcmp(argv[0], "balance")){
		return mode_balance(db,argc,argv);
	}
	else if(!strcmp(argv[0], "history")){
		return mode_history(db,argc,argv);
	}
	else if(!strcmp(argv[0], "deposit")||!strcmp(argv[0], "withdraw")){
		return mode_deposit(db,argc,argv);
	}
	else{
		printf("No such mode \"%s\".\n",argv[0]);
		return usage("garfield-user");
	}
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
	printf("\tdeposit <amount>\t\t\tAdd funds to snack account balance\n");
	printf("\twithdraw <amount>\t\t\tWithdraw funds from snack account balance\n");

	return -1;
}
