#ifndef CLIENT_H
#define CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

// Declare the function that is implemented in client.c
int connect_socket(int port_n, const char* servip, const char* name_);

#ifdef __cplusplus
}
#endif

#endif // CLIENT_H