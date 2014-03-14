#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>

#include <pthread.h>

typedef struct {
	int heartbeat;
	int peer;
	int client;
} ports;

extern ports port;
extern int connected;

// heartbeat
extern void	(*func_heartbeat)(void *nothing);	// pthreads



void		error_invocation	(int argc, char** argv);
void        redraw              ();
void        control             ();
