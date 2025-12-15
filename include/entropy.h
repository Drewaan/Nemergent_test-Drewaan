#ifndef ENTROPY_H
#define ENTROPY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>

#define _GNU_SOURCE
#define START_CAP 8
#define CLR_END  "\033[0m"
#define CLR_RED  "\033[31m"
#define CLR_GREEN "\033[32m"

typedef struct s_bucket
{
	int *values;
	int capacity;
	int length;
	pthread_mutex_t mtx;
}	bucket_t;

typedef struct s_world
{
	int nthreads;
	int per_thread;
	bucket_t positives;
	bucket_t negatives;
}	world_t;

//BUCKET_INIT =========================

int		bucket_init(bucket_t *b);

//BUCKET_OPS =========================

void	bucket_push(bucket_t *b, int val);

//BUCKET_UTILS =========================

void	bucket_destroy(bucket_t *b);
void	bucket_compact(bucket_t *b);
int	 	cmp_int_asc(const void *a, const void *b);
void	world_sort_buckets(world_t *w);

//RESULTS_DISPLAY =========================

void world_show_results(const world_t *w);

//RANDOM_GEN =========================

int	generate_full_int(unsigned int *seedp);

//THREAD_WORKER =========================

void	world_launch(world_t *w);

//WORLD_INIT =========================

int world_init(world_t *w, int nthreads, int per_thread);

//WORLD_OPS =========================

void	world_finish_buckets(world_t *w);
void	world_print_and_cleanup(world_t *w);


#endif