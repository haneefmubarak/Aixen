#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>

typedef struct {
	int heartbeat;
	int peer;
	int client;
} ports;

extern ports port;



void		error_invocation	(int argc, char** argv);

// heartbeat
void		(*heartbeat)		(void *nothing);	// pthreads
