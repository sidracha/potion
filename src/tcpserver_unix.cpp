#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <cstddef>
#include <vector>

#include "../includes/tcpserver_unix.hpp"

TCPServer::TCPServer(int port) : portno(port){
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    error("ERROR opening socket");
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    error("ERROR on binding");
  }

  listen(sockfd, 5);
}

int TCPServer::accept_connection() {
  int socket;
  socklen_t clilen = sizeof(cli_addr);
  socket = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
  if (socket < 0) {
    error("ERROR on accept");
  }
  return socket;

}

receive_struct_t TCPServer::receive(int timeout_val, int socket, size_t read_size) {
  //char * buffer = new char[read_size]; 
  std::vector<std::byte> *buffer = new std::vector<std::byte>(read_size);
  struct timeval timeout;
  timeout.tv_sec = timeout_val;
  timeout.tv_usec = 0;

  fd_set readSet;
  FD_ZERO(&readSet);
  FD_SET(socket, &readSet);
  
  receive_struct_t receiveStruct;

  int activity = select(socket + 1, &readSet, nullptr, nullptr, &timeout); 
  //receive_struct_t* receiveStruct = new receive_struct_t();
  
  
  if (activity == 0) {
    receiveStruct.bytes_read = 0; //if no bytes are read within timeout, return
    return receiveStruct;
  }

  int n;
  while (1) {
    n = read(socket, (*buffer).data() + (*buffer).size() - read_size, read_size);
    if (n < 0) {
      error("ERROR reading from socket");
    }
    (*buffer).resize((*buffer).size() + n - read_size);

    if (static_cast<size_t>(n) < read_size) {
      break;
    }


  }
  size_t bytes_read = (*buffer).size();
  std::cout << bytes_read << ", " << (*buffer).size() << std::endl;
  receiveStruct.buffer = buffer;
  receiveStruct.bytes_read = bytes_read;
  return receiveStruct;

    
}

void TCPServer::send(const std::string& message, int socket) {
  int n = write(socket, message.c_str(), message.length());
  if (n < 0) {
    error("ERROR writing to socket");
  } 
}

void TCPServer::close_connection(int socket) {
  close(socket);
}


void TCPServer::error(const char *msg) {
  perror(msg);
    exit(1);
}



