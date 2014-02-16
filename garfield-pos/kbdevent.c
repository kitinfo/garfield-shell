#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>

char charFromKeycode(int kc){
	switch(kc){
		case KEY_1:
			return '1';
		case KEY_2:
			return '2';
		case KEY_3:
			return '3';
		case KEY_4:
			return '4';
		case KEY_5:
			return '5';
		case KEY_6:
			return '6';
		case KEY_7:
			return '7';
		case KEY_8:
			return '8';
		case KEY_9:
			return '9';
		case KEY_0:
			return '0';
	}
	return 'x';
}

int main(int argc, char** argv){
	char* input_device=NULL;
	int fd, bytes;
	struct input_event ev;

	if(argc<2){
		printf("Insufficient arguments\n");
		exit(1);
	}
	
	input_device=argv[1];

	fd=open(input_device, O_RDONLY);

	if(fd<0){
		printf("Failed to open device\n");
		exit(1);
	}

	//get exclusive control
	bytes=ioctl(fd, EVIOCGRAB, 1);
	
	while(true){
		bytes=read(fd, &ev, sizeof(struct input_event));
		if(bytes<0){
			printf("read() error\n");
			close(fd);
			exit(1);
		}
		if(ev.type==EV_KEY){
			if(ev.value!=0){
				continue;
			}
			printf("Value %d, Code %d, Type %d - %c\n",ev.value, ev.code, ev.type, charFromKeycode(ev.code));
		}
	}

	return 0;
}
