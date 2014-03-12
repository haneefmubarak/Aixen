#include "aixen.h"

int main (int argc, char **argv) {
	// a.out [master/slave-] [heartbeat port] [peer port] [client port] {upstream URL}
	if ((argc != 5) && (argc !=6)) {
		error_invocation (argc, argv);
		return -1;
	}

	int master = 1;
	if (!strcmp(argv[1], "slave-"))
		master = 0;

	int heartbeatPort = atoi(argv[2]);
	int peerPort = atoi(argv[3]);
	int clientPort = atoi(argv[4]);

	if (argc == 6)
		char *upstream = strdup(argv[5]);

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
