#include "aixen.h"

struct aixen_configuration config;

int main (int argc, char **argv) {
	// a.out [master/slave-] {upstream URL}
	if ((argc != 2) && (argc != 3)) {
		return error_invocation (argc, argv);
	}

	config.connected = 0;

	if (!strcmp (argv[1], "master"))
		config.master = 1;
	else if (!strcmp (argv[1], "slave-"))
		config.master = 0;
	else
		return error_invocation (argc, argv);


	if (argc == 3)
		config.upstream = strdup (argv[5]);
	else
		config.upstream = NULL;


	if (config.master)
		control();


	return 0;
}

int error_invocation (int argc, char **argv) {
	fprintf (stderr,
		"Invocation requires five or six arguments:\n"
		"%s "
		"[master/slave-] "
		"{existing master}"
		"\n\n"
		"Examples (localhost):\n"
		"\t"
		"First Master:\n"
		"\t\t"
		"%s master\n"
		"\n\t"
		"Slave:\n"
		"\t\t"
		"%s slave- localhost:4490\n",
		argv[0], argv[0], argv[0]
		);


	// and thus close the program
	return -1;
}
