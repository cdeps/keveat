#ifdef __cplusplus
extern "C" {
#endif

#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "base.h"
#include "ev.h"
#include "net.h"

struct sockaddr_in addr_int; // For nodes
struct sockaddr_in addr_ext; // For clients
int sock_int;
int sock_ext;

net_client *client_list = 0;
net_node   *node_list   = 0;

// Gracefully shutdown all connections
void net_shutdown( char *evname, void *evdata, void *udata ) {

}

void net_tick( char *evname, void *evdata, void *udata ) {

  // Check if a new client has connected
  net_client *client = calloc(1,sizeof(net_client));
  socklen_t addr_size = sizeof(struct sockaddr_in);
  int fd = accept( sock_ext, (struct sockaddr *)&client->addr, &addr_size);

  // Check if we need to register or free
  if ( fd >= 0 ) {
    printf("CLIENT!!!\n");
    client->next = client_list;
    client->fd   = fd;
    client_list  = client;
  } else {
    free(client);
  }

}

// Initialize the network
void net_start( char *evname, void *evdata, void *udata ) {

  // This will be used later
  int status = 0;

  // Listen for events we want
  ev_on( "shutdown", &net_shutdown, NULL );
  ev_on( "tick"    , &net_tick    , NULL );

  // Create a UDP socket
  if ((sock_int=socket(AF_INET,SOCK_DGRAM,0))==-1) {
    fprintf(stderr,"Could not initialize internal socket\n");
    ev_trigger("shutdown",SHUTDOWN_FAILURE);
  }

  // Create a TCP socket
  if ((sock_ext=socket(AF_INET,SOCK_STREAM,0))==-1) {
    fprintf(stderr,"Could not initialize external socket\n");
    ev_trigger("shutdown",SHUTDOWN_FAILURE);
  }

  // Allow re-use of just-killed sockets
  int optval= 1;
  status &= setsockopt( sock_int, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));
  status &= setsockopt( sock_ext, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));

  // Check if re-using was allowed
  if (status) {
    fprintf(stderr,"Could not set up address re-using\n");
    ev_trigger("shutdown",SHUTDOWN_FAILURE);
  }

  // Set both sockets to non-blocking
  fcntl( sock_int, F_SETFL, O_NONBLOCK );
  fcntl( sock_ext, F_SETFL, O_NONBLOCK );

  // Zero-out our addresses
  memset((char*)&addr_int,0,sizeof(addr_int));
  memset((char*)&addr_ext,0,sizeof(addr_ext));

  // Fetch the port to use for clients
  unsigned short  port  = 5000;
  if (getenv("PORT")) {
    port = atoi(getenv("PORT"));
  }
  printf("PORT: %d\n",port);

  // Configure the addresses
  addr_int.sin_family      = AF_INET;
  addr_int.sin_addr.s_addr = htonl(INADDR_ANY);
  addr_ext.sin_family      = AF_INET;
  addr_ext.sin_addr.s_addr = htonl(INADDR_ANY);
  addr_ext.sin_port        = htons(port);

  // Bind UDP socket
  if (bind(sock_int,(struct sockaddr *)&addr_int,sizeof(addr_int))<0) {
    fprintf(stderr,"Could not bind internal socket\n");
    ev_trigger("shutdown",SHUTDOWN_FAILURE);
  }

  // Bind TCP socket
  if (bind(sock_ext,(struct sockaddr *)&addr_ext,sizeof(addr_ext))<0) {
    fprintf(stderr,"Could not bind external socket\n");
    ev_trigger("shutdown",SHUTDOWN_FAILURE);
  }

  // TCP needs to explicitly listen
  if (listen(sock_ext,5)<0) {
    fprintf(stderr,"Could not listen on external socket\n");
    ev_trigger("shutdown",SHUTDOWN_FAILURE);
  }
}

// Register our startup function
INIT net_init() {
  ev_on( "start", &net_start, NULL );
}

#ifdef __cplusplus
} // extern "C"
#endif
