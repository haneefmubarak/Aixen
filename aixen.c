#include "aixen.h"

ports port;
int master = 1;

int main (int argc, char **argv) {
	// a.out [master/slave-] [heartbeat port] [peer port] [client port] {upstream URL}
	if ((argc != 5) && (argc !=6)) {
		error_invocation (argc, argv);
		return -1;
	}

	if (!strcmp(argv[1], "slave-"))
		master = 0;

	port.heartbeat	= atoi(argv[2]);
	port.peer	= atoi(argv[3]);
	port.client	= atoi(argv[4]);

	char *upstream = NULL;
	if (argc == 6)
		upstream = strdup(argv[5]);


	pthread_t thread_heartbeat;
	assert (!pthread_create (		// pthreads returns zero on success
			&thread_heartbeat,	// thread struct pointer
			NULL,			// thread attr
			func_heartbeat,		// function
			NULL			// data pointer
			));

  redraw();

	return 0;
}

void error_invocation (int argc, char **argv) {
	fprintf (stderr,
		"Invocation requires five or six arguments:\n"
		"%s "
		"[master/slave-] "
		"[heartbeat port] "
		"[peer port] "
		"[client port] "
		"{existing master/peer}"
		"\n\n"
		"Examples (localhost):\n"
		"\t"
		"First Master:\n"
		"\t\t"
		"%s master 4485 4480 4490\n"
		"\t"
		"Additional Master:\n"
		"\t\t"
		"%s master 4465 4460 4470 localhost:4480\n"
		"\t"
		"Slave:\n"
		"\t\t"
		"%s slave- 8085 8080 8090 localhost:4490\n",
		argv[0], argv[0], argv[0], argv[0]
		);

	return;
}
