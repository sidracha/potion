#ifndef TCPSERVER_UNIX_H_INCLUDED
#define TCPSERVER_UNIX_H_INCLUDED

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct receive_struct_t {
  char * buffer;
  int bytes_read;

} receive_struct_t;

class TCPServer {
  private:
    int portno;
    int sockfd;
    int newsockfd;
    sockaddr_in serv_addr;
    sockaddr_in cli_addr;
    size_t read_size;

  public:
    TCPServer(int port, size_t read_size_p);
    int acceptConnection();
    receive_struct_t* receive(int timeout_val, int socket); //timeout val in seconds
    void send(const std::string& message, int socket);
    void closeConnection(int socket);
  
  private:
    void error(const char *msg);
};

#endif
