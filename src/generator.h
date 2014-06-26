#ifndef _MRAND_GENERATOR_H_
#define _MRAND_GENERATOR_H_
#include <pthread.h>

typedef struct {
	pthread_mutex_t mutex;
	pthread_t *threads;
	size_t num_threads;
	char byte, prev;
} rcrg;

int rcrg_init(rcrg *gen, size_t num_workers);
void rcrg_output_byte(rcrg *gen);
void rcrg_output_bytes(rcrg *gen);
void rcrg_output_forever(rcrg *gen);

#endif