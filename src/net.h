#ifdef __cplusplus
extern "C" {
#endif

#include <arpa/inet.h>
#include <sys/socket.h>

#ifndef H_NET
#define H_NET

typedef struct {
  void *next;                // Pointer to the next in the list
  struct sockaddr_in *addr;  // The address of the node
  long long seen;            // Last message received timestamp
  long long ping;            // Last ping transmission timestamp
  unsigned short ping_state; // State to be received in pong
  unsigned short rtt;        // Round-trip-time (set on pong rx)
} net_node;

#endif // H_NET

#ifdef __cplusplus
} // extern "C"
#endif
