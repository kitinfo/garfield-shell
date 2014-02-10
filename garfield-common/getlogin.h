#ifdef _WIN32
	#include <windows.h>
	#include <errno.h>
	int _getlogin_r(char *buf, size_t size){
		DWORD sz=(size>0x7fff)?0x7fff:size;
		if(!GetUserName(buf, &sz)){
			if(GetLastError()==ERROR_INSUFFICIENT_BUFFER)
				return ERANGE;
			else
				return ENOENT;
		}
		return 0;
	}
	#define getlogin_r _getlogin_r
#endif