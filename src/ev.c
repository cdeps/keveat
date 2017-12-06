#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>

#include "ev.h"

EventListener *listenerList = 0;

/* Register a new listener
 *
 * Adds a new handler to the list of handlers for events for the given event name.
 *
 * @param {string}                       name   The name of the event to register to
 * @param {function(string,mixed,mixed)} func   The handler function for the event
 * @param {mixed}                        udata  Static data to pass the handler
 *
 * @return {EventListener}
 */
EventListener * ev_on( char *name, void (*func)(char*,void*,void*), void *udata ) {
  EventListener *listener = malloc( sizeof(EventListener) );
  listener->next  = listenerList;
  listener->name  = name;
  listener->func  = func;
  listener->udata = udata;
  listenerList = listener;
  return listener;
}

/* Unregister a listener
 *
 * @param {EventListener} listener  The listener to remove from the list
 */
void ev_off( EventListener *listener ) {
  EventListener *previous = listenerList;
  // Listener at the beginning of the linked list
  if(listener==listenerList) {
    listenerList = listener->next;
    free(listener);
    return;
  }
  // Listener somewhere else in the linked list
  while( previous->next != listener ) {
    previous = previous->next;
  }
  previous->next = listener->next;
  free(listener);
  return;
}

/* Run all handlers for this event name
 *
 * @param {string} name  The name of the event to trigger
 * @param {mixed}  data  Data to pass to the handler
 */
void ev_trigger( char *name, void *data ) {
  EventListener *listener = listenerList;
  while(listener) {
    if(strcmp(name,listener->name)==0) {
      listener->func(name,data,listener->udata);
    }
    listener=listener->next;
  }
}


#ifdef __cplusplus
} // extern "C"
#endif
