int mode_find(PGconn* db, int argc, char** argv){
	static const char* QUERY_SNACKS="SELECT snacks.snack_id, snack_name, snack_price FROM garfield.snacks JOIN garfield.snacks_available ON snacks_available.snack_id=snacks.snack_id WHERE snack_available AND (snack_name ILIKE $1 OR snack_barcode LIKE $1)";

	unsigned size=0;
	int i=0,c=0;
	char* queryString=NULL;
    
	//sanity check
	if(argc<2){
		printf("Not enough arguments for mode find\n");
		return -1;
	}
	
	//determine query arg length
	for(i=1;i<argc;i++){
		size+=strlen(argv[i])+1;
	}
	size+=2;
	
	//allocate memory for query arg
	queryString=malloc((size)*sizeof(char));
	if(!queryString){
		printf("Failed to allocate memory for query string!");
		return -1;
	}
	
	//build query arg
	*queryString='%';
	i=1;
	c=1;
	for(;i<argc;i++){
		strncpy(queryString+c,argv[i],strlen(argv[i]));
		c+=strlen(argv[i])+1;
		queryString[c-1]=' ';
	}
	queryString[c-1]='%';
	queryString[c]=0;
	//printf("Query arg: %s\n",queryString);
	
	//run query
	PGresult* result=PQexecParams(db,QUERY_SNACKS,1,NULL,(const char**)&queryString,NULL,NULL,0);
	
	if(PQresultStatus(result)!=PGRES_TUPLES_OK){
		//TODO print exact error message, check more return codes
		printf("Querying the snacks table failed!");
		free(queryString);
		PQclear(result); 
		return -1;
	}
	
	size=PQntuples(result);
	for(i=0;i<size;i++){
		printf("%5s => %s @ %s Eur\n",PQgetvalue(result,i,0),PQgetvalue(result,i,1),PQgetvalue(result,i,2));
	}
	free(queryString);
	PQclear(result);
	return size;
}