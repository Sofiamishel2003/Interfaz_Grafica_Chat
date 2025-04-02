#ifndef CLIENT_H
#define CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

// Declare the function that is implemented in client.c
int connect_socket(int port_n, const char* servip, const char* name_);
void list_users(int socket_fd, uint8_t frame[1024]);
void change_status(int socket_fd, const char *username, int status);
void send_message(int socket_fd, const char *username, const char *dest, const char *message);

#ifdef __cplusplus
}
#endif

#endif // CLIENT_H