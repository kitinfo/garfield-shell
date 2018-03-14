#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <malloc.h>
#include <stdbool.h>
#include <libpq-fe.h>

#define TOOL_NAME "garfield-snack"

#ifndef _WIN32
	#include <arpa/inet.h>
#else
	#include <winsock2.h>
#endif

int usage(char* fn);

bool beVerbose=false;

//operation modes
#include "mode_stats.c"
#include "mode_find.c"
#include "mode_buy.c"	//buy needs find

int module_main(PGconn* db, int argc, char** argv){
	int i;
	//select garfield-snack mode
	if(!strcmp(argv[0],"buy")){
		i=mode_buy(db,argc,argv);
	}
	else if(!strcmp(argv[0],"find")||!strcmp(argv[0],"search")){
		i=mode_find(db,argc,argv);
	}
	else if(!strcmp(argv[0],"stats")||!strcmp(argv[0],"info")){
		i=mode_stats(db,argc,argv);
	}
	else{
		printf("No such mode \"%s\".\n",argv[0]);
		i=usage("garfield-snack");
	}
	return i;
}

#include "../garfield-common/module-argparse.c"

int usage(char* fn){
	printf("garfield-snack shell utility\n");
	printf("Interact with the snack subsystem of Garfield\n\n");
		
	//options
	meta_usage(fn);

	//modes
	printf("\nAvailable modes:\n");
	printf("\tfind <term>\t\tSearch by barcode/snack name\n");
	printf("\tbuy <snack-id>\t\tBuy snack by ID\n");
	printf("\tbuy -s <term>\t\tBuy snack by name (if search result is one row)\n");
	printf("\tbuy -u <user> <snackid>\tBuy snack for specified user\n");
	printf("\tinfo <snackid>\t\tQuery information for a given snack\n");
	
	//examples
	printf("\nExamples:\n");
	printf("%s find mate\t\tFind snacks matching *mate*\n",fn);
	printf("%s find ritter sport\tFind snacks matching *ritter sport*\n",fn);
	printf("%s buy -u user 828\t\tBuy snack #828 as 'user'\n",fn);
	printf("%s buy -s <barcode>\t\tBuy snack by barcode\n",fn);
	printf("%s info 828\t\t\tShow information about snack #828\n",fn);
	return -1;
}
