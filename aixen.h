#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>

#include <pthread.h>

struct aixen_ports {
	int master;
	int client;
};

struct aixen_status {
	int main;
	int peer;
};

struct aixen_configuration {
	struct aixen_ports	port;
	struct aixen_status	status;
	int			master;
	int			connected;
	char* upstream;
};

extern	struct aixen_configuration		config;

// control panel
void		redraw			(void);
void		draw			(void);
void		control			(void);
int		doCommand		(char* comm);
void		writeline		(char* line);	// Use this to log messages to CPL


int		error_invocation	(int argc, char** argv);
