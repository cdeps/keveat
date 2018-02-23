#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CDEPS_KEVEAT_H_
#define _CDEPS_KEVEAT_H_

#include <stdint.h>

typedef struct {
  uint64_t size;
} keveat_stat;

typedef struct {
  void *udata;                                  //                                 // Personal data passed to the functions
  void (*read)(uint64_t,uint64_t,void*,void*);  // position, length, buffer, udata // Read a bunch of bytes from whatever the adapter handles
  void (*write)(uint64_t,uint64_t,void*,void*); // position, length, buffer, udata // Write a bunch of bytes to whatever the adapter handles
  void (*truncate)(uint64_t,void*);             // length, udata                   // Change the size of whatever the adapter handles
  keveat_stat (*stat)(void*);                   // udata                           // Report info about whatever the adapter handles
} keveat_adapter;

typedef struct {
  keveat_adapter *adapter; // How to perform IO
  uint32_t recsize;        // What size are the records
  uint64_t cpos;           // The current position of the order &  garbage collector
} keveat_ctx;

#endif // _CDEPS_KEVEAT_H_

#ifdef __cplusplus
} // extern "C"
#endif
