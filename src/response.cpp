#include <filesystem>
#include <fstream>
#include <iostream>

#include "../includes/response.hpp"
#include "../includes/request.hpp"

namespace fs = std::filesystem;


Response::Response(Request* r) : request(r) {

}

inline char* Response::string_to_char(std::string str, char* buffer) {
   
  str.copy(buffer, str.length());
  return buffer;
}

inline void Response::error(std::string msg) {
  throw std::runtime_error(msg);
}


route_struct_t Response::send_string(PotionApp* app, std::string str) {
  
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

route_struct_t Response::render(PotionApp* app, std::string file_path) {
  fs::path path = file_path;
  fs::path p = fs::current_path() / path;
  size_t f_size = fs::file_size(p);
  
  std::string headers = 
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: " + std::to_string(f_size) + "\r\n"
    "Accept-Ranges: bytes\r\n"
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


route_struct_t Response::send_status_code(PotionApp* app, uint16_t status_code) {
  
  //for now only 404 and 405 supported add later
  //add enum class later
  
  std::string status_404 = "HTTP/1.1 404 Not Found\r\n";
  std::string status_405 = "HTTP/1.1 405 Method Not Allowed\r\n";
  
  route_struct_t routeStruct;
  switch (status_code) {
      
    case 404: {
              
      char* buffer = new char[status_404.length()];
      string_to_char(status_404, buffer);
      routeStruct.buffer = buffer;
      routeStruct.buffer_size = status_404.length();
      break;
    }
    case 405: {
              
      char* buffer = new char[status_405.length()];
      string_to_char(status_405, buffer);
      routeStruct.buffer = buffer;
      routeStruct.buffer_size = status_405.length();
      break;
    }
    
    default: {
      error("Invalid status code return");
    }
  }

  return routeStruct;

}

route_struct_t Response::send_file(PotionApp* app, std::string file_path) {
  

  fs::path path = file_path;
  fs::path p = fs::current_path() / path;
  size_t f_size = fs::file_size(p);

  std::string http_response = 
    "HTTP/1.1 206 Partial Content\r\n"
    "Content-Type: video/mp4\r\n"
    "Content-Length: " + std::to_string(100) + "\r\n"
    "Accept-Ranges: bytes\r\n"
    "\r\n";


  size_t header_len = http_response.length();
  //size_t buffer_size = header_len + f_size;
  size_t buffer_size = 100 + header_len;
  char* buffer = new char[buffer_size];
  
  for (size_t i = 0; i < header_len; i++) {
    buffer[i] = http_response[i];
  }
  std::ifstream file(p);

  file.read(buffer + header_len, 100);
  route_struct_t routeStruct;
  routeStruct.buffer = buffer;
  routeStruct.buffer_size = buffer_size;
  return routeStruct;
  
}


//route_struct_t send_js_file(PotionApp* app, std::string file_path) {
//}
