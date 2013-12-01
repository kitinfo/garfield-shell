#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <malloc.h>
#include <postgresql/libpq-fe.h> //the path for this header differs by distribution.

#ifndef _WIN32
	#include <arpa/inet.h>
#else
	#include <winsock2.h>
#endif

//portability hacks
#include "getchar.h"
#include "getlogin.h"

bool beVerbose=false;

//operation modes
#include "mode_find.c"
#include "mode_buy.c"	//buy needs find

#define MAX_PASS_LEN 254
#define MAX_USER_LEN 254

int usage(char* fn){
	printf("garfield-snack shell utility\n");
	
	//options
	printf("Usage: %s [options] <mode> [mode-args]\n",fn);
	printf("Available options:\n");
	printf("\t--user <user>\t\tDatabase user name\n");
	printf("\t--pass <password>\tDatabase password\n");
	printf("\t--server <server>\tDatabase server address\n");
	printf("\t--port <port>\t\tDatabase server port\n");
	printf("\t--dbname <dbname>\tDatabase name\n");
	printf("\t--verbose\t\tPrint some debug info\n");
	
	//modes
	printf("\nAvailable modes:\n");
	printf("\tfind <term>\t\tSearch by barcode/snack name\n");
	printf("\tbuy <snack-id>\t\tBuy snack by ID\n");
	printf("\tbuy -s <term>\t\tBuy snack by name (if search result is one row)\n");
	printf("\tbuy -u <user> <snackid>\tBuy snack for specified user\n");
	
	//examples
	printf("\nExamples:\n");
	printf("%s find mate\t\tFind snacks named *mate*\n",fn);
	printf("%s find ritter sport\tFind snacks named *ritter sport*\n",fn);
	printf("%s buy -u user 828\tBuy snack #828 as 'user'\n",fn);
	return -1;
}

int main(int argc, char** argv){
	int i,c;
	
	PGconn* conn;
	
	char user[MAX_USER_LEN+1];
	*user=0;
	char pass[MAX_PASS_LEN+1];
	*pass=0;
	char* server="fsmi-db";
	char* port="5435";
	char* dbname="garfield";
	char* mode=NULL;
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
			printf("Failed to get user name, try --user\n\n");
			exit(usage(argv[0]));
		}
	}
	
	//if none supplied, ask for password
	if(*pass==0){
		printf("Enter Garfield / DB access password for %s: ",user);
		i=0;
		do{
			c=getch();
			if(c==3){
				//handle sigint during input
				return -2;
			}
			if(c!='\n'&&c!='\r'&&c!=EOF){
				//printf("%c|%x\n",c,c);
				pass[i]=c;
			}
			else{
				break;
			}
			i++;
		}
		while(i<MAX_PASS_LEN);
		pass[i]=0;
		
		printf("\n");
	}
	
	char const* keywords[]={"host","port","dbname","user","password",NULL};
	char* values[]={server,port,dbname,user,pass,NULL};
	
	conn=PQconnectdbParams(keywords,(char const **)values,0);
	if(!conn){
		printf("libpq failed to allocate memory\n");
		exit(-1);
	}
	
	switch(PQstatus(conn)){
		case CONNECTION_OK:
			if(beVerbose){
				printf("Connected to database server...\n");
			}
			break;
		case CONNECTION_BAD:
			printf("Connection bad :(\nAborting...\n");
			PQfinish(conn);
			return -1;
		default:
			printf("Unknown status code, aborting.\n");
			PQfinish(conn);
			return -1;
	}
	
	if(!strcmp(mode,"buy")){
		i=mode_buy(conn,argc-mode_arg,argv+mode_arg);
	}
	else if(!strcmp(mode,"find")){
		i=mode_find(conn,argc-mode_arg,argv+mode_arg);
	}
	else{
		printf("No such mode %s.",mode);
		i=usage(argv[0]);
	}
	
	if(beVerbose){
		printf("Mode %s finished with result %d\n",mode,i);
	}
	PQfinish(conn);
	return i;
}