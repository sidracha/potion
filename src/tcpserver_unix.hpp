#ifndef TCPSERVER_UNIX_H_INCLUDED
#define TCPSERVER_UNIX_H_INCLUDED

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class TCPServer {
  private:
    int portno;
    int sockfd;
    int newsockfd;
    sockaddr_in serv_addr;
    sockaddr_in cli_addr;

  public:
    TCPServer(int port);
    void acceptConnection();
    std::string receive();
    void send(const std::string& message);
    void closeConnection();
  
  private:
    void error(const char *msg);
};

#endif
