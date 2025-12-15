#include "../../include/entropy.h"

void	bucket_destroy(bucket_t *b)
{
	if (b -> values)
		free(b -> values);
	b -> values = NULL;
	b -> capacity = 0;
	b -> length = 0;
	pthread_mutex_destroy(&b -> mtx);
}

void	bucket_compact(bucket_t *b)
{
	if (b -> length == 0)
	{
		free(b -> values);
		b -> values = NULL;
		b -> capacity = 0;
		return ;
	}
	int	*tmp = realloc(b -> values, sizeof(int) * b -> length);
	if (tmp == NULL)
	{
		fprintf(stderr, CLR_RED "Error: realloc en bucket_compact\n" CLR_END);
		bucket_destroy(b);
		exit(1);
	}
	b -> values = tmp;
	b -> capacity = b -> length;
}

int cmp_int_asc(const void *a, const void *b)
{
	int	ia = *(const int *)a;
	int	ib = *(const int *)b;
	if (ia < ib)
		return -1;
	if (ia > ib)
		return 1;
	return 0;
}


void world_sort_buckets(world_t *w)
{
	if (w->positives.values && w->positives.length > 0)
		qsort(w->positives.values, (size_t)w->positives.length, sizeof(int), cmp_int_asc);
	if (w->negatives.values && w->negatives.length > 0)
		qsort(w->negatives.values, (size_t)w->negatives.length, sizeof(int), cmp_int_asc);
}
