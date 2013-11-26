int mode_buy(PGconn* db, int argc, char** argv){
	int i=0;
	
	//parse arguments
	//if -s -> run idsearch
	//if -u -> run userverify
	
	//fetch user id
	
	printf("Mode arguments:\n");
	for(i=0;i<argc;i++){
		printf("=>%s\n",argv[i]);
	}
	
	printf("Not yet implemented\n");
	
	return -1;
}