PGresult* querySnacksForTerms(PGconn* db, int argc, char** argv){
	//static const char* QUERY_SNACKS="SELECT snacks.snack_id, snack_name, snack_price FROM garfield.snacks JOIN garfield.snacks_available ON snacks_available.snack_id=snacks.snack_id WHERE snack_available AND (snack_name ILIKE $1 OR snack_barcode LIKE $1)";
	static const char* QUERY_SNACKS="SELECT snacks.snack_id, snack_name, snack_price, locations.location_name FROM garfield.snacks JOIN garfield.snacks_available ON snacks_available.snack_id = snacks.snack_id JOIN garfield.locations ON locations.location_id = snacks.location_id WHERE snack_available AND (snack_name ILIKE $1 OR snack_barcode LIKE $1)";
	int i=0,c=0;
	unsigned size=0;
	char* queryString=NULL;
	
	if(argc<1){
		return NULL;
	}
	
	//determine query arg length
	for(i=0;i<argc;i++){
		size+=strlen(argv[i])+1;
	}
	size+=2;

	//allocate memory for query arg
	queryString=malloc((size)*sizeof(char));
	if(!queryString){
		printf("Failed to allocate memory for query string\n");
		return NULL;
	}
	
	//build query arg
	*queryString='%';
	i=0;
	c=1;
	for(;i<argc;i++){
		strncpy(queryString+c,argv[i],strlen(argv[i]));
		c+=strlen(argv[i])+1;
		queryString[c-1]=' ';
	}
	queryString[c-1]='%';
	queryString[c]=0;
	
	if(beVerbose){
		printf("Query arg: %s\n",queryString);
	}
	
	//run query
	PGresult* result=PQexecParams(db,QUERY_SNACKS,1,NULL,(const char**)&queryString,NULL,NULL,0);
	
	free(queryString);
	
	if(PQresultStatus(result)!=PGRES_TUPLES_OK){//FIXME there might be another valid error code
		printf("Querying the snacks table failed (%s)\n",PQresultErrorMessage(result));
		PQclear(result); 
		return NULL;
	}
	return result;
}

int mode_find(PGconn* db, int argc, char** argv){
	int size=0;
	int i=0;
    
	//sanity check
	if(argc<2){
		printf("Not enough arguments for mode find\n");
		return -1;
	}

	PGresult* result=querySnacksForTerms(db,argc-1,argv+1);
	if(!result){
		printf("Failed to construct query\n");
		return -1;
	}

	size=PQntuples(result);
	if(beVerbose){
		printf("Query returned %d rows\n",size);
	}
	for(i=0;i<size;i++){
		printf("%5s (%3s) => %s @ %s Eur\n",PQgetvalue(result,i,0),PQgetvalue(result,i,3),PQgetvalue(result,i,1),PQgetvalue(result,i,2));
	}
	PQclear(result);
	return size;
}
