int queryUserID(PGconn* db, char* username){
	static const char* QUERY_UID="SELECT user_id FROM garfield.users WHERE user_name = $1";
	
	PGresult* result=PQexecParams(db,QUERY_UID,1,NULL,(const char**)&username,NULL,NULL,0);
	
	if(PQresultStatus(result)!=PGRES_TUPLES_OK||PQntuples(result)!=1){
		PQclear(result);
		return -1;
	}
	long uid=strtol(PQgetvalue(result,0,0),NULL,10);
	PQclear(result);
	if(errno==EINVAL){
		return -1;
	}
	return uid;
}

int buySnackByID(PGconn* db, int user, int snack){
	static const char* BUY_SNACK="SELECT garfield.snack_buy($1::integer, $2::integer)";
	
	user=htonl(user);
	snack=htonl(snack);
	
	const char *values[2]={(char*)&user, (char*)&snack};
	int lengths[2]={sizeof(user), sizeof(snack)};
	int binary[2]={1, 1};
	
	PGresult* result=PQexecParams(db,BUY_SNACK,2,NULL,values,lengths,binary,0);
	
	/*switch(PQresultStatus(result)){
		case PGRES_EMPTY_QUERY:
			printf("Empty query\n");
			break;
		case PGRES_COMMAND_OK:
			printf("Command ok\n");
			break;
		case PGRES_TUPLES_OK:
			printf("Got tuples\n");
			break;
		case PGRES_BAD_RESPONSE:
			printf("Server response bad\n");
			break;
		case PGRES_NONFATAL_ERROR:
			printf("Query resulted in nonfatal error\n");
			break;
		case PGRES_FATAL_ERROR:
			printf("Query resulted in fatal error\n");
			break;
		default:
			printf("Unknown result code\n");
	}*/
	
	if(PQresultStatus(result)!=PGRES_TUPLES_OK){
		printf("Failed to buy snack (%s)\n",PQresultErrorMessage(result));
		PQclear(result); 
		return -1;
	}
	
	PQclear(result);
	return 0;
}

int mode_buy(PGconn* db, int argc, char** argv){
	int i=0;
	int userid=-1;
	char* username=NULL;
	bool search_term=false;
	int term_start=1;
	int snack_id=-1;
	
	for(i=1;i<argc;i++){
		if(argv[i][0]=='-'){
			switch(argv[i][1]){
				case 'u':
					if(!username&&i+2<argc){
						username=argv[i+1];
						i++;
						term_start=i+1;
					}
					break;
				case 's':
					if(i+1<argc){//FIXME this breaks snack names starting with "-s" (unlikely, but possible)
						search_term=true;
						term_start=i+1;
					}
					break;
			}
		}
	}
	
	if(!username){
		username=PQuser(db); //FIXME errhandling?
	}
	
	//fetch user id
	userid=queryUserID(db,username);
	if(userid<0){
		printf("Could not resolve user name to user ID\n");
		return -1;
	}
	
	if(search_term){
		printf("Search terms: ");
		for(i=term_start;i<argc;i++){
			printf("%s ",argv[i]);
		}
	}
	printf("\n");
	
	if(search_term){
		//TODO search term for snack id
	}
	else{
		snack_id=strtol(argv[term_start],NULL,10);
		if(errno==EINVAL){
			snack_id=-1;
		}
	}
	
	if(snack_id<0){
		printf("Failed to resolve snack ID\n");
		return -1;
	}
	
	//TODO print price
	printf("Paying user: %s (%d)\nSnack ID: %d\n",username,userid,snack_id);
	
	//buy snack for id
	if(buySnackByID(db,userid,snack_id)<0){
		printf("Failed to buy snack :(\n");
	}
	else{
		printf("Snack bought.\n");
	}
	
	return -1;
}