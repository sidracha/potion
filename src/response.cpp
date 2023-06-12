#include <filesystem>
#include <fstream>

#include "../includes/response.hpp"

namespace fs = std::filesystem;

char* Response::send_string(std::string str) {

  return const_cast<char*>(str.c_str());

}

char* Response::render(std::string file_path) {
  
  fs::path path = file_path;
  fs::path p = fs::current_path() / path;
  size_t f_size = fs::file_size(p);
  
  std::string headers = 
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html"
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
  
  return buffer;
  
  

}
