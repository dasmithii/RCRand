#include "generator.h"

int main(int argc, char *argv[]){
	rcr gen;
	rcr_init(&gen, 5);
	rcr_output_forever_formatted(&gen);
}