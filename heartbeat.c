#include "aixen.h"

static void *heartbeat (void *nothing);

void *(*func_heartbeat)(void *nothing) = &heartbeat;

static void *heartbeat (void *nothing) {
	// fill this in later
	return NULL;
}
