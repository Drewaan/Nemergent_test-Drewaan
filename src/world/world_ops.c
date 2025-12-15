#include "../../include/entropy.h"

void	world_finish_buckets(world_t *w)
{
	bucket_compact(&w -> positives);
	bucket_compact(&w -> negatives);
}

void	world_print_and_cleanup(world_t *w)
{
	bucket_destroy(&w -> positives);
	bucket_destroy(&w -> negatives);
}
