#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CDEPS_KEVEAT_H_
#define _CDEPS_KEVEAT_H_

#include <stdint.h>

typedef struct {
  void *udata;                                  //                                 // Personal data passed to the functions
  void (*read)(uint64_t,uint64_t,void*,void*);  // position, length, buffer, udata // Read a bunch of bytes from whatever the adapter handles
  void (*write)(uint64_t,uint64_t,void*,void*); // position, length, buffer, udata // Write a bunch of bytes to whatever the adapter handles
//  void (*remove)(uint64_t,uint64_t,void*);      // position, length, udata         // Remove a bunch of bytes from whatever the adapter handles (delete, not clear)
} keveat_adapter;

typedef struct {
  keveat_adapter *adapter; // How to perform IO
  uint32_t bufsize;        // What size is our buffer
  uint32_t recsize;        // What size are the records
} keveat_ctx;

#endif // _CDEPS_KEVEAT_H_

#ifdef __cplusplus
} // extern "C"
#endif
