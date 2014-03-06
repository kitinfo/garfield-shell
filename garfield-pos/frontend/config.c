void cfg_init(CONFIG* cfg){
	memset(cfg, 0, sizeof(CONFIG));
	//memset(&(cfg->db), 0, sizeof(DATABASE));
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
	//TODO
}

bool cfg_sane(CONFIG* cfg){
	//TODO
}

