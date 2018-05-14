#ifdef __cplusplus
extern "C" {
#endif

#include "keveat.h"

#include <stdlib.h>

keveat_ctx * keveat_open( int fd ) {
  keveat_ctx *output = calloc( 1, sizeof(keveat_ctx) );
  output->fd = fd;
  return output;
}

#ifdef __cplusplus
} // extern "C"
#endif
