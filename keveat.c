#ifdef __cplusplus
extern "C" {
#endif

#include <arpa/inet.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#include "keveat.h"

keveat_ctx * keveat_init( keveat_adapter *adapter ) {

  // Check the required functions exist
  if ( !adapter->read  ) return 0;
  if ( !adapter->write ) return 0;

  // Verify signature
  char *signature = malloc(7);
  adapter->read(2,7,signature,adapter->udata);
  if ( strcmp("KEVEAT",signature) ) {
    free(signature);
    return 0;
  }
  free(signature);

  // Start building the context
  keveat_ctx *ctx = calloc(1,sizeof(keveat_ctx));
  ctx->adapter = adapter;

  // Stat the adapter if possible
  if ( adapter->stat ) {
    ctx->stat = adapter->stat(adapter->udata);
  }

  // Fetch the record size in bytes
  adapter->read(9,1,&ctx->recsize,adapter->udata);
  ctx->recsize = 512 << ctx->recsize;

  // Initialize the key holder
  if ( !ctx->last_key ) ctx->last_key = calloc( 1, ctx->recsize );

  // Return what we just built
  return ctx;
}

void keveat_free( keveat_ctx *ctx ) {
  if ( !ctx ) return;
  if ( ctx->adapter->close ) ctx->adapter->close( ctx->adapter->udata );
  if ( ctx->stat ) {
    if ( ctx->stat->flags & KEVEAT_FLAG_ADAPTER_FREE ) free( ctx->adapter );
    if ( ctx->stat->flags & KEVEAT_FLAG_STAT_FREE ) free( ctx->stat );
  }
  if ( ctx->last_key ) free(ctx->last_key);
  free( ctx );
}

uint32_t keveat_read( keveat_ctx *ctx, char *key, void *buffer ) {
  
  return 0;
}

uint32_t keveat_write(  keveat_ctx *ctx, char *key, void *buffer, uint32_t length ) {
  return 0;
}

uint32_t keveat_delete( keveat_ctx *ctx, char *key ) {
  return 0;
}

#ifdef __cplusplus
} // extern "C"
#endif
