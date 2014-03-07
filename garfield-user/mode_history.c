PGresult* queryUserHistory(PGconn* db, int numRows){
	static const char* QUERY_USER_HISTORY="\
	SELECT \
		to_char(user_trans_log_timestamp, 'YYYY-MM-DD HH24:MI:SS') AS timestamp, \
		user_name AS performer, \
		snack_name AS desc, \
		user_trans_log_quantity AS balance, \
		snack_sales_log.type_id AS type \
	FROM garfield.user_trans_log \
	JOIN garfield.snack_user_buy_log \
		ON (user_trans_log.user_trans_log_id = snack_user_buy_log.user_trans_log_id) \
	JOIN garfield.snack_sales_log \
		ON (snack_user_buy_log.snack_sales_log_id = snack_sales_log.snack_sales_log_id) \
	JOIN garfield.snacks \
		ON (snack_sales_log.snack_id = snacks.snack_id) \
	JOIN garfield.users \
		ON (users.user_id=user_trans_log_performed_by_user_id) \
	\
	UNION ALL SELECT \
		to_char(user_trans_log_timestamp, 'YYYY-MM-DD HH24:MI:SS') AS timestamp, \
		user_name as performer, \
		user_to_user_trans_log_description AS desc, \
		user_trans_log_quantity AS balance, user_trans_log.type_id AS type \
	FROM garfield.user_trans_log \
	JOIN garfield.user_to_user_trans_log \
		ON (user_trans_log.user_trans_log_id = user_trans_log_target_id) \
	JOIN garfield.users \
		ON (users.user_id=user_trans_log_performed_by_user_id) \
	UNION ALL SELECT \
		to_char(user_trans_log_timestamp, 'YYYY-MM-DD HH24:MI:SS') AS timestamp, \
		user_name as performer, \
		'' AS desc, \
		user_trans_log_quantity AS balance, \
		user_trans_log.type_id AS type \
	FROM garfield.user_trans_log \
	JOIN garfield.users \
		ON (users.user_id=user_trans_log_performed_by_user_id) \
	WHERE \
		type_id != 'TRANSFER' \
		AND type_id != 'SNACK_BUY' \
	ORDER BY timestamp DESC \
	LIMIT $1::integer;";
	
	numRows=htonl(numRows);

	const char *values[1]={(char*)&numRows};
	int lengths[1]={sizeof(numRows)};
	int binary[1]={1};
	
	PGresult* result=PQexecParams(db,QUERY_USER_HISTORY,1,NULL,values,lengths,binary,0);

	if(PQresultStatus(result)!=PGRES_TUPLES_OK){
		printf("User history query failed (%s)\n",PQresultErrorMessage(result));
		PQclear(result);
		return NULL;
	}
	return result;
}


int mode_history(PGconn* db, int argc, char** argv){
	int numRows=10;
	int i=0, size=0;

	if(argc>1){
		numRows=strtoul(argv[1],NULL,10);
		if(errno!=0||numRows==0){
			printf("Invalid number of history items passed\n");
			return -1;
		}
	}
	
	if(beVerbose){
		printf("Querying for %d history items\n",numRows);
	}
		
	PGresult* historyRows=queryUserHistory(db,numRows);
	if(!historyRows){
			printf("Failed to query user history!\n");
			return -1;
	}

	size=PQntuples(historyRows);
	if(beVerbose){
		printf("Received %d history items\n",size);
	}

	for(i=0;i<size;i++){
		printf("%s: %s %s %s performed by %s\n",PQgetvalue(historyRows,i,0),PQgetvalue(historyRows,i,4),PQgetvalue(historyRows,i,2),PQgetvalue(historyRows,i,3),PQgetvalue(historyRows,i,1));
	}

	return size;
}
