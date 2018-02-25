#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CDEPS_KEVEAT_H_
#define _CDEPS_KEVEAT_H_

#include <stdint.h>

#define KEVEAT_FLAG_STAT_FREE    1
#define KEVEAT_FLAG_ADAPTER_FREE 2

typedef struct {
  uint64_t size;
  uint64_t flags;
} keveat_stat;

typedef struct {
  void *udata;                                      //                                 // Personal data passed to the functions
  uint64_t (*read)(uint64_t,uint64_t,void*,void*);  // position, length, buffer, udata // Read a bunch of bytes from whatever the adapter handles
  uint64_t (*write)(uint64_t,uint64_t,void*,void*); // position, length, buffer, udata // Write a bunch of bytes to whatever the adapter handles
  void (*truncate)(uint64_t,void*);                 // length, udata                   // Change the size of whatever the adapter handles
  keveat_stat *(*stat)(void*);                      // udata                           // Report info about whatever the adapter handles
  void (*close)(void*);                             // udata                           // DO whatever needs to be done to finishd
} keveat_adapter;

typedef struct {
  keveat_adapter *adapter; // How to perform IO
  keveat_stat *stat;
  uint32_t recsize;        // What size are the records
  uint64_t cpos;           // The current position of the order &  garbage collector
  uint64_t last_post;      // The most recent position read
  char *last_key;          // The key of the most recent read
} keveat_ctx;

keveat_ctx * keveat_init( keveat_adapter *adapter );
void keveat_free( keveat_ctx *ctx );
uint32_t keveat_read(   keveat_ctx *ctx, char *key, void *buffer );
uint32_t keveat_write(  keveat_ctx *ctx, char *key, void *buffer );
uint32_t keveat_delete( keveat_ctx *ctx, char *key );

#endif // _CDEPS_KEVEAT_H_

#ifdef __cplusplus
} // extern "C"
#endif
