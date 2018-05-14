#ifdef __cplusplus
extern "C" {
#endif

#ifndef ___KEVEAT_H_
#define ___KEVEAT_H_

#include <stdio.h>

typedef struct {
  int fd;
} keveat_ctx;

/**
 * Open a file descriptor as a keveat collection
 *
 * While this creates a new context, it DOES NOT verify if the given file
 * descriptor contains a valid collection.
 *
 * @param {int} fd       File descriptor to operate on
 *
 * @return {keveat_ctx}  The context to pass to later calls
 */
keveat_ctx * keveat_open( int fd );


#endif // ___KEVEAT_H_

#ifdef __cplusplus
} // extern "C"
#endif
