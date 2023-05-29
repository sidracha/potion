#include <map>
#include <iostream>

#include "../includes/tcpserver_unix.hpp"
#include "../includes/http.hpp"

void Request::parse_headers(receive_struct_t receiveStruct) {
  std::map<std::string, std::string> headers;
  std::string request_str = ""; 
  for (size_t i = 0; i < receiveStruct.bytes_read; i++) {
    char ch = static_cast<char>((*receiveStruct.buffer)[i]);
    request_str += ch;
    if(ch == '\n') {
      std::cout << i << std::endl;
    }
  }

  std::cout << request_str << std::endl;
  
  return headers;

}

