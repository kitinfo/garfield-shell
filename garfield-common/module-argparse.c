#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "getlogin.h"

#include "pqconnect.c"
#include "getpass.c"

#define MAX_PASS_LEN 254
#define MAX_USER_LEN 254

void meta_usage(char* module_name){
	        printf("Usage: %s [options] <mode> [mode-args]\n",module_name);
		printf("Available options:\n");
		printf("\t--user <user>\t\tDatabase user name\n");
		printf("\t--pass <password>\tDatabase password\n");
		printf("\t--server <server>\tDatabase server address\n");
		printf("\t--port <port>\t\tDatabase server port\n");
		printf("\t--dbname <dbname>\tDatabase name\n");
		printf("\t--verbose\t\tPrint some debug info\n");
		printf("\t--pgpass\t\tUse credentials supplied via .pgpass\n");
}

int main(int argc, char** argv){
	int i;
	PGconn* conn;
	
	char user[MAX_USER_LEN+1];
	*user=0;
	char pass[MAX_PASS_LEN+1];
	*pass=0;
	char* server="fsmi-db.fsmi.uni-karlsruhe.de";
	char* port="5432"; //garfield test instance is on 5435
	char* dbname="garfield";
	char* mode=NULL;
	bool use_pgpass=false;
	int mode_arg=-1;
	
	//parse arguments
	for(i=1;i<argc;i++){
		if(*argv[i]=='-'){
			if(i+1<argc&&!strcmp(argv[i],"--user")){
				strncpy(user,argv[i+1],MAX_USER_LEN);
				i++;
			}
			else if(i+1<argc&&!strcmp(argv[i],"--pass")){
				strncpy(pass,argv[i+1],MAX_PASS_LEN);
				i++;
			}
			else if(i+1<argc&&!strcmp(argv[i],"--server")){
				server=argv[i+1];
				i++;
			}
			else if(i+1<argc&&!strcmp(argv[i],"--port")){
				port=argv[i+1];
				i++;
			}
			else if(i+1<argc&&!strcmp(argv[i],"--dbname")){
				dbname=argv[i+1];
				i++;
			}
			else if(!strcmp(argv[i],"--verbose")){
				beVerbose=true;
			}
			else if(!strcmp(argv[i],"--pgpass")){
				use_pgpass=true;
			}
		}
		else{
			if(!mode){
				mode=argv[i];
				mode_arg=i;
			}
		}
	}
	
	if(!mode){
		printf("No operation specified\n");
		exit(usage(argv[0]));
	}
	
	//if no user supplied, get from environment
	if(*user==0){
		i=getlogin_r(user,MAX_USER_LEN);
		if(i!=0){
			printf("Failed to get user name (Return value %d, errno %d), try --user\n\n",i,errno);
			exit(usage(argv[0]));
		}
	}
	
	if(beVerbose){
		printf("Connecting to %s:%s\n",server,port);
	}
	
	//if none supplied, ask for password
	if(*pass==0&&!use_pgpass){
		printf("Enter Garfield / DB access password for %s: ",user);
		
		if(ask_password(pass,MAX_PASS_LEN)<0){
			printf("Aborting\n");
			exit(1);
		}
		
		printf("\n\n");
	}
	
	conn=database_connect(server, port, dbname, user, use_pgpass?NULL:pass, beVerbose);
	if(!conn){
		return -1;
	}
	
	i=module_main(conn,argc-mode_arg,argv+mode_arg);
	
	if(beVerbose){
		printf("Module finished with result %d\n",i);
	}
	PQfinish(conn);
	return i;
}
