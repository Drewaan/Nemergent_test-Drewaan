#include "../../include/entropy.h"

static void	*thread_main(void *arg)
{
	world_t			*w = (world_t *)arg;
	unsigned int	seed;
	int				generated = 0;
	int				per = w -> per_thread;

	seed = (unsigned int)time(NULL) ^ (unsigned int)(uintptr_t)pthread_self();
	while (generated < per)
	{
		int	val = generate_full_int(&seed);
		if (val < 0)
			bucket_push(&w -> negatives, val);
		else
			bucket_push(&w -> positives, val);
		generated++;
	}
	return NULL;
}

void	world_launch(world_t *w)
{
	pthread_t	*pool = NULL;
	int			created = 0;
	int			i = 0;

	pool = malloc(sizeof(pthread_t) * (size_t)w -> nthreads);
	if (pool == NULL)
	{
		fprintf(stderr, CLR_RED "Error: malloc pool\n" CLR_END);
		world_print_and_cleanup(w);
		exit(1);
	}
	while (i < w -> nthreads)
	{
		if (pthread_create(&pool[i], NULL, thread_main, (void *)w) != 0)
		{
			int	j = 0;
			while (j < created)
			{
				pthread_join(pool[j], NULL);
				j++;
			}
			free(pool);
			fprintf(stderr, CLR_RED "Error: pthread_create\n" CLR_END);
            world_print_and_cleanup(w);
            exit(1);
		}
		created++;
		i++;
	}
	i = 0;
	while (i < created)
	{
		pthread_join(pool[i], NULL);
		i++;
	}
	free(pool);
	world_finish_buckets(w);
	world_sort_buckets(w);
}
