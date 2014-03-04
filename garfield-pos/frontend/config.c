bool conn_init(CONNECTION* in, CONNECTION_TYPE type){
	in->host=NULL;
	in->port=0;
	in->type=type;
	in->fd=-1;
	return true;
}


