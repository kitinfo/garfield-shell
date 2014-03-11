MAPPING* map_elem(CONFIG_PARAMS* cfg, uint16_t scancode, bool create){
	MAPPING* iter;

	if(!cfg->mapping_head||cfg->mapping_head->scancode>scancode){
		//create, set up as head
		if(!create){
			return NULL;
		}

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
			if(!create){
				return NULL;
			}

			MAPPING* new=calloc(1,sizeof(MAPPING));
			new->scancode=scancode;
			new->next=iter->next;
			iter->next=new;
			return new;
		}
		if(!iter->next){
			//insert in back
			if(!create){
				return NULL;
			}

			MAPPING* new=calloc(1,sizeof(MAPPING));
			new->scancode=scancode;
			new->next=NULL;
			iter->next=new;
			return new;
		}
	}

	fprintf(stderr, "Could not insert mapping\n");
	return NULL;
}

bool map_add(CONFIG_PARAMS* cfg, uint16_t scancode, char* output){
	if(cfg->verbosity>2){
		fprintf(stderr, "Mapping scancode %d to \"%s\"\n", scancode, output);
	}

	MAPPING* element=map_elem(cfg, scancode, true);
	if(!element){
		return false;
	}

	if(element->map_target){
		free(element->map_target);
	}

	element->map_target=output;
	return true;
}

char* map_get(CONFIG_PARAMS* cfg, uint16_t scancode){
	MAPPING* element=map_elem(cfg, scancode, false);
	return (element)?element->map_target:NULL;
}

bool map_free(CONFIG_PARAMS* cfg){
	MAPPING* current;
	MAPPING* next;
	if(cfg->mapping_head){
		current=cfg->mapping_head;
		next=current->next;
		while(current!=NULL){
			if(cfg->verbosity>2){
				fprintf(stderr, "Releasing mapping of %d to %s\n", current->scancode, current->map_target);
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
