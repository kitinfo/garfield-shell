#include "tokenizer.c"

int garfield_pos(CONFIG* cfg){
	struct timeval tv;
	fd_set readfds;
	int fd_max, i, error, bytes, offset=0;
	char input_buffer[INPUT_BUFFER_LENGTH];

	//set up initial state
	POS.state=STATE_IDLE;
	POS.cart=NULL;
	POS.items_allocated=0;
	POS.items=0;
	POS.shutdown=false;

	//TODO send welcoming message to display
	printf(">GarfieldPOS v%s\n",VERSION);

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
				
				if(bytes<0){
					perror("read_tcp");
				}

				if(bytes==0){
					printf("Connection %d lost, reconnecting...\n", i);
					//TODO try to reconnect
				}

				//terminate
				input_buffer[offset+bytes]=0;

				if(cfg->verbosity>3){
					printf("%d bytes of data from conn %d\n", bytes, i);
				}
				
				//TODO lex, parse
			}
		}
	}

	return 0;
}
