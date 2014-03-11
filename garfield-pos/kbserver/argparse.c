int parse_arguments(int argc, char** argv, CONFIG_PARAMS* cfg){
	int i, c;

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
					for(c=1;argv[i][c]=='v';c++){
					}
					cfg->verbosity=c-1;
					break;
				default:
					fprintf(stderr, "Unknown flag %s\n", argv[i]);
					return -1;
			}
		}
		else{
			fprintf(stderr, "Unknown argument %s\n", argv[i]);
		}
	}

	return 0;
}
