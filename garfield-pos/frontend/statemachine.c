TRANSITION_RESULT state_idle(INPUT_TOKEN token){
	TRANSITION_RESULT res={STATE_IDLE, TOKEN_DISCARD};
	return res;
}

TRANSITION_RESULT state_barcode(INPUT_TOKEN token){
	TRANSITION_RESULT res={STATE_BARCODE, TOKEN_DISCARD};
	return res;
}

TRANSITION_RESULT state_plu(INPUT_TOKEN token){
	TRANSITION_RESULT res={STATE_PLU, TOKEN_DISCARD};
	return res;
}

TRANSITION_RESULT state_display(INPUT_TOKEN token){
	TRANSITION_RESULT res={STATE_DISPLAY, TOKEN_DISCARD};
	return res;
}

TRANSITION_RESULT state_storno(INPUT_TOKEN token){
	TRANSITION_RESULT res={STATE_STORNO, TOKEN_DISCARD};
	return res;
}

TRANSITION_RESULT state_pay(INPUT_TOKEN token){
	TRANSITION_RESULT res={STATE_PAY, TOKEN_DISCARD};
	return res;
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
