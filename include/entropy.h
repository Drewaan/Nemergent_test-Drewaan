#ifndef ENTROPY_H
#define ENTROPY_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

typedef struct s_bucket {
	int *values;
	int capacity;
	int length;
	pthread_mutex_t mtx;
} bucket_t;

typedef struct s_world {
	int nthreads;
	int per_thread;
	bucket_t positives;
	bucket_t negatives;
} world_t;


#endif