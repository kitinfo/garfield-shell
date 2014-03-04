MAPPING* map_elem(CONFIG_PARAMS* cfg, uint16_t scancode){
	MAPPING* iter;

	if(!cfg->mapping_head||cfg->mapping_head->scancode>scancode){
		//create, set up as head
		MAPPING* new=calloc(1,sizeof(MAPPING));
		new->scancode=scancode;
		new->next=cfg->mapping_head;
		cfg->mapping_head=new;
		return new;
	}
	
	for(iter=cfg->mapping_head;iter!=NULL;iter=iter->next){
		if(iter->scancode==scancode){
			//use existing element
			return iter;
		}
		if(iter->next&&iter->next->scancode>scancode){
			//insert in front
			MAPPING* new=calloc(1,sizeof(MAPPING));
			new->scancode=scancode;
			new->next=iter->next;
			iter->next=new;
			return new;
		}
		if(!iter->next){
			//insert in back
			MAPPING* new=calloc(1,sizeof(MAPPING));
			new->scancode=scancode;
			new->next=NULL;
			iter->next=new;
			return new;
		}
	}

	printf("Could not insert mapping\n");
	return NULL;
}

bool map_add(CONFIG_PARAMS* cfg, uint16_t scancode, char* output){
	if(cfg->verbosity>0){
		printf("Mapping scancode %d to \"%s\"\n", scancode, output);
	}

	MAPPING* element=map_elem(cfg, scancode);
	if(!element){
		return false;
	}

	element->map_target=output;
	return true;
}

char* map_get(CONFIG_PARAMS* cfg, uint16_t scancode){
	return map_elem(cfg, scancode)->map_target;
}

bool map_free(CONFIG_PARAMS* cfg){
	MAPPING* current;
	MAPPING* next;
	if(cfg->mapping_head){
		current=cfg->mapping_head;
		next=current->next;
		while(current!=NULL){
			if(cfg->verbosity>0){
				printf("Releasing mapping of %d to %s\n", current->scancode, current->map_target);
			}
			free(current);
			current=next;
			if(current){
				next=current->next;
			}
		}
	}
	return true;
}
