#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include <libpq-fe.h>

#include "portability/sleep.h"

#include "garfield-pos.h"
#include "config.c"
#include "argparse.c"
#include "pgconn.c"
#include "tcpconn.c"

int main(int argc, char** argv){
	CONFIG cfg;

	cfg_init(&cfg);

	//read commandline args
	if(!arg_parse(&cfg, argc-1, argv+1)){
		return -1;
	}

	//read config file
	if(!cfg.cfg_file){
		printf("No config file supplied\n");
		return -1;
	}
	if(!cfg_read(&cfg, cfg.cfg_file)){
		return -1;
	}
	if(!cfg_sane(&cfg)){
		cfg_free(&cfg);
		return -1;
	}

	//connect to database
	if(!pq_connect(&(cfg.db))){
		cfg_free(&cfg);
		return -1;
	}

	//connect to remote devices
	if(!comms_open(&cfg)){
		pq_close(&(cfg.db));
		cfg_free(&cfg);
		return -1;
	}
	
	//run the state machine
	//TODO

	comms_close(&cfg);
	pq_close(&(cfg.db));
	cfg_free(&cfg);
	return 0;
}
