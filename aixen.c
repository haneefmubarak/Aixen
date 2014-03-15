#include "aixen.h"

config cfg;

int main (int argc, char **argv) {
	// a.out [master/slave-] [heartbeat port] [peer port] [client port] {upstream URL}
	if ((argc != 5) && (argc !=6)) {
		return error_invocation (argc, argv);
	}

    cfg.connected = 0;

	if (!strcmp (argv[1], "master"))
		cfg.master = 1;
	else if (!strcmp (argv[1], "slave-"))
		cfg.master = 0;
	else
		return error_invocation (argc, argv);

	cfg.heartbeat	= atoi (argv[2]);
	cfg.peer	= atoi (argv[3]);
	cfg.client	= atoi (argv[4]);

	if (argc == 6)
		cfg.upstream = strdup (argv[5]);
    else
        cfg.upstream = NULL;


	pthread_t thread_heartbeat;
	assert (!pthread_create (		// pthreads returns zero on success
			&thread_heartbeat,	// thread struct pointer
			NULL,			// thread attr
			func_heartbeat,		// function
			NULL			// data pointer
			));
    cfg.heartbeatStatus = 1;
    cfg.mainStatus = 1;
    cfg.peerStatus = 1;

	if (cfg.master) {
		control();
	}

	return 0;
}

int error_invocation (int argc, char **argv) {
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


	// and thus close the program
	return -1;
}
