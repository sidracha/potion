#include <map>
#include <iostream>
#include <bitset>

#include "../includes/tcpserver_unix.hpp"
#include "../includes/request.hpp"


void Request::parse_headers() {
  
  std::string method = "";
  std::string request_str = "";
  std::string route = "";

  size_t line = 0;
  bool found_method = false;
  bool on_route = false;

  for (size_t i = 0; i < receiveStruct.bytes_read; i++) {
    
    std::byte bt = (*receiveStruct.buffer)[i];
    char character = static_cast<char>(bt);
    request_str += character;
    if (on_route) {
      route += character;
    }

    if (line == 0 && character == ' ' && request_str != "") {

      if (!found_method) {
        header_map["method"] = request_str.substr(0, request_str.length()-1);
        found_method = true;
        on_route = true;
      }
      else {
        on_route = false;
        header_map["route"] = route;
      }
    }
      
      
  }
  std::cout << method << std::endl;
  std::cout << route << std::endl;


}


  
  

std::string Request::get_method () { //returns first word of request
  return header_map["method"];
}

std::string Request::get_route () {
  return header_map["route"];
}
