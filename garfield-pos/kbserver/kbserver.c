#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <malloc.h>
#include <inttypes.h>

#include "kbserver.h"

#include "config.c"
#include "mapping.c"
#include "cfgparse.c"
#include "argparse.c"

int usage(char* fn){
	printf("garfield-pos kbserver utility\n\n");	
	printf("Exposes evdev input via TCP in a configurable fashion\n");	
	return -1;
}

int main(int argc, char** argv){
	CONFIG_PARAMS cfg;
	int error=0;

	memset(&cfg, 0, sizeof(CONFIG_PARAMS));

	error=parse_arguments(argc-1, argv+1, &cfg);

	if(error!=0){
		printf("Failed to parse commandline arguments\n");
		usage(argv[0]);
		exit(error);
	}

	if(!cfg.config_file){
		printf("No config file supplied, aborting\n");
		exit(usage(argv[0]));
	}

	if(cfg.verbosity>0){
		printf("Using config file %s\n",cfg.config_file);
	}

	error=parse_config(cfg.config_file, &cfg);
	if(error!=0){
		printf("Failed to parse config file, aborting\n");
		exit(error);
	}

	printf("kbserver v%s starting\n",VERSION);

	return 0;
}
