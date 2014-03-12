#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <malloc.h>
#include <inttypes.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <unistd.h>

#include "kbserver.h"

#include "mapping.c"
#include "config.c"
#include "cfgparse.c"
#include "argparse.c"
#include "evfd.c"
#include "sighandle.c"
#include "sockfd.c"

int usage(char* fn){
	printf("garfield-pos kbserver utility\n\n");	
	printf("Exposes evdev input via TCP in a configurable fashion\n");	
	printf("Usage:\n");
	printf("\t%s -f <config file>\n", fn);
	return -1;
}

volatile bool shutdown_server=false;

int main(int argc, char** argv){
	CONFIG_PARAMS cfg;
	int i;
	int error=0;
	int ev_fd=-1;
	int listen_fd=-1;
	int maxfd;
	int bytes;
	int client_fds[LISTEN_QUEUE_LENGTH];
	char read_buffer[128];
	struct timeval tv;
	fd_set readfds;
	struct input_event ev_data;

	memset(&cfg, 0, sizeof(CONFIG_PARAMS));
	memset(client_fds, -1, sizeof(client_fds));

	error=parse_arguments(argc-1, argv+1, &cfg);

	if(error!=0){
		fprintf(stderr, "Failed to parse commandline arguments\n");
		usage(argv[0]);
		exit(error);
	}

	if(!cfg.config_file){
		fprintf(stderr, "No config file supplied, aborting\n");
		exit(usage(argv[0]));
	}

	if(cfg.verbosity>2){
		fprintf(stderr, "Using config file %s\n", cfg.config_file);
	}

	error=parse_config(cfg.config_file, &cfg);
	if(error!=0){
		fprintf(stderr, "Failed to parse config file, aborting\n");
		exit(error);
	}

	printf("kbserver v%s starting\n",VERSION);
	
	if(!cfg_sanity_check(&cfg)){
		fprintf(stderr, "Config failed the sanity check, aborting\n");
		cfg_free(&cfg);
		return -1;
	}

	//set up signal handlers
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, sig_interrupt);

	//open event descriptor
	ev_fd=evin_open(&cfg);
	if(ev_fd<0){
		cfg_free(&cfg);
		return -1;
	}

	//open listening socket
	listen_fd=sock_open(&cfg);
	if(listen_fd<0){
		evin_close(ev_fd);
		cfg_free(&cfg);
		return -1;
	}

	//main loop
	while(!shutdown_server){
		maxfd=(ev_fd>listen_fd)?ev_fd:listen_fd;

		//prepare timeouts & fd sets
		tv.tv_sec=2;
		tv.tv_usec=0;

		FD_ZERO(&readfds);
		FD_SET(ev_fd, &readfds);
		FD_SET(listen_fd, &readfds);
		for(i=0;i<LISTEN_QUEUE_LENGTH;i++){
			if(client_fds[i]>0){
				if(client_fds[i]>maxfd){
					maxfd=client_fds[i];
				}
				FD_SET(client_fds[i], &readfds);
			}
		}

		//call select
		error=select(maxfd+1, &readfds, NULL, NULL, &tv);
		if(error<0){
			perror("select");
			break;
		}

		if(FD_ISSET(ev_fd, &readfds)){
			//read event
			bytes=read(ev_fd, &ev_data, sizeof(ev_data));
			if(bytes<=0){
				perror("evfd read");
				break;
			}

			//handle event data
			if(ev_data.type==EV_KEY){
				if(ev_data.value==0){
					//key press
					char* map_target=map_get(&cfg, ev_data.code);
					if(cfg.verbosity>3){
						fprintf(stderr, "Read scancode %d, mapped to \"%s\"\n", ev_data.code, (map_target)?map_target:"NULL");
					}
					if(map_target||cfg.send_raw){
						//send data
						for(i=0;i<LISTEN_QUEUE_LENGTH;i++){
							if(client_fds[i]>0){
								if(map_target){
									bytes=send(client_fds[i], map_target, strlen(map_target), 0);
									if(bytes<strlen(map_target)&&cfg.verbosity>1){
										fprintf(stderr, "Incomplete send\n");
									}
								}
								else{
									bytes=send(client_fds[i], &(ev_data.code), sizeof(ev_data.code), 0);
								}
								if(bytes<0){
									perror("client_send");
									close(client_fds[i]);
									client_fds[i]=-1;
								}
							}
						}
					}
				}
			}
		}

		if(FD_ISSET(listen_fd, &readfds)){
			//handle new client
			if(cfg.verbosity>2){
				fprintf(stderr, "New client\n");
			}
			//find client slot
			for(i=0;i<LISTEN_QUEUE_LENGTH;i++){
				if(client_fds[i]<0){
					//accept into that
					client_fds[i]=accept(listen_fd, NULL, NULL);
					break;
				}
			}
		}

		for(i=0;i<LISTEN_QUEUE_LENGTH;i++){
			if(client_fds[i]>0&&FD_ISSET(client_fds[i],&readfds)){
				//handle & ignore client input
				bytes=recv(client_fds[i], &read_buffer, sizeof(read_buffer),0);
				if(bytes<=0){
					perror("client_read");
					close(client_fds[i]);
					client_fds[i]=-1;
				}
			}
		}
	}

	sock_close(listen_fd);
	evin_close(ev_fd);
	cfg_free(&cfg);
	printf("kbserver shut down\n");
	return 0;
}
