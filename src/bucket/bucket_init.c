#include "../../include/entropy.h"

int	bucket_init(bucket_t *b)
{
	b -> values = malloc(sizeof(int) * START_CAP);
	if (b -> values == NULL)
	{
		fprintf(stderr, CLR_RED "Error: malloc bucket_init\n" CLR_END);
		return 0;
	}
	b -> capacity = START_CAP;
	b -> length = 0;
	if (pthread_mutex_init(&b -> mtx, NULL) != 0)
	{
        fprintf(stderr, CLR_RED "Error: pthread_mutex_init\n" CLR_END);
		free(b -> values);
		b -> values = NULL;
		return 0;
	}
	return 1;
}