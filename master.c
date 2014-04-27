#include "aixen.h"
#include "master.h"

static void *pt_spawn_master (void *retval) {
	int *ret = retval;

	*ret = master ();

	return retval;
}

static inline int master (void) {
	int x;

	// db initialization
	struct lcb_create_st db_options = { 0 };

	for (x = 0; x < config.ipport.master.db.count; x++) {
		// preserve the last iteration
		assert ((char *last = strdup (db_options.v.v0.host)));
		// iterate and build the db host string
		asprintf ((char **) &(db_options.v.v0.host), "%s%s:%i;", last,
				config.ipport.master.db.address[x].host,
				config.ipport.master.db.address[x].port);
		assert (db_options.v.v0.host);
		free (last);
	}

	lcb_t db_instance;
	lcb_error_t err = lcb_create (&db_instance, &options);
	assert (err == LCB_SUCCESS);

// fill in later

	// cleanup
	lcb_destroy (instance);
	free (db_options.v.v0.host);

	return 0;
}
