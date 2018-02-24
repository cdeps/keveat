#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#include "keveat.h"

keveat_ctx * keveat_init( keveat_adapter *adapter ) {
  printf("KEVEAT INIT START\n");

  // Check the required functions exist
  if ( !adapter->read  ) return 0;
  if ( !adapter->write ) return 0;
  if ( !adapter->stat  ) return 0;

  printf("  CHECKED FUNCTIONS\n");

  // Verify signature
  char *signature = malloc(7);
  adapter->read(2,7,signature,adapter->udata);
  printf("SIG: %s\n", signature);
  if ( strcmp("KEVEAT",signature) ) {
    printf("'KEVEAT' != '%s'\n", signature);
    free(signature);
    return 0;
  }
  free(signature);

  printf("  VERIFIED SIGNATURE\n");

  // Start building the context
  keveat_ctx *ctx = calloc(1,sizeof(keveat_ctx));
  ctx->adapter = adapter;

  // Fetch the record size in bytes
  adapter->read(9,1,&ctx->recsize,adapter->udata);
  ctx->recsize = 512 << ctx->recsize;

  // Return what we just built
  return ctx;
}

#ifdef __cplusplus
} // extern "C"
#endif
