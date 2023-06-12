#include <filesystem>
#include <fstream>
#include <iostream>

#include "../includes/response.hpp"

namespace fs = std::filesystem;

route_struct_t send_string(std::string str) {
  
  std::string headers = 
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/plain\r\n"
    "\r\n";

  route_struct_t routeStruct;
  char* buffer = new char[str.length() + headers.length()];
  for (size_t i = 0; i < headers.length(); i++) {
    buffer[i] = headers[i];
  }
  std::cout << str << std::endl;
  for (size_t i = 0; i < str.length(); i++) {
    buffer[i+headers.length()] = str[i];
  }
  
  routeStruct.buffer = buffer;
  routeStruct.buffer_size = str.length() + headers.length();
  return routeStruct;

}

route_struct_t render(std::string file_path) {
  std::cout << "hello\n"; 
  fs::path path = file_path;
  fs::path p = fs::current_path() / path;
  size_t f_size = fs::file_size(p);
  
  std::string headers = 
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: " + std::to_string(f_size) + "\r\n"
    "\r\n";
  
  size_t header_len = headers.length();
  size_t buffer_size = f_size + header_len;

  char* buffer = new char[buffer_size];
  
  for (size_t i = 0; i < header_len; i++) {
    buffer[i] = headers[i];
  }

  std::ifstream file(p);
  file.read(buffer + header_len, f_size);

  route_struct_t routeStruct;
  routeStruct.buffer = buffer;
  routeStruct.buffer_size = buffer_size;
  return routeStruct;
}
