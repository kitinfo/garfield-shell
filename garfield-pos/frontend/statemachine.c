TRANSITION_RESULT state_idle(INPUT_TOKEN token, CONFIG* cfg){
	TRANSITION_RESULT res={STATE_IDLE, TOKEN_DISCARD};

	switch(token){
		case TOKEN_PLU:
			res.state=STATE_PLU;
			break;
		case TOKEN_NUMERAL:
			res.state=STATE_BARCODE;
			res.action=TOKEN_KEEP;
			break;
		default:
			return res;
	}
	return res;
}

TRANSITION_RESULT state_barcode(INPUT_TOKEN token, CONFIG* cfg){
	TRANSITION_RESULT res={STATE_BARCODE, TOKEN_DISCARD};

	switch(token){
		case TOKEN_BACKSPACE:
			printf("\b");
			res.action=TOKEN_REMOVE;
			break;
		case TOKEN_NUMERAL:
			res.action=TOKEN_KEEP;
			break;
		case TOKEN_ENTER:
			//TODO resolve snack, add to cart
			///no break here
		case TOKEN_CANCEL:
			res.state=STATE_DISPLAY;
			break;
		default:
			return res;
	}
	return res;
}

TRANSITION_RESULT state_plu(INPUT_TOKEN token, CONFIG* cfg){
	TRANSITION_RESULT res={STATE_PLU, TOKEN_DISCARD};
	int last_numeric;

	switch(token){
		case TOKEN_BACKSPACE:
			printf("\b");
			res.action=TOKEN_REMOVE;
			break;
		case TOKEN_NUMERAL:
			last_numeric=tok_lasttype_offset(TOKEN_NUMERAL);
			printf("%c",INPUT.parse_head[last_numeric]);
			res.action=TOKEN_KEEP;
			break;
		case TOKEN_ENTER:
			printf("\n");
			//TODO resolve snack, add to cart
			///no break here
		case TOKEN_CANCEL:
			res.state=STATE_DISPLAY;
			break;
		default:
			return res;
	}
	return res;
}

TRANSITION_RESULT state_display(INPUT_TOKEN token, CONFIG* cfg){
	TRANSITION_RESULT res={STATE_DISPLAY, TOKEN_DISCARD};

	switch(token){
		case TOKEN_NUMERAL:
			res.state=STATE_BARCODE;
			res.action=TOKEN_KEEP;
			break;
		case TOKEN_PLU:
			res.state=STATE_PLU;
			break;
		case TOKEN_CANCEL:
			res.state=STATE_IDLE;
			break;
		case TOKEN_STORNO:
			res.state=STATE_STORNO;
			break;
		case TOKEN_PAY:
			res.state=STATE_PAY;
			break;
		default:
			return res;
	}
	return res;
}

TRANSITION_RESULT state_storno(INPUT_TOKEN token, CONFIG* cfg){
	TRANSITION_RESULT res={STATE_STORNO, TOKEN_DISCARD};
	int last_numeral;

	switch(token){
		case TOKEN_NUMERAL:
			last_numeral=tok_lasttype_offset(TOKEN_NUMERAL);
			printf("%c",INPUT.parse_head[last_numeral]);
			res.action=TOKEN_KEEP;
			break;
		case TOKEN_BACKSPACE:
			printf("\b");
			res.action=TOKEN_REMOVE;
			break;
		case TOKEN_STORNO:
			//TODO remove last item from cart
			res.state=STATE_DISPLAY;
			break;
		case TOKEN_ENTER:
			printf("\n");
			//TODO resolve snack, remove from cart
			//no break here
		case TOKEN_CANCEL:
			res.state=STATE_DISPLAY;
			break;
		default:
			return res;
	}
	return res;
}

TRANSITION_RESULT state_pay(INPUT_TOKEN token, CONFIG* cfg){
	TRANSITION_RESULT res={STATE_PAY, TOKEN_DISCARD};
	int last_numeral;

	switch(token){
		case TOKEN_NUMERAL:
			last_numeral=tok_lasttype_offset(TOKEN_NUMERAL);
			printf("%c",INPUT.parse_head[last_numeral]);
			res.action=TOKEN_KEEP;
			break;
		case TOKEN_BACKSPACE:
			printf("\b");
			res.action=TOKEN_REMOVE;
			break;
		case TOKEN_ENTER:
			printf("\n");
			//TODO execute payment
			res.state=STATE_IDLE;
			break;
		case TOKEN_CANCEL:
			res.state=STATE_DISPLAY;
			break;
		default:
			return res;
	}
	return res;
}

TRANSITION_RESULT transition(POS_STATE state, INPUT_TOKEN token, CONFIG* cfg){
	switch(state){
		case STATE_IDLE:
			return state_idle(token, cfg);
		case STATE_BARCODE:
			return state_barcode(token, cfg);
		case STATE_PLU:
			return state_plu(token, cfg);
		case STATE_DISPLAY:
			return state_display(token, cfg);
		case STATE_STORNO:
			return state_storno(token, cfg);
		case STATE_PAY:
			return state_pay(token, cfg);
	}
	TRANSITION_RESULT def={STATE_IDLE, TOKEN_DISCARD};
	return def;
}

void state_enter(POS_STATE s){
	switch(s){
		case STATE_IDLE:
			printf("\f> ** GarfieldPOS ** \n");
			break;
		case STATE_BARCODE:
			printf("\f>Scanning...\n");
			break;
		case STATE_PLU:
			printf("\f>PLU: ");
			break;
		case STATE_DISPLAY:
			printf("\f>Last item x.xx\r\n>Total:     x.xx \n");
			break;
		case STATE_STORNO:
			printf("\f>Storno: ");
			break;
		case STATE_PAY:
			printf("\f>Fachschafter: ");
			break;
	}
	fflush(stdout);
}

const char* state_dbg_string(POS_STATE s){
	switch(s){
		case STATE_IDLE:
			return "STATE_IDLE";
		case STATE_BARCODE:
			return "STATE_BARCODE";
		case STATE_PLU:
			return "STATE_PLU";
		case STATE_DISPLAY:
			return "STATE_DISPLAY";
		case STATE_STORNO:
			return "STATE_STORNO";
		case STATE_PAY:
			return "STATE_PAY";
	}
	return "UNKNOWN";
}

const char* action_dbg_string(TOKEN_ACTION a){
	switch(a){
		case TOKEN_KEEP:
			return "TOKEN_KEEP";
		case TOKEN_DISCARD:
			return "TOKEN_DISCARD";
		case TOKEN_REMOVE:
			return "TOKEN_REMOVE";
	}
	return "UNKNOWN";
}
