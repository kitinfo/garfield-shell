void line_strip_trail(char* line){
	int i=strlen(line)-1;
	for(;i>=0;i--){
		if(isspace(line[i])){
			line[i]=0;
		}
		else{
			return;
		}
	}
}

int parse_config(char* input_file, CONFIG_PARAMS* cfg){
	int offset, param;	
	char line_buffer[MAX_CFGLINE_LENGTH+1];
	FILE* handle=fopen(input_file, "r");

	if(!handle){
		perror("parse_config");
		return -1;
	}

	while(fgets(line_buffer, MAX_CFGLINE_LENGTH, handle)!=NULL){
	//handle config line
		//skip leading whitespace characters
		offset=0;
		for(;isspace(line_buffer[offset]);offset++){
		}

		//skip comments and blank lines
		if(line_buffer[offset]=='#'||line_buffer[offset]=='\n'||line_buffer[offset]==0){
			continue;
		}

		//remove trailing space characters
		line_strip_trail(line_buffer);

		//skip past argument name
		param=offset;
		for(;!isspace(line_buffer[param]);param++){
		}
		//skip to argument
		for(;isspace(line_buffer[param])&&line_buffer[param]!='\n';param++){
		}
		
		if(cfg->verbosity>3){
			fprintf(stderr, "Line: %s\n",line_buffer);
		}

		if(!strncmp(line_buffer+offset, "device", 6)){
			//handle device line
			cfg->input_device=calloc(1, (strlen(line_buffer+param)+1)*sizeof(char));
			strncpy(cfg->input_device, line_buffer+param, strlen(line_buffer+param));
		}
		else if(!strncmp(line_buffer+offset, "bind", 4)){
			//handle bind line
			cfg->bind_host=calloc(1, (strlen(line_buffer+param)+1)*sizeof(char));
			strncpy(cfg->bind_host, line_buffer+param, strlen(line_buffer+param));
		}
		else if(!strncmp(line_buffer+offset, "port", 4)){
			//handle port line
			cfg->port=strtoul(line_buffer+param, NULL, 10);
		}
		else if(!strncmp(line_buffer+offset, "send_raw", 8)){
			//handle send_raw line
			if(!strncmp(line_buffer+param, "true", 4)){
				cfg->send_raw=true;
			}
		}
		else if(!strncmp(line_buffer+offset, "exclusive", 9)){
			//handle exclusive line
			if(!strncmp(line_buffer+param, "true", 4)){
				cfg->exclusive_access=true;
			}
		}
		else if(!strncmp(line_buffer+offset,"map",3)){
			//handle map line
			char* endptr;
			char* map_target;

			uint16_t scancode=strtoul(line_buffer+param, &endptr, 10);
			
			for(;isspace(endptr[0]);endptr++){
			}

			map_target=cfg_parse_string(endptr);
			if(!map_target){
				fprintf(stderr, "Failed to translate string: %s (Scancode %d)\n", endptr, scancode);
				continue;
			}

			if(!map_add(cfg, scancode, map_target)){
				fprintf(stderr, "Failed to add mapping for scancode %d\n", scancode);
				free(map_target);
				continue;
			}
		}
		else{
			fprintf(stderr, "Unrecognized config line: %s\n",line_buffer+offset);
		}
	}

	if(errno!=0){
		perror("parse_config");
		fclose(handle);
		return -1;
	}

	fclose(handle);
	
	return 0;
}
