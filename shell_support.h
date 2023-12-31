#ifndef SHELL_SUP_H
#define SHELL_SUP_H

/* Shell Prompt */
#define PROMPT_MSG "$ " /* It should work with signal */

/* Resume from the unused attibute */
#define UNUSED __attribute__((unused))

/* buffer size for each read call in _getline */
#define BUFFER_SIZE 1024

/*--- different formatted messages for the help built-in command ---*/
#define HELP_MSG_CD "cd=\n"\
"cd:\tcd [dir]\n\n"\
"	Change the shell working directory.\n\n"\
"	If no argument is given to cd the command will be interpreted\n"\
"	as cd $HOME.\n"\
"	if the argument help is - (cd -), the command will be interpreted\n"\
"	as cd $OLDPWD.\n\n"

#define HELP_MSG_EXIT "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"	Exits the simple-shell.\n\n"\
"	Exits the shell with a status of N.  If N is omitted, the exit status\n"\
"	is that of the last command executed.\n\n"

#define HELP_MSG "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\
"	Displays information about builtin commands.\n\n"\
"	Displays brief summaries of builtin commands.  If BUILTIN_NAME is\n"\
"	specified, gives detailed help on all commands matching BUILTIN_NAME,\n"\
"	otherwise the list of help topics is printed BUILTIN_NAME list.\n"\
"	Arguments:\n\n"\
"	BUILTIN_NAME specifying a help topic.\n\n"\
"	cd\t[dir]\n"\
"	exit\t[status]\n"\
"	env\n"\
"	setenv\t[variable value]\n"\
"	unset\t[variable]\n"\
"	help\t[built_name]\n\n"

#define HELP_MSG_SETENV "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	Change or add an environment variable.\n\n"\
"	initialize a new environment variable, or modify an existing one\n"\
"	When there are not correct numbers of arguments print error message.\n\n"

#define HELP_MSG_ENV "env=\n"\
"env:\tenv \n\n"\
"	Print environment.\n\n"\
"	The env command will be print a complete list of enviroment variables.\n\n"

#define HELP_MSG_UNSETENV "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	The unsetenv function deletes one variable from the environment.\n\n"\
"	When there are not correct numbers of arguments print error message.\n\n"

#endif
