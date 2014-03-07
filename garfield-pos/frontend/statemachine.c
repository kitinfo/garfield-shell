TRANSITION_RESULT state_idle(INPUT_TOKEN token){
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
}

TRANSITION_RESULT state_barcode(INPUT_TOKEN token){
	TRANSITION_RESULT res={STATE_BARCODE, TOKEN_DISCARD};

	switch(token){
		case TOKEN_BACKSPACE:
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
}

TRANSITION_RESULT state_plu(INPUT_TOKEN token){
	TRANSITION_RESULT res={STATE_PLU, TOKEN_DISCARD};

	switch(token){
		case TOKEN_BACKSPACE:
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
}

TRANSITION_RESULT state_display(INPUT_TOKEN token){
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
}

TRANSITION_RESULT state_storno(INPUT_TOKEN token){
	TRANSITION_RESULT res={STATE_STORNO, TOKEN_DISCARD};

	switch(token){
		case TOKEN_NUMERAL:
			res.action=TOKEN_KEEP;
			break;
		case TOKEN_BACKSPACE:
			res.action=TOKEN_REMOVE;
			break;
		case TOKEN_ENTER:
			//TODO resolve snack, remove from cart
			//no break here
		case TOKEN_CANCEL:
			res.state=STATE_DISPLAY;
			break;
		default:
			return res;
	}
}

TRANSITION_RESULT state_pay(INPUT_TOKEN token){
	TRANSITION_RESULT res={STATE_PAY, TOKEN_DISCARD};

	switch(token){
		case TOKEN_NUMERAL:
			res.action=TOKEN_KEEP;
			break;
		case TOKEN_BACKSPACE:
			res.action=TOKEN_REMOVE;
			break;
		case TOKEN_ENTER:
			//TODO execute payment
			res.state=STATE_IDLE;
			break;
		case TOKEN_CANCEL:
			res.state=STATE_DISPLAY;
			break;
		default:
			return res;
	}
}

TRANSITION_RESULT transition(POS_STATE state, INPUT_TOKEN token){
	switch(state){
		case STATE_IDLE:
			return state_idle(token);
		case STATE_BARCODE:
			return state_barcode(token);
		case STATE_PLU:
			return state_plu(token);
		case STATE_DISPLAY:
			return state_display(token);
		case STATE_STORNO:
			return state_storno(token);
		case STATE_PAY:
			return state_pay(token);
	}
	TRANSITION_RESULT def={STATE_IDLE, TOKEN_DISCARD};
	return def;
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
