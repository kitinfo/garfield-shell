int mode_balance(PGconn* db, int argc, char** argv){
	static const char* QUERY_SNACK_ACCOUNT_BALANCE = "SELECT users.user_id, user_name, user_full_name, balance "
		"FROM garfield.users "
		"JOIN garfield.user_balances ON "
		"users.user_id = user_balances.user_id "
		"WHERE user_name = $1";
	char* user_name = PQuser(db);

	PGresult* result = PQexecParams(db, QUERY_SNACK_ACCOUNT_BALANCE, 1, NULL, (const char**)&user_name, NULL, NULL, 0);
	if(!result){
		printf("Failed to execute query\n");
		return -1;
	}

	if(PQresultStatus(result) != PGRES_TUPLES_OK){
		printf("Query returned failure\n");
		PQclear(result);
		return -1;
	}

	if(PQntuples(result) != 1){
		printf("Query returned invalid number of rows\n");
		PQclear(result);
		return -1;
	}

	//print balance
	printf("Snack account balance for user %s (%s) is %s\n",
			PQgetvalue(result, 0, 1),
			PQgetvalue(result, 0, 2),
			PQgetvalue(result, 0, 3));

	PQclear(result);
	return 0;
}
