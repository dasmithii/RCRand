#ifndef _RCRAND_GENERATOR_H_
#define _RCRAND_GENERATOR_H_
#define BUFFER_SIZE 50
#define SEGMENT_SIZE 100
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


typedef struct {
	pthread_mutex_t mutex;
	pthread_t *threads;
	size_t num_threads;
	char buffer[BUFFER_SIZE];
	char prev;
} rcr;

int rcr_init(rcr *gen, size_t num_workers);
void rcr_kill(rcr *gen);
char rcr_generate_byte(rcr *gen);
void rcr_output(rcr *gen);
void rcr_output_formatted(rcr *gen);
void rcr_output_forever(rcr *gen);
void rcr_output_forever_formatted(rcr *gen);

#endif