#define VERSION "0.1"
#define MAX_CFGLINE_LENGTH 1024
#define MAX_PASSWORD_LENGTH 128
#define PGRES_SSLMODE "require"
#define INPUT_BUFFER_LENGTH 128

typedef enum /*_CONNECTION_TYPE*/ {
	CONN_INPUT,
	CONN_OUTPUT
} CONNECTION_TYPE;

typedef enum /*_LOGIC_STATE*/ {
	STATE_IDLE,
	STATE_BARCODE,
	STATE_PLU,
	STATE_DISPLAY,
	STATE_STORNO,
	STATE_PAY
} POS_STATE;

typedef enum /*_INPUT_TOKEN*/ {
	TOKEN_INVALID,
	TOKEN_PAY,
	TOKEN_PLU,
	TOKEN_STORNO,
	TOKEN_CANCEL,
	TOKEN_ENTER,
	TOKEN_BACKSPACE,
	TOKEN_NUMERAL
} INPUT_TOKEN;

typedef struct /*_CART_SNACK_ITEM*/ {
	int snackid;
	double price;
} CART_ITEM;

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

struct {
	POS_STATE state;
	CART_ITEM* cart;
	int items_allocated;
	int items;
	bool shutdown;
} POS;
