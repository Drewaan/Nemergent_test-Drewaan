#include "../../include/entropy.h"

int world_init(world_t *w, int nthreads, int per_thread)
{
	w -> nthreads = nthreads;
	w -> per_thread = per_thread;

	if (!bucket_init(&w -> positives))
		return 0;
	if (!bucket_init(&w -> negatives))
	{
		pthread_mutex_destroy(&w -> positives.mtx);
		free(w -> positives.values);
		w -> positives.values = NULL;
		return 0;
	}
	return 1;
}
