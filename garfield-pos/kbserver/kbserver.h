#define VERSION "0.1 hackedy hack"

#define MAX_CFGLINE_LENGTH 1024
#define LISTEN_QUEUE_LENGTH 30

typedef struct _MAPPING {
	uint16_t scancode;
	char* map_target;
	struct _MAPPING* next;
} MAPPING;

typedef struct /*_CFG_PARAMS*/ {
	int verbosity;		//verbosity level
	char* config_file;	//cfg file, allocated by system
	MAPPING* mapping_head;
	char* input_device;	//input device, allocated by cfgparse
	char* bind_host;	//bindhost, allocated by cfgparse
	uint16_t port;		//local port
	bool send_raw;		//send raw scancodes
	bool exclusive_access;	//request exclusive access
} CONFIG_PARAMS;
