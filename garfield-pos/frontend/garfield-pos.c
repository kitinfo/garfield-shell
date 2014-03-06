#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include <libpq-fe.h>
#include <errno.h>
#include <ctype.h>

#include "portability/sleep.h"
#include "portability/getpass.c"

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
		cfg_free(&cfg);
		return -1;
	}

	//if not using pgpass, ask for database password
	if(!cfg.db.use_pgpass){
		cfg.db.pass=calloc(sizeof(char),MAX_PASSWORD_LENGTH+1);
		if(!cfg.db.pass){
			printf("Failed to allocate memory\n");
			cfg_free(&cfg);
			return -1;
		}
		printf("Database access password: ");
		ask_password(cfg.db.pass, MAX_PASSWORD_LENGTH);
	}

	//check for sane config
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
