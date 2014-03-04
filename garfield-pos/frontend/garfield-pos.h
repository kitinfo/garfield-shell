#define VERSION "0.1"

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
	char* db_name;
	bool persist_connection;
	bool use_pgpass;
	PGconn* conn;
} DATABASE;

typedef struct /*_CONFIG_PARAMS*/ {
	char* cfg_file;
	DATABASE db;
	CONNECTION* connections;
	int connection_count;
} CONFIG;
