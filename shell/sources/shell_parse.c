#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../headers/shell_sec.h"
#include "../headers/shell_debug.h"
#include "../headers/shell_help.h"

void parseArguments(int argc, char* argv[]) {

	//parse arguments
	int i;
	for(i=1;i<argc;i++){
		if(*argv[i]=='-'){
			if(i+1<argc&&!strcmp(argv[i],"--user")){
				setUser(argv[i+1]);
				i++;
			}
			if(i+1<argc&&!strcmp(argv[i],"-u")){
				setUser(argv[i+1]);
				i++;
			}
			else if(i+1<argc&&!strcmp(argv[i],"--pass")){
				setPassword(argv[i+1]);
				i++;
			}
			else if(i+1<argc&&!strcmp(argv[i],"-p")){
				setPassword(argv[i+1]);
				i++;
			}
			else if(i+1<argc&&!strcmp(argv[i],"--help")){
				printHelp();
			}
			else if(i+1<argc&&!strcmp(argv[i],"-h")){
				printHelp();
			}
			else if(!strcmp(argv[i],"--debug")){
				setDebug(true);
			}
			else if(!strcmp(argv[i],"-d")){
				setDebug(true);
			}
			else if(!strcmp(argv[i],"--pgpass")){
				//TODO pgpass imp
			}
			else if(!strcmp(argv[i],"-g")){
				//TODO pgpass imp
			}
			else {
				printf("Invalid arguments.\n");
				printHelp();
			}
		}
	}
}
