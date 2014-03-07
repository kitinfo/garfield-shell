INPUT_TOKEN read_token(char* input){
	int len=strlen(input);

	if(isdigit(input[0])){
		return TOKEN_NUMERAL;
	}

	if(!strncmp(input, "PAY\r\n", 5)){
		return TOKEN_PAY;
	}

	if(!strncmp(input, "PLU\r\n", 5)){
		return TOKEN_PLU;
	}

	if(!strncmp(input, "STORNO\r\n", 8)){
		return TOKEN_STORNO;
	}

	if(!strncmp(input, "CANCEL\r\n", 8)){
		return TOKEN_CANCEL;
	}

	if(!strncmp(input, "ENTER\r\n", 7)){
		return TOKEN_ENTER;
	}

	if(!strncmp(input, "BACKSPACE", 9)){
		return TOKEN_BACKSPACE;
	}

	return TOKEN_INVALID;
}

int token_length(INPUT_TOKEN token){
	switch(token){
		case TOKEN_PAY:
			return 3+2;
		case TOKEN_PLU:
			return 3+2;
		case TOKEN_STORNO:
			return 6+2;
		case TOKEN_CANCEL:
			return 6+2;
		case TOKEN_ENTER:
			return 5+2;
		case TOKEN_BACKSPACE:
			return 9;
		case TOKEN_NUMERAL:
			return 0;
		default:
			return 1;
	}
}

int garfield_pos(CONFIG* cfg){
	struct timeval tv;
	fd_set readfds;
	int fd_max, i, error, bytes, offset=0;
	char input_buffer[INPUT_BUFFER_LENGTH];

	//set up initial state
	POS={
		STATE_IDLE,
		NULL,
		0,
		0,
		false
	};

	//TODO send welcoming message

	while(!POS.shutdown){	
		tv.tv_sec=10;
		tv.tv_usec=0;

		//select over i/o descriptors
		fd_max=-1;
		FD_ZERO(&readfds);
		for(i=0;i<cfg->connection_count;i++){
			FD_SET(cfg->connections[i].fd, &readfds);
			if(cfg->connections[i].fd>fd_max){
				fd_max=cfg->connections[i].fd;
			}
		}

		error=select(fd_max+1, &readfds, NULL, NULL, &tv);
		if(error<0){
			perror("select");
			return -1;
		}

		//process input
		if(cfg->verbosity>2){
			printf("Input ready from %d descriptors\n", error);
		}

		for(i=0;i<cfg->connection_count;i++){
			if(FD_ISSET(cfg->connections[i].fd, &readfds)){
				bytes=recv(cfg->connections[i].fd, input_buffer+offset, sizeof(input_buffer)-offset, 0);
				input_buffer[offset+bytes]=0;
				if(cfg->verbosity>3){
					printf("%d bytes of data from conn %d\n", bytes, i);
				}
				
				//read tokens from input stream
				//while numeric -> increment offset (limit!)
				//if !numeric -> execute and reset
			}
		}
	}

	return 0;
}
