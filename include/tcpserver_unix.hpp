#ifndef TCPSERVER_UNIX_H_INCLUDED
#define TCPSERVER_UNIX_H_INCLUDED

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <cstddef>

#define KB 1024

typedef struct receive_struct_t {
  std::vector<std::byte>* buffer;
  size_t bytes_read;

} receive_struct_t;


class TCPServer {
  private:
    int portno;
    int sockfd;
    sockaddr_in serv_addr;
    sockaddr_in cli_addr;

  public:
    TCPServer(int port);
    int accept_connection();
    receive_struct_t receive(int socket, int timeout_val, size_t read_size, size_t read_size_max); //timeout val in seconds
    void close_connection(int socket);
    void send(char* buffer, size_t size, int socket);
    void send_str(const std::string& str, int socket); 

  private:
    void error(const char *msg);
};

#endif
