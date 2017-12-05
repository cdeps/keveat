#ifdef __cplusplus
extern "C" {
#endif

#ifndef H_EV
#define H_EV

typedef struct {
  void *next;
  char *name;
  void (*func)(char*,void*,void*);
  void *udata;
} EventListener;

EventListener * ev_on( char *name, void (*func)(char*,void*,void*), void *udata );
void ev_off( EventListener *listener );
void ev_trigger( char *name, void *data );


#endif // H_EV

#ifdef __cplusplus
} // extern "C"
#endif
