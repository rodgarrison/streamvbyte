#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "streamvbyte.h"

char verbose=0;

int main() {
  const int sz = streamvbyte_max_compressedbytes(1);
  for (uint32_t i = 0; i < 0x1FFFFFFF; i++) {
    uint32_t datain = i;
    uint64_t dataout = 0;
    uint64_t lastout = 0;
	  size_t compsize = streamvbyte_encode(&datain, 1, (uint8_t*)&dataout);
    if (i>0) {
      if (dataout<=lastout) {
        printf("order problem at index %u: dataout %llx lastout %llx\n", i, dataout, lastout);
      }
    }
    lastout = dataout;
    if (verbose) {
      printf("encoded value %u in %lu bytes\n", i, compsize);
    }
	  size_t compsize2 = streamvbyte_decode((uint8_t*)&dataout, &datain, 1);
    if (compsize2!=compsize || datain!=i) {
      printf("decode error value %u compsize %lu compsize2 %lu actual: %u expected: %u\n",
        i, compsize, compsize2, datain, i);
    }
  }

  return 0;
}
