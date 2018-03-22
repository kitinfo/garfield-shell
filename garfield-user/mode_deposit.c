int queryUserID(PGconn* db, char* username){
	static const char* QUERY_UID = "SELECT user_id FROM garfield.users WHERE user_name = $1";
	PGresult* result = PQexecParams(db, QUERY_UID, 1, NULL, (const char**)&username, NULL, NULL, 0);
	if(PQresultStatus(result) != PGRES_TUPLES_OK || PQntuples(result) != 1){
		PQclear(result);
		return -1;
	}

	long uid = strtol(PQgetvalue(result, 0, 0), NULL, 10);
	PQclear(result);

	if(errno == EINVAL){
		return -1;
	}

	return uid;
}


int selectCashRegister(PGconn* db){
	static const char* QUERY_CASH_REGISTERS="SELECT cash_box_id, cash_box_name, location_name "
		"FROM garfield.cash_boxes "
		"JOIN garfield.locations USING (location_id)";

	size_t i;
	char read_buffer[20] = "";

	PGresult* result = PQexec(db, QUERY_CASH_REGISTERS);
	if(!result){
		printf("Failed to execute cash register query\n");
		return -1;
	}

	if(PQresultStatus(result) != PGRES_TUPLES_OK){
		printf("Cash register query returned failure\n");
		PQclear(result);
		return -1;
	}

	if(PQntuples(result) < 1){
		printf("No registers seem to have been defined\n");
		PQclear(result);
		return -1;
	}

	printf("Select cash register to be used in transaction:\n");

	for(i = 0; i < PQntuples(result); i++){
		printf("\t%s: %s (%s)\n",
				PQgetvalue(result, i, 0),
				PQgetvalue(result, i, 1),
				PQgetvalue(result, i, 2));
	}

	PQclear(result);

	fgets(read_buffer, sizeof(read_buffer) - 1, stdin);
	return strtoul(read_buffer, NULL, 10);
}

int mode_deposit(PGconn* db, int argc, char** argv){
	static const char* QUERY_DEPOSIT = "SELECT garfield.snack_account_deposit($1, $2, $3);";
	static const char* QUERY_WITHDRAW = "SELECT garfield.snack_account_withdraw($1, $2, $3);";
	const char* act_query = NULL;

	double amount = 0.0;
	int transfer_register = -1, uid;
	size_t i;
	char str_uid[20], str_amount[20], str_register[20]; 

	for(i = 1; i <argc ; i++){
		if(argv[i][0] == '-'){
			switch(argv[i][1]){
				case 'r':
					transfer_register = strtol(argv[++i], NULL, 0);
					break;
				default:
					printf("Unknown mode argument \"-%c\"\n", argv[i][1]);
					return -1;
			}
		}
		else{
			amount = strtod(argv[i], NULL);
		}
	}

	if(transfer_register < 0){
		//select register
		transfer_register = selectCashRegister(db);
	}

	if(transfer_register < 0){
		printf("Invalid register selected\n");
		return -1;
	}

	uid = queryUserID(db, PQuser(db));

	snprintf(str_uid, sizeof(str_uid) - 1, "%d", uid);
	snprintf(str_amount, sizeof(str_amount) - 1, "%.2f", amount);
	snprintf(str_register, sizeof(str_register) - 1, "%d", transfer_register);

	printf("Performing %s on register %s for user %s with %s\n", argv[0], str_register, str_uid, str_amount);

	const char* params[3] = {str_register, str_uid, str_amount};
	if(!strcmp(argv[0], "withdraw")){
		act_query = QUERY_WITHDRAW;
	}
	else if(!strcmp(argv[0], "deposit")){
		act_query = QUERY_DEPOSIT;
	}

	if(!act_query){
		printf("Invalid mode selected\n");
		return -1;
	}

	PGresult* result = PQexecParams(db, act_query, 3, NULL, params, NULL, NULL, 0);

	if(!result){
		printf("Failed to build query\n");
		return -1;
	}

	if(PQresultStatus(result) != PGRES_TUPLES_OK){
		printf("Failed to perform account update\n");
		PQclear(result);
		return -1;
	}

	PQclear(result);
	return 0;
}
