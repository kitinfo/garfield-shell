INPUT_TOKEN tok_read(char* input){
	if(isdigit(input[0])){
		return TOKEN_NUMERAL;
	}

	if(!strncmp(input, "PAY\r\n", 5)){
		return TOKEN_PAY;
	}

	if(!strncmp(input, "PLU\r\n", 5)){
		return TOKEN_PLU;
	}

	if(!strncmp(input, "STORNO\r\n", 8)){
		return TOKEN_STORNO;
	}

	if(!strncmp(input, "CANCEL\r\n", 8)){
		return TOKEN_CANCEL;
	}

	if(!strncmp(input, "ENTER\r\n", 7)){
		return TOKEN_ENTER;
	}

	if(!strncmp(input, "BACKSPACE", 9)){
		return TOKEN_BACKSPACE;
	}

	//TODO check for incomplete matches

	return TOKEN_INVALID;
}

int tok_length(INPUT_TOKEN token){
	switch(token){
		case TOKEN_PAY:
			return 3+2;
		case TOKEN_PLU:
			return 3+2;
		case TOKEN_STORNO:
			return 6+2;
		case TOKEN_CANCEL:
			return 6+2;
		case TOKEN_ENTER:
			return 5+2;
		case TOKEN_BACKSPACE:
			return 9;
		case TOKEN_NUMERAL:
			return 1;
		case TOKEN_INCOMPLETE:
			return 0;
		default:
			return 1;
	}
}

const char* tok_dbg_string(INPUT_TOKEN t){
	switch(t){
		case TOKEN_INCOMPLETE:
			return "TOKEN_INCOMPLETE";
		case TOKEN_INVALID:
			return "TOKEN_INVALID";
		case TOKEN_PAY:
			return "TOKEN_PAY";
		case TOKEN_PLU:
			return "TOKEN_PLU";
		case TOKEN_STORNO:
			return "TOKEN_STORNO";
		case TOKEN_CANCEL:
			return "TOKEN_CANCEL";
		case TOKEN_ENTER:
			return "TOKEN_ENTER";
		case TOKEN_BACKSPACE:
			return "TOKEN_BACKSPACE";
		case TOKEN_NUMERAL:
			return "TOKEN_NUMERAL";
	}
	return "UNKNOWN";
}
