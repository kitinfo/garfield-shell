#define VERSION "0.1 hackedy hack"

#define MAX_CFGLINE_LENGTH 1024

typedef struct /*_CFG_PARAMS*/ {
	int verbosity;		//verbosity level
	char* config_file;	//cfg file, allocated by system
	char* input_device;	//input device, allocated by cfgparse
	char* bind_host;	//bindhost, allocated by cfgparse
	int port;		//local port
	bool send_raw;		//send raw scancodes
	bool exclusive_access;	//request exclusive access
} CONFIG_PARAMS;
