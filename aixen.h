#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>

#include <pthread.h>

typedef struct {
	int heartbeat;
	int peer;
	int client;
	int master;
	int connected;
	int heartbeatStatus;
	int mainStatus;
	int peerStatus;
	char* upstream;
} config;

extern config cfg;

// heartbeat
extern void	(*func_heartbeat)(void *nothing);	// pthreads

// control panel
void		redraw		    	();
void		control			    ();
void		doCommand (char* comm);


int		error_invocation	(int argc, char** argv);
