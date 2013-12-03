PGresult* queryStatsForId(PGconn* db, int snackid){
	static const char* QUERY_STATS_BY_ID="SELECT snacks.snack_id, snack_name, count(snack_sales_log.snack_sales_log_id) AS sales, snack_barcode, snack_price, snack_timestamp, min(locations.location_name) AS location, min(users.user_name) AS user,\
											min(users.user_full_name) AS user_name FROM garfield.snacks LEFT JOIN garfield.snack_sales_log ON snack_sales_log.snack_id=snacks.snack_id LEFT JOIN garfield.users ON snacks.snack_modifed_by_user_id=users.user_id \
											JOIN garfield.locations ON snacks.location_id = locations.location_id WHERE snacks.snack_id=$1::integer GROUP BY snacks.snack_id";
	
	snackid=htonl(snackid);
	
	const char *values[1]={(char*)&snackid};
	int lengths[1]={sizeof(snackid)};
	int binary[1]={1};
	
	PGresult* result=PQexecParams(db,QUERY_STATS_BY_ID,1,NULL,values,lengths,binary,0);
	
	if(PQresultStatus(result)!=PGRES_TUPLES_OK){
		printf("Failed to query snack statistics (%s)\n",PQresultErrorMessage(result));
		PQclear(result); 
		return NULL;
	}
	
	return result;
}

int mode_stats(PGconn* db, int argc, char** argv){
	int i=0;
	
	if(argc<2){
		printf("Not enough arguments for this mode\n");
		return -1;
	}
	
	int snackid=-1;
	for(i=1;i<argc;i++){
		errno=0;
		snackid=strtol(argv[i],NULL,10);
		if(errno!=0){
			if(beVerbose){
				printf("Argument \"%s\" is not a valid snack ID\n",argv[i]);
			}
			snackid=-1;
			break;
		}
		printf("\n");
		if(beVerbose){
			printf("Querying info for snack %d\n",snackid);
		}
		PGresult* result=queryStatsForId(db,snackid);
		if(!result){
			snackid=-1;
			break;
		}
		if(PQntuples(result)==1){
			printf("%s (ID %s)\n",PQgetvalue(result,0,1),PQgetvalue(result,0,0));
			if(strlen(PQgetvalue(result,0,3))>2){
				printf("Barcode: %s\n",PQgetvalue(result,0,3));
			}
			printf("Price: %s\n",PQgetvalue(result,0,4));
			printf("Sales: %s\n",PQgetvalue(result,0,2));
			printf("Location: %s\n",PQgetvalue(result,0,6));
			if(strlen(PQgetvalue(result,0,5))>2){
				printf("Last modification: %s by %s (%s)\n",PQgetvalue(result,0,5),PQgetvalue(result,0,7),PQgetvalue(result,0,8));
			}
		}		
		else{
			printf("Invalid result returned for snack %d\n",snackid);
		}
		PQclear(result);
	}
	
	return snackid;
}