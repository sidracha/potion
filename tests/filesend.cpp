#include "../includes/tcpserver_unix.hpp"
#include <filesystem>
#include <cstddef>
#include <fstream>


namespace fs = std::filesystem;

int main () {


  fs::path path = "catimg.jpeg";
  fs::path p = fs::current_path() / path;

  size_t f_size = fs::file_size(p);
  std::cout << f_size << std::endl;
  
  //std::string html_body = "<html><body><h1>Hello, World!</h1></body></html>";

  std::string http_response =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/plain; charset=UTF-8\r\n"
    "Content-Length: " + std::to_string(f_size) + "\r\n"
    "\r\n";
  size_t resp_len = http_response.length();
  size_t buffer_size = resp_len + f_size;
  char buffer[buffer_size];

  for (size_t i = 0; i < resp_len; i++) {
    buffer[i] = http_response[i];
  }

  std::ifstream file(p);

  file.read(buffer + resp_len, f_size);

  TCPServer server(8080);
  int socket = server.accept_connection();
  receive_struct_t receiveStruct = server.receive(60, socket, 1024);
  
  //for (size_t i = 0; i < (*receiveStruct.buffer).size(); i++) {
    //std::cout << static_cast<char>((*receiveStruct.buffer)[i]);
  //}

  server.send_file(buffer, buffer_size, socket);




  return 0;
  
}
