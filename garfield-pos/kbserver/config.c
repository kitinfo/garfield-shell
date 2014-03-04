bool cfg_sanity_check(CONFIG_PARAMS* cfg){
	//TODO
	return false;
}

bool cfg_free(CONFIG_PARAMS* cfg){
	if(cfg->input_device){
		free(cfg->input_device);
	}

	if(cfg->bind_host){
		free(cfg->bind_host);
	}

	return true;
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
					printf("Invalid numeral at %s\n",input);
					return NULL;
				}
				translation[pos++]=conv;
				input=endptr;
			}
		}
	}

	return translation;
}
