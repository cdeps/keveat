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
  void *udata;                                   //                                 // Personal data passed to the functions
  int64_t (*read)(int64_t,int64_t,void*,void*);  // position, length, buffer, udata // Read a bunch of bytes from whatever the adapter handles
  int64_t (*write)(int64_t,int64_t,void*,void*); // position, length, buffer, udata // Write a bunch of bytes to whatever the adapter handles
  void (*truncate)(int64_t,void*);               // length, udata                   // Change the size of whatever the adapter handles
  keveat_stat *(*stat)(void*);                   // udata                           // Report info about whatever the adapter handles
  void (*close)(void*);                          // udata                           // DO whatever needs to be done to finishd
} keveat_adapter;

typedef struct {
  keveat_adapter *adapter; // How to perform IO
  keveat_stat *stat;
  uint32_t recsize;        // What size are the records
  int64_t last_pos;        // The most recent position read
  char *last_key;          // The key of the most recent read
  int64_t end_pos;
  int64_t gc_left;         // GC left index
  int64_t gc_right;        // GC right index
} keveat_ctx;

keveat_ctx * keveat_init( keveat_adapter *adapter );
void keveat_free( keveat_ctx *ctx );
uint32_t keveat_read(   keveat_ctx *ctx, char *key, void *buffer );
uint32_t keveat_write(  keveat_ctx *ctx, char *key, void *buffer, uint32_t length );
uint32_t keveat_delete( keveat_ctx *ctx, char *key );

#endif // _CDEPS_KEVEAT_H_

#ifdef __cplusplus
} // extern "C"
#endif
