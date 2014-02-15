PGresult* getUserRowForId(PGconn* db, int userid){
	static const char* QUERY_USER_BY_ID="SELECT * FROM garfield.users WHERE user_id=$1::integer";
	
	userid=htonl(userid);

	const char *values[1]={(char*)&userid};
	int lengths[1]={sizeof(userid)};
	int binary[1]={1};
	
	PGresult* result=PQexecParams(db,QUERY_USER_BY_ID,1,NULL,values,lengths,binary,0);

	if(PQresultStatus(result)!=PGRES_TUPLES_OK){
		printf("User info query failed (%s)\n",PQresultErrorMessage(result));
		PQclear(result);
		return NULL;
	}
	return result;
}

PGresult* getUserRowsForTerms(PGconn* db, int argc, char** argv){
	static const char* QUERY_USERS_BY_TERMS="SELECT * FROM garfield.users WHERE user_name ILIKE $1 OR user_full_name ILIKE $1";

	unsigned size=0;
	int i=0,c=0;
	char* queryString=NULL;

	if(argc<1){
		return NULL;
	}

	//determine length
	for(i=0;i<argc;i++){
		size+=strlen(argv[i])+1;//arg + space
	}
	size+=2; //prepend + term

	//allocate buffer
	queryString=malloc(size*sizeof(char));
	if(!queryString){
		printf("Failed to allocate memory for query string\n");
		return NULL;
	}
	
	//prepare query argument
	*queryString='%';
	i=0; //argument position
	c=1; //character position
	for(;i<argc;i++){
		strncpy(queryString+c, argv[i], strlen(argv[i]));
		c+=strlen(argv[i])+1;
		queryString[c-1]=' ';
	}
	queryString[c-1]='%';
	queryString[c]=0;

	if(beVerbose){
		printf("Query argument is %s\n",queryString);
	}

	//run query
	PGresult* result=PQexecParams(db,QUERY_USERS_BY_TERMS,1,NULL,(const char**)&queryString,NULL,NULL,0);

	//free allocated memory
	free(queryString);

	//examine results
	if(PQresultStatus(result)!=PGRES_TUPLES_OK){
		printf("Failed to query the user table (%s)\n",PQresultErrorMessage(result));
		PQclear(result);
		return NULL;
	}

	return result;
}

int mode_list(PGconn* db, int argc, char** argv){
	long data=0;
	int size=0;
	PGresult* result=NULL;

	if(argc<2){
		printf("Not enough arguments for this mode\n");
		return -1;
	}

	data=strtoul(argv[1],NULL,10);

	if(errno!=0||data==0){
		//string query
		if(beVerbose){
			printf("Input seems to be a query string\n");
		}
		result=getUserRowsForTerms(db,argc-1,argv+1);
	}
	else{
		if(beVerbose){
			printf("Input seems to be a user id, asking for info on that\n");
		}
		result=getUserRowForId(db, data);
	}

	if(!result){
		printf("Failed to query for user info!\n");
		return -1;
	}

	size=PQntuples(result);
	if(beVerbose){
		printf("Query returned %d rows\n",size);
	}

	if(size==0){
		printf("No match found.\n");
	}

	for(data=0;data<size;data++){
		printf("%5s: %s (%s)\n",PQgetvalue(result,data,0),PQgetvalue(result,data,1),PQgetvalue(result,data,2));
	}

	PQclear(result);
	return size;
}
