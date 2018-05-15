#ifdef __cplusplus
extern "C" {
#endif

#ifndef ___KEVEAT_H_
#define ___KEVEAT_H_

#include <stdio.h>

#define ___KEVEAT_FLAG_READ     1
#define ___KEVEAT_FLAG_WRITE    2
#define ___KEVEAT_FLAG_DELETE   3
#define ___KEVEAT_FLAG_COMPACT  4
#define ___KEVEAT_FLAG_SHUTDOWN 5

struct {
  char *name;   // Name of the event
  void *udata;  // User data
} keveat_event;

struct {
  void          *next;                     // Pointer to the next listener
  unsigned char flags;                     // Internal flags (read,write,delete,compact,shutdown)
  char          *name;                     // Name or key do update
  void          *data;                     // Data to write
  void          *udata;                    // Data to pass to the callback
  void (*callback)(struct keveat_event *); // Callback to run once the action/event happened
} keveat_listener;

struct {
  int fd;                             // The file descriptor this collection acts on
  unsigned long long     start;       // Offset to location where the actual data starts a.k.a.
  unsigned long long     pending;     // +start = where the pending data starts (non-compacted)
  unsigned long long     cow;         // +start = where to write new pending data
  struct keveat_listener *listeners;  // Listeners for internal events
  struct keveat_listener *tasks;      // Tasks to execute
} keveat_ctx;

/**
 * Open a file descriptor as a keveat collection
 *
 * Creates a new context & verifies the given file descriptor contains valid
 * collection data.
 *
 * @param {int}                       fd        File descriptor to operate on
 * @param {function(keveat_event*)*}  callback  The function that will be called once this collection has started.
 * @param {*}                         udata     Data to pass to the callback
 *
 * @return {keveat_ctx*}             The context to pass to later calls
 */
struct keveat_ctx * keveat_open( int fd, void (*callback)(struct keveat_event *), void *udata );

/**
 * Gracefully shutdown the collection after finishing all requests
 *
 * Enqueues a shutdown to execute & prevents new tasks to be given
 *
 * @param {keveat_ctx*}               ctx       The collection context to work upon
 * @param {function(keveat_event*)*}  callback  The function that will be called once this has completed
 * @param {*}                         udata     Data to pass to the callback
 */
void keveat_shutdown( keveat_ctx *ctx, void (*callback)(struct keveat_event *), void *udata );

/**
 * Shutdown the collection NOW
 *
 * Instantly stops the collection without running any tasks. You will lose all
 * data that is in the queue and has not been written yet.
 *
 * @param {keveat_ctx*}  ctx  The collection to shut down
 */
void keveat_destroy( keveat_ctx *ctx );

#endif // ___KEVEAT_H_

#ifdef __cplusplus
} // extern "C"
#endif
