#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "streamvbyte.h"

int main() {
	int N = 64;
	uint32_t * datain = malloc(N * sizeof(uint32_t));
	uint8_t * compressedbuffer = malloc(streamvbyte_max_compressedbytes(N));
	uint32_t * recovdata = malloc(N * sizeof(uint32_t));

	for (int k = 0; k < N; ++k) {
		datain[k] = k;
  }

	size_t compsize;
	size_t compsize2;

  for (unsigned i = 0; i<1000000; i++) {
	  compsize = streamvbyte_encode(datain, N, compressedbuffer);
	  compsize2 = streamvbyte_decode(compressedbuffer, recovdata, N);
  }

  printf("%lu %lu\n", compsize, compsize2);

	return 0;
}
