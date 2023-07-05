#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <cstddef>
#include <vector>

#include "../include/tcpserver_unix.hpp"

TCPServer::TCPServer(int port) : portno(port){
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  
  int reuse = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

  if (sockfd < 0) {
    error("ERROR opening socket");
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    error("ERROR on binding");
  }
  std::cout << "server running on port " + std::to_string(portno) << std::endl; 
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

receive_struct_t TCPServer::receive(int socket, int timeout_val, size_t read_size, size_t read_size_max) {
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
    receiveStruct.buffer = buffer;
    return receiveStruct;
  }
  
  int n;
  int bytes_read = 0;
  while (1) {
    n = read(socket, (*buffer).data() + (*buffer).size() - read_size, read_size);
    //bytes_read += n;
    
    
    if (n > 0) {
      bytes_read += n;
    }
    
    if (n < 0) {
      error("ERROR reading from socket");
    }
    if (static_cast<size_t>(n) < read_size) {
      break;
    }

    (*buffer).resize(static_cast<size_t>(n) + read_size);
    
    if (bytes_read >= KB*read_size_max) {
      std::cout << "READ MAX\n";
      break;
    }    

  }
  //size_t bytes_read = (*buffer).size();
  receiveStruct.buffer = buffer;
  receiveStruct.bytes_read = static_cast<size_t>(bytes_read);
  return receiveStruct;

    
}


void TCPServer::send(char* buffer, size_t size, int socket) {

   
  int n = write(socket, buffer, size);

  if (n < 0) { //need to change 
    error("ERROR writing to socket");
  }

}

void TCPServer::send_str(const std::string& msg, int socket) {
  int n = write(socket, msg.c_str(), msg.length());

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


