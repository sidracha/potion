#include <map>
#include <iostream>

#include "../includes/tcpserver_unix.hpp"
#include "../includes/http.hpp"

void Request::parse_headers() {
  std::string request_str = ""; 
  for (size_t i = 0; i < receiveStruct.bytes_read; i++) {
    char ch = static_cast<char>((*receiveStruct.buffer)[i]);
    request_str += ch;
    if(ch == '\n') {
      std::cout << i << std::endl;
    }
  }

  std::cout << request_str << std::endl;
  

}

std::string Request::get_method () { //returns first word of request
  std::string word = "";
  std::string req_body = "";

  for (size_t i = 0; i < receiveStruct.bytes_read; i++) {
    char character = static_cast<char>((*receiveStruct.buffer)[i]);
    req_body += character;
    //std::cout << character << std::endl;
    if (i > 0) {
      
      if (static_cast<char>((*receiveStruct.buffer)[i-1]) == '\n' && character == '\n') {
        std::cout << "here\n";
      }

    }

  }
  std::cout << req_body << std::endl;
  return word;

}
