#ifndef ENTROPY_H
#define ENTROPY_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#define START_CAP 8
#define CLR_END  "\033[0m"
#define CLR_RED  "\033[31m"
#define CLR_GREEN "\033[32m"

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

//BUCKET_INIT =========================
int		bucket_init(bucket_t *b);

//BUCKET_OPS =========================
void	bucket_push(bucket_t *b, int val);



#endif