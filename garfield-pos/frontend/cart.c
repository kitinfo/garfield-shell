int cart_index(CONFIG* cfg){

	//printf("Cart status: allocated %d, used %d\n",POS.items_allocated, POS.items);

	if(POS.items==POS.items_allocated){
		if(cfg->verbosity>2){
			printf("Reallocating cart to %d items\n", POS.items_allocated+1);
		}

		POS.cart=realloc(POS.cart, (++POS.items_allocated)*sizeof(CART_ITEM));
		if(!POS.cart){
			return -1;
		}
		else{
			POS.items++;
			return POS.items_allocated-1;
		}
	}
	POS.items++;
	return POS.items-1;
}

bool cart_store(CART_ITEM item, CONFIG* cfg){
	int index;
	if(item.id>0){
		index=cart_index(cfg);
		if(index<0){
			if(cfg->verbosity>1){
				printf("Failed to store cart item\n");
			}
			return false;
		}
		POS.cart[index]=item;

		if(cfg->verbosity>3){
			printf("Stored in cart at position %d\n", index);
		}
		return true;
	}
	return false;
}

float cart_get_total(){
	int i;
	float sum=0.f;
	for(i=0;i<POS.items;i++){
		sum+=POS.cart[i].price;
	}
	return sum;
}
