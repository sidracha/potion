#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>

#include "tcpserver_unix.hpp"

TCPServer::TCPServer(int port) {
  portno = port;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    error("ERROR opening socket");
  }

  memset((char *) &serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    error("ERROR on binding");
  }

  listen(sockfd, 5);
}

void TCPServer::acceptConnection() {
  socklen_t clilen = sizeof(cli_addr);
  newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
  std::cout << "connected\n";
  if (newsockfd < 0) {
    error("ERROR on accept");
  }
}

std::string TCPServer::receive() {
  char buffer[256];
  memset(buffer, 0, sizeof(buffer));
  int n = read(newsockfd, buffer, 255);
  if (n < 0) {
    error("ERROR reading from socket");
  }

  return std::string(buffer);
    
}

void TCPServer::send(const std::string& message) {
  int n = write(newsockfd, message.c_str(), message.length());
  if (n < 0) {
    error("ERROR writing to socket");
  } 
}

void TCPServer::closeConnection() {
  close(newsockfd);
}


void TCPServer::error(const char *msg) {
  perror(msg);
    exit(1);
}

