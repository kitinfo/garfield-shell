#define VERSION "0.1"
#define MAX_CFGLINE_LENGTH 1024
#define MAX_PASSWORD_LENGTH 128

typedef enum /*_CONNECTION_TYPE*/ {
	CONN_INPUT,
	CONN_OUTPUT
} CONNECTION_TYPE;

typedef struct /*_CONNECTION_SPEC*/ {
	char* host;
	uint16_t port;
	CONNECTION_TYPE type;
	int fd;
} CONNECTION;

typedef struct /*_DB_SPEC*/ {
	char* server;
	uint16_t port;
	char* user;
	char* pass;
	char* db_name;
	bool persist_connection;
	bool use_pgpass;
	PGconn* conn;
} DATABASE;

typedef struct /*_CONFIG_PARAMS*/ {
	char* cfg_file;
	int verbosity;
	int connection_count;
	CONNECTION* connections;
	DATABASE db;
} CONFIG;
