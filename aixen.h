#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>

#include <pthread.h>

struct hostport {
	char *host;
	int port;
};

struct list_hostports {
	struct hostport *address;
	int count;
};

struct aixen_ipports {
	union {
		struct list_hostports db;
		struct list_hostports slave;
	} master;
	union {
		struct list_hostports master;
		struct list_hostports client;
	} slave;
};

struct aixen_status {
	int main;
	int peer;
};

struct aixen_configuration {
	struct aixen_ipports	ipport;
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
