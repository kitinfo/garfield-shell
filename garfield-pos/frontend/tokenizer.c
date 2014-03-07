INPUT_TOKEN read_token(char* input){
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

	return TOKEN_INVALID;
}

int token_length(INPUT_TOKEN token){
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
			return 0;
		default:
			return 1;
	}
}