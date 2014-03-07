bool db_conn_begin(CONFIG* cfg){
	if(!cfg->db.conn){
		if(cfg->verbosity>2){
			printf("Connecting to database\n");
		}
		return pq_connect(&(cfg->db));
	}
	return cfg->db.conn!=NULL;
}

void db_conn_end(CONFIG* cfg){
	if(!cfg->db.persist_connection&&cfg->db.conn){
		if(cfg->verbosity>2){
			printf("Closing non-persistent database connection\n");
		}
		pq_close(&(cfg->db));
	}
}

CART_ITEM db_query_item(CONFIG* cfg, char* barcode){
	static const char* QUERY_SNACK="SELECT \
		snacks.snack_id, snack_name, snack_price \
		FROM garfield.snacks JOIN garfield.snacks_available \
		ON snacks_available.snack_id = snacks.snack_id \
		WHERE snack_available AND location_id=1 AND snack_barcode = $1";

	//FIXME FSI hardcoded. ugly
	int i;
	CART_ITEM rv={0, 0.0};

	char* barcode_buffer=NULL;
	
	if(!db_conn_begin(cfg)){
		if(cfg->verbosity>1){
			printf("Failed to begin database communication\n");
		}
		return rv;
	}

	barcode_buffer=malloc(INPUT_BUFFER_LENGTH);
	if(!barcode_buffer){
		//FIXME error message
		return rv;
	}

	for(i=0;isdigit(barcode[i]);i++){
		barcode_buffer[i]=barcode[i];
	}
	barcode_buffer[i]=0;

	if(cfg->verbosity>3){
		printf("Searching for barcode %s\n", barcode_buffer);
		//printf("QUERY: %s\n",QUERY_SNACK);
	}

	//query item
	PGresult* result=PQexecParams(cfg->db.conn, QUERY_SNACK, 1, NULL, (const char**)&barcode_buffer, NULL, NULL, 0);

	if(result){
		if(PQresultStatus(result)==PGRES_TUPLES_OK){
			if(PQntuples(result)==1){
				rv.id=strtoul(PQgetvalue(result, 0, 0), NULL, 10);
				rv.price=strtof(PQgetvalue(result, 0, 2), NULL);	
				if(cfg->verbosity>2){
					printf("Queried snack: %s\n", PQgetvalue(result, 0, 1));
				}
			}
			else if(cfg->verbosity>2){
				printf("Query returned %d matches\n", PQntuples(result));
			}
		}
		PQclear(result);
	}

	free(barcode_buffer);
	db_conn_end(cfg);
	return rv;
}