bool cfg_sanity_check(CONFIG_PARAMS* cfg){
	if(!cfg->input_device){
		fprintf(stderr, "No input device specified\n");
		return false;
	}

	if(!cfg->bind_host){
		fprintf(stderr, "No bind address specified\n");
		return false;
	}

	if(cfg->port==0){
		fprintf(stderr, "Invalid port\n");
		return false;
	}

	if(cfg->verbosity>2){
		fprintf(stderr, "Using verbosity level %d\n",cfg->verbosity);
		fprintf(stderr, "Using input device %s\n",cfg->input_device);
		fprintf(stderr, "Binding to host %s Port %d\n",cfg->bind_host, cfg->port);
		fprintf(stderr, "Fall back to sending raw scancodes: %s\n",cfg->send_raw?"true":"false");
		fprintf(stderr, "Open device in exclusive mode: %s\n",cfg->exclusive_access?"true":"false");
	}

	return true;
}

bool cfg_free(CONFIG_PARAMS* cfg){
	if(cfg->verbosity>2){
		fprintf(stderr, "Freeing allocated memory\n");
	}

	if(cfg->input_device){
		free(cfg->input_device);
	}

	if(cfg->bind_host){
		free(cfg->bind_host);
	}

	return map_free(cfg);
}

char* cfg_parse_string(char* input){
	bool istext=false;
	int pos=0;
	uint8_t conv;
	char* endptr;
	char* translation=calloc(1, strlen(input)*sizeof(char));
	
	if(!translation){
		perror("cfg_parse_string");
		return NULL;
	}

	for(;input[0]!=0;){
		if(input[0]=='\''){
			//toggle mode
			istext=!istext;
			input++;
		}
		else if(istext){
			//literal copy
			translation[pos++]=input[0];
			input++;
		}
		else{
			//skip spaces
			for(;isspace(input[0]);input++){
			}
			if(input[0]!=0&&input[0]!='\''){
				//try strtoul
				conv=(uint8_t)strtoul(input, &endptr, 0);
				if(input==endptr&&input[0]!=0){
					free(translation);
					fprintf(stderr, "Invalid numeral at %s\n",input);
					return NULL;
				}
				translation[pos++]=conv;
				input=endptr;
			}
		}
	}

	return translation;
}
