#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "event.h"

// #define EV_NAMED    1
// #define EV_TIMEOUT  2
// #define EV_INTERVAL 4

// typedef struct {
//   void *next;
//   void *udata;
//   char *name;
//   uint8_t flags;
//   int64_t interval;
//   int64_t timeout;
//   void (*func)(var*,void*); // event, udata
// } EventListener;

EventListener *listenerList = 0;

EventListener * addEventListener( char *name, void (*func)(var*,void*), void *udata ) {
  EventListener *listener = malloc(sizeof(EventListener));
  listener->next  = listenerList;
  listener->udata = udata;
  listener->name  = name;
  listener->flags = EV_NAMED;
  listener->func  = func;
  listenerList = listener;
  return listener;
}

EventListener * setTimeout( uint64_t timeout, void (*func)(var*,void*), void *udata ) {
  EventListener *listener = malloc(sizeof(EventListener));
  listener->next    = listenerList;
  listener->udata   = udata;
  listener->flags   = EV_TIMEOUT;
  listener->timeout = timeout;
  listener->func    = func;
  listenerList = listener;
  return listener;
}

EventListener * setInterval( uint64_t interval, void (*func)(var*,void*), void *udata ) {
  EventListener *listener = malloc(sizeof(EventListener));
  listener->next     = listenerList;
  listener->udata    = udata;
  listener->flags    = EV_INTERVAL;
  listener->interval = interval;
  listener->timeout  = interval;
  listener->func     = func;
  listenerList = listener;
  return listener;
}

void removeEventListener( EventListener *listener ) {

}

void clearTimeout( EventListener *listener ) {

}

void clearInterval( EventListener *listener ) {

}

void eventTrigger( char *name, void *data ) {

}

void eventTick( uint8_t ticks ) {

}

#ifdef __cplusplus
} // extern "C"
#endif
