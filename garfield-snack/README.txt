This application handles interaction with the snack subsystem of Garfield,
such as finding and buying snacks, as well as displaying some fun statistics
and information.

garfield-snack can be built on Windows (use the corresponding make target or
do it yourself) as well as Linux-based systems. The provided makefile uses 
whatever 'cc' expands to on your machine, which might lead to problems on Windows 
(Substitute whatever you use. TCC works pretty well.) In any case, you will need 
the libpq-dev package for your respective environment.