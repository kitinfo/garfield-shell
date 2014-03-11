int evin_open(CONFIG_PARAMS* cfg){
	int status;
	int fd=open(cfg->input_device, O_RDONLY);

	if(fd<0){
		perror("evin_open");
		return fd;
	}

	if(cfg->exclusive_access){
		if(cfg->verbosity>2){
			fprintf(stderr, "Requesting exclusive access\n");
		}

		status=ioctl(fd, EVIOCGRAB, 1);
		if(status<0){
			perror("evin_open/exclusive");
			close(fd);
			return status;
		}
	}

	return fd;
}

int evin_close(int fd){
	return close(fd);
}
