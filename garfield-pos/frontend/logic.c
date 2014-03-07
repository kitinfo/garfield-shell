#include "tokenizer.c"
#include "statemachine.c"

int garfield_pos(CONFIG* cfg){
	struct timeval tv;
	fd_set readfds;
	int fd_max, i, c, error, bytes, offset=0, active_token=0, head_offset;
	INPUT_TOKEN token;
	TRANSITION_RESULT trans;

	//set up initial state
	POS.state=STATE_IDLE;
	POS.cart=NULL;
	POS.items_allocated=0;
	POS.items=0;
	POS.shutdown=false;

	memset(INPUT.data, 0, sizeof(INPUT.data));
	INPUT.parse_head=INPUT.data;

	//TODO send welcoming message to display
	printf("\f");
	printf(">GarfieldPOS v%s\n",VERSION);
	state_enter(POS.state);

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
				bytes=recv(cfg->connections[i].fd, INPUT.data+offset, sizeof(INPUT.data)-offset, 0);
				
				if(bytes<0){
					perror("read_tcp");
				}

				if(bytes==0){
					printf("Connection %d lost, reconnecting...\n", i);
					//TODO reconnect
					continue;
				}

				//terminate
				INPUT.data[offset+bytes]=0;

				if(cfg->verbosity>2){
					printf("%d bytes of data from conn %d\n", bytes, i);
				}

				if(cfg->verbosity>3){
					printf("Current buffer: \"%s\"\n", INPUT.data);
				}
				
				INPUT.parse_head=INPUT.data;
				token=TOKEN_INVALID;
				c=active_token;

				while(INPUT.data[c]!=0){
					//recognize token
					token=tok_read(INPUT.data+c);

					if(token==TOKEN_INCOMPLETE){
						break;
					}

					//do transition
					trans=transition(POS.state, token);
					c+=tok_length(token);

					if(cfg->verbosity>3){
						printf("(%s | %s) => %s %s\n", state_dbg_string(POS.state), tok_dbg_string(token), state_dbg_string(trans.state), action_dbg_string(trans.action));	

					}
					fflush(stdout); //FIXME this is stupid

					//TODO add token_head variable to minimize parsing overhead
				
					//display output	
					if(POS.state!=trans.state){ //FIXME this might need to be called every transition
						state_enter(trans.state);
					}

					//apply results
					POS.state=trans.state;
					switch(trans.action){
						case TOKEN_KEEP:
							//do not move parse_head
							break;
						case TOKEN_DISCARD:
							INPUT.parse_head=INPUT.data+c;
							break;
						case TOKEN_REMOVE:
							//TODO remove this and the last token
							break;
					}
				}

				//

				//shift parse_head to 0
				if(INPUT.parse_head!=INPUT.data){
					head_offset=INPUT.parse_head-INPUT.data;
					active_token=c-head_offset;
					for(c=0;INPUT.parse_head[c]!=0;c++){
						INPUT.data[c]=INPUT.parse_head[c];
					}
					INPUT.data[c]=0;
					offset=c;
				}
				else{
					head_offset=0;
					offset=strlen(INPUT.data);
					active_token=c;
				}
				
				if(cfg->verbosity>3){
					printf("parse_head offset is %d, active token is %d\n",head_offset, active_token);
					printf("Buffer after processing: \"%s\"\n", INPUT.data);
					printf("Current input offset is %d\n", offset);
				}
			}
		}
	}

	return 0;
}
