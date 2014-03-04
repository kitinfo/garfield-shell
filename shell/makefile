.PHONY: all debug windows

all:
	$(CC) -o garfield-shell -Wall sources/*.c

debug:
	$(CC) -o garfield-shell -Wall -g sources/*.c

windows:
	cd sources && tcc -o garfield-shell.exe -Wall \
		shell_buy.c shell_exec.c shell_io.c shell_parse.c \
		shell_strings.c shell_cmd.c shell_find.c shell_list.c \
		shell_sec.c shell_user.c shell_debug.c shell_help.c \
		shell_main.c shell_shell.c
