#include "generator.h"

// ----------------------------------------------------------- //
static void work_once(void *addr)
{
	char *buffer = addr;
	for(int b = 0; b < BUFFER_SIZE; ++b){
		const char byte = buffer[b];
		int offset = (b + byte) % BUFFER_SIZE;
		buffer[b] ^= buffer[offset];
	}
}

// ----------------------------------------------------------- //
static void *work(void *addr)
{
	for(;;)
		work_once(addr);
	return NULL;
}

// ----------------------------------------------------------- //
int rcr_init(rcr *gen, size_t num_workers)
{
	// Setup worker threads. Fuck error handling.
	pthread_mutex_init(&gen->mutex, NULL);
	gen->threads = calloc(num_workers, sizeof(pthread_t));
	gen->num_threads = num_workers;
	for(int i = 0; i < num_workers; ++i)
		pthread_create(gen->threads + i, NULL, work, gen->buffer);

	// Randomize initial bytes.
	srand(time(0));
	for(int i = 0; i < BUFFER_SIZE; ++i)
		gen->buffer[i] = (char) rand();
	return 0;
}

// ----------------------------------------------------------- //
void rcr_kill(rcr *gen)
{
	for(int i = 0; i < gen->num_threads; ++i)
		pthread_cancel(gen->threads[i]);
	free(gen->threads);
	gen->num_threads = 0;
}

// ----------------------------------------------------------- //
static char rcr_current_byte(rcr *gen)
{
	char byte = gen->buffer[0];
	for(int i = 1; i < BUFFER_SIZE; ++i)
		byte ^= gen->buffer[i];
	return byte;
}

// ----------------------------------------------------------- //
char rcr_generate_byte(rcr *gen)
{
	pthread_mutex_lock(&gen->mutex);
	char byte;
	do {
		byte = rcr_current_byte(gen);
	} while(byte == gen->prev);
	gen->prev = byte;
	pthread_mutex_unlock(&gen->mutex);
	return byte;
}

// ----------------------------------------------------------- //
char *rcr_generate_bytes(rcr *gen, size_t n)
{
	char *ret = malloc(n);
	for(int i = 0; i < n; ++i)
		ret[i] = rcr_generate_byte(gen);
	return ret;
}

// ----------------------------------------------------------- //
void rcr_output_byte(rcr *gen)
{
	char byte = rcr_generate_byte(gen);
	printf("%c", byte);
}

// ----------------------------------------------------------- //
void rcr_output_byte_formatted(rcr *gen)
{
	char byte = rcr_generate_byte(gen);
	printf("%d\n", (unsigned char) byte);
}

// ----------------------------------------------------------- //
static void rcr_output_segment(rcr *gen)
{
	char bytes[SEGMENT_SIZE];
	for(int i = 0; i < SEGMENT_SIZE; ++i)
		bytes[i] = rcr_generate_byte(gen);
	printf("%.*s", SEGMENT_SIZE, bytes);
}

// ----------------------------------------------------------- //
void rcr_output_forever(rcr *gen)
{
	for(;;)
		rcr_output_segment(gen);
}

// ----------------------------------------------------------- //
void rcr_output_forever_formatted(rcr *gen)
{
	for(;;)
		rcr_output_byte_formatted(gen);
}
