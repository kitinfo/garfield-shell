bool add_mapping(CONFIG_PARAMS* cfg, uint16_t scancode, char* output){
	if(cfg->verbosity>0){
		printf("Mapping scancode %d to \"%s\"\n", scancode, output);
	}

	//TODO
	return false;
}

bool del_mapping(CONFIG_PARAMS* cfg, uint16_t scancode){
	//TODO
	return false;
}

char* get_mapping(CONFIG_PARAMS* cfg, uint16_t scancode){
	//TODO
	return false;
}
