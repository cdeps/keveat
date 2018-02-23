#ifdef __cplusplus
extern "C" {
#endif

#ifndef _KEVEAT_EVENTS_H_
#define _KEVEAT_EVENTS_H_

#include <stdint.h>

#include "base.h"

#define EV_NAMED    1
#define EV_TIMEOUT  2
#define EV_INTERVAL 4

typedef struct {
  void *next;
  void *udata;
  char *name;
  uint8_t flags;
  int64_t interval;
  int64_t timeout;
  void (*func)(var*,void*); // event, udata
} EventListener;

EventListener * addEventListener( char *name, void (*func)(var*,void*), void *udata );
EventListener * setTimeout( uint64_t timeout, void (*func)(var*,void*), void *udata );
EventListener * setInterval( uint64_t interval, void (*func)(var*,void*), void *udata );

void removeEventListener( EventListener *listener );
void clearTimeout( EventListener *listener );
void clearInterval( EventListener *listener );

void eventTrigger( char *name, void *data );
void eventTick( uint8_t ticks );

#endif // _KEVEAT_EVENTS_H_

#ifdef __cplusplus
} // extern "C"
#endif
