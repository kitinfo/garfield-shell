#include <libpq-fe.h>
#define SSLMODE "require"

PGconn* database_connect(char* host, char* port, char* dbname, char* user, char* pass, bool verbose){
	PGconn* conn=NULL;
	
	//set up connection parameters
	char const* keywords[]={"host","port","dbname","user","password", "sslmode",NULL};
	char* values[]={host,port,dbname,user,pass,SSLMODE,NULL};
	
	if(!pass||*pass==0){
		keywords[4]=NULL;
	}
	
	//connect to server
	conn=PQconnectdbParams(keywords,(char const **)values,0);
	if(!conn){
		printf("libpq failed to allocate memory\n");
		return NULL;
	}
	
	//check connection status
	switch(PQstatus(conn)){
		case CONNECTION_OK:
			if(verbose){
				printf("Connected to database server...\n");
			}
			break;
		case CONNECTION_BAD:
			printf("Connection failure: %s\nAborting...\n",PQerrorMessage(conn));
			PQfinish(conn);
			return NULL;
		default:
			printf("Unknown status code, aborting.\n");
			PQfinish(conn);
			return NULL;
	}
	return conn;
}
