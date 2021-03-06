This project provides a command-line interface to 'Garfield',
the Point-of-Sales system used at the FSMI at the University
of Karlsruhe, as well as supplementary tools related to it.

The main components are:
	- shell (garfield-shell)
		A wrapper providing a persistent interaction
		framework with the Garfield tools

	- garfield-snack
		This module interfaces the snack subsystem,
		providing functionality for finding and buying 
		snacks

	- garfield-user
		Interfaces the user subsystem, such as snack
		account balances and user management

Most modules can be built on Linux based systems as well as on
windows (using the corresponding make target).

Prerequisites (Linux)
	- libpq-dev
	- make
	- A C compiler (tcc works fine) 

Prerequisites (Windows)
	- libpq headers, definitions and shared libraries
		Can be acquired from the PostgreSQL git and/or
		the pgAdmin application (libintl.dll and libpq.dll)
	- OpenSSL shared libraries (ssleay32.dll)
	- advapi32 and ws2_32 headers and definitions
		Should probably have come shipped with your compiler,
		but can alternatively be taken from MinGW or generated
	- make (Not a hard requirement, it shouldn't be too hard to build
		the modules by hand)

Compile the project by executing 'make' (or 'make windows', respectively).
This will use whatever 'cc' expands to on your system to compile the modules,
which might lead to problems on windows, so either edit the makefiles
or make sure you have some executable (eg, Batch file) named 'cc' in your path
that resolves to whatever compiler you want to use (again, tcc works fine here).

Linux users may also wish to execute 'make install' in order to have easier access
to the garfield-shell and garfield-snack commands.

Additionally, this repo contains
	- bash-completion
		Completion scripts for shell environments

	- garfield-api
		A PHP/PDO API with a simple AJAX frontend implementation.
	
Build/setup/usage information for these subprojects is probably located
in the respective folders.

The garfield-shell project is released as free-to-use and free-to-modify
software under the respective licenses found in the individual folders.

The authors greatly appreciate bug/issue reports, feature requests and 
general feedback. They also happily accept snack donations ;)

mpease, cbdev | #kitinfo | 2013+
