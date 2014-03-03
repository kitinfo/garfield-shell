int parse_arguments(int argc, char** argv, CONFIG_PARAMS* cfg){
	int i;

	for(i=0;i<argc;i++){
		if(argv[i][0]=='-'){
			switch(argv[i][1]){
				case 'f':
					if(argc>i+1){
						cfg->config_file=argv[i+1];
						i++;
					}
					break;
				case 'h':
					return 0;
				case 'v':
					cfg->verbosity=1;
					break;
			}
		}
	}

	return 0;
}
