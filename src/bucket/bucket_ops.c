#include "../../include/entropy.h"

static void bucket_grow_locked(bucket_t *b)
{
	int	newcap = b -> capacity * 2;
	int	*tmp = realloc(b -> values, sizeof(int) * newcap);
	if (tmp == NULL)
	{
		fprintf(stderr, CLR_RED "Error: realloc en bucket_grow_locked\n" CLR_END);
		pthread_mutex_unlock(&b -> mtx);
		exit(1);
	}
	b -> values = tmp;
	b -> capacity = newcap;
}

void	bucket_push(bucket_t *b, int val)
{
	if (pthread_mutex_lock(&b->mtx) != 0)
	{
		fprintf(stderr, CLR_RED "Error: pthread_mutex_lock en bucket_push\n" CLR_END);
		exit(1);
	}
	if (b->length >= b->capacity)
		bucket_grow_locked(b);

	b->values[b->length] = val;
	b->length++;
	if (pthread_mutex_unlock(&b->mtx) != 0)
	{
		fprintf(stderr, CLR_RED "Error: pthread_mutex_unlock en bucket_push\n" CLR_END);
		exit(1);
	}
}
