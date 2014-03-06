void cfg_init(CONFIG* cfg){
	memset(cfg, 0, sizeof(CONFIG));
	//memset(&(cfg->db), 0, sizeof(DATABASE));
}

void cfg_conn_init(CONNECTION* conn){
	conn->host=NULL;
	conn->port=0;
	conn->type=CONN_INPUT;
	conn->fd=-1;
}

void cfg_parse_hostspec(CONNECTION* conn, char* spec){
	int i;

	//get host part length
	for(i=0;!isspace(spec[i]);i++){
	}

	conn->host=calloc(sizeof(char), i+1);
	strncpy(conn->host, spec, i);

	conn->port=strtoul(spec+i, NULL, 10);
}

void cfg_free(CONFIG* cfg){
	int i;
	if(cfg->connections){
		for(i=0;i<cfg->connection_count;i++){
			free(cfg->connections[i].host);
		}
		free(cfg->connections);
	}

	if(cfg->db.server){
		free(cfg->db.server);
	}

	if(cfg->db.user){
		free(cfg->db.user);
	}

	if(cfg->db.pass){
		free(cfg->db.pass);
	}

	if(cfg->db.db_name){
		free(cfg->db.db_name);
	}
}

bool cfg_read(CONFIG* cfg, char* file){
	int i;
	char line_buffer[MAX_CFGLINE_LENGTH+1];
	char* line_head;
	char* argument;
	FILE* handle=fopen(file, "r");

	if(!handle){
		perror("cfg_read");
		return false;
	}

	while(fgets(line_buffer, MAX_CFGLINE_LENGTH, handle)!=NULL){
	//handle single config line
		//strip trailing newline
		for(i=strlen(line_buffer)-1;i>0&&isspace(line_buffer[i]);i--){
			line_buffer[i]=0;
		}

		//skip leading spaces
		for(line_head=line_buffer;isspace(line_head[0]);line_head++){
		}

		//skip comments & blank lines
		if(line_head[0]==0||line_head[0]=='#'){
			continue;
		}

		//find argument offset
		for(argument=line_head;!isspace(argument[0])&&argument[0]!=0;argument++){
		}
		for(;isspace(argument[0]);argument++){
		}

		//fail if no argument supplied
		if(argument[0]==0){
			printf("No argument for option %s\n",line_head);
			fclose(handle);
			return false;
		}

		//read option
		if(!strncmp(line_head, "input", 5)||!strncmp(line_head, "output", 6)){
			//input/output stanza
			CONNECTION conn;
			cfg_conn_init(&conn);

			switch(line_head[0]){
				case 'i':
					conn.type=CONN_INPUT;
					break;
				case 'o':
					conn.type=CONN_OUTPUT;
					break;
			}

			//hand to hostparse
			cfg_parse_hostspec(&conn, argument);

			//realloc connections
			cfg->connection_count++;
			cfg->connections=realloc(cfg->connections, cfg->connection_count*sizeof(CONNECTION));
			if(!cfg->connections){
				printf("Failed to allocate memory for connection data\n");
				//TODO exit fail
			}
			
			cfg->connections[cfg->connection_count-1]=conn;
		}
		else if(!strncmp(line_head, "db_server", 9)){
			if(cfg->db.server){
				printf("Multiple db_server directives, ignoring\n");
				continue;
			}
			//db_server stanza
			CONNECTION db;
			cfg_conn_init(&db);

			//hostparse
			cfg_parse_hostspec(&db, argument);

			//stuff into db config
			cfg->db.server=db.host;
			cfg->db.port=db.port;
		}
		else if(!strncmp(line_head, "db_user", 7)){
			//db_user stanza
			if(cfg->db.user){
				printf("Multiple db_user directives, ignoring\n");
				continue;
			}
			cfg->db.user=calloc(sizeof(char), strlen(argument)+1);
			strncpy(cfg->db.user, argument, strlen(argument));
		}
		else if(!strncmp(line_head, "db_name", 7)){
			//db_name stanza
			if(cfg->db.db_name){
				printf("Multiple db_name directives, ignoring\n");
				continue;
			}
			cfg->db.db_name=calloc(sizeof(char), strlen(argument)+1);
			strncpy(cfg->db.db_name, argument, strlen(argument));
		}
		else if(!strncmp(line_head, "db_persist", 10)){
			//db_persist stanza
			if(!strncmp(argument, "true", 4)){
				cfg->db.persist_connection=true;
			}
		}
		else if(!strncmp(line_head, "use_pgpass", 10)){
			//use_pgpass stanza
			if(!strncmp(argument, "true", 4)){
				cfg->db.use_pgpass=true;
			}
		}
		else{
			printf("Unrecognized config line %s\n", line_head);
			fclose(handle);
			return false;
		}
	}

	if(errno!=0){
		perror("cfg_read");
		fclose(handle);
		return false;
	}

	fclose(handle);
	return true;
}

bool cfg_sane(CONFIG* cfg){
	int i;

	if(!cfg->connections||cfg->connection_count<1){
		printf("No input/output connections specified\n");
		return false;
	}

	for(i=0;i<cfg->connection_count;i++){
		if(!cfg->connections[i].host||strlen(cfg->connections[i].host)<1){
			printf("Connection %d has invalid server\n", i);
			return false;
		}

		if(cfg->connections[i].port==0){
			printf("Connection %d has no port\n", i);
			return false;
		}
	}

	if(!cfg->db.server||strlen(cfg->db.server)<1){
		printf("No database server specified\n");
		return false;
	}

	if(cfg->db.port==0){
		printf("Invalid database port\n");
		return false;
	}

	if(!cfg->db.user||strlen(cfg->db.user)<1){
		printf("No database user specified\n");
		return false;
	}

	if(!cfg->db.use_pgpass&&(!cfg->db.pass||strlen(cfg->db.pass)<1)){
		printf("No database password specified\n");
		return false;
	}

	if(!cfg->db.db_name||strlen(cfg->db.db_name)<1){
		printf("No database name specified\n");
		return false;
	}

	if(cfg->verbosity>1){
		printf("Config summary:\n");
		printf("Configuration file: %s\n", cfg->cfg_file);
		printf("Verbosity level %d\n", cfg->verbosity);
		printf("Connection count %d\n", cfg->connection_count);
		for(i=0;i<cfg->connection_count;i++){
			printf("Connection %d directionality: %s\n", i, (cfg->connections[i].type==CONN_INPUT)?"input":"output");
			printf("Connection %d host: %s Port %d\n", i, cfg->connections[i].host, cfg->connections[i].port);
		}
		printf("Database server: %s Port %d\n", cfg->db.server, cfg->db.port);
		printf("Database name: %s\n", cfg->db.db_name);
		printf("Database user name: %s\n", cfg->db.user);
		printf("Connections are %spersistent\n", (cfg->db.persist_connection)?"":"non-");
		printf("Using pgpass: %s\n", (cfg->db.use_pgpass)?"yes":"no");
	}

	return true;
}

