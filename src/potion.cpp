
#include <unistd.h>
#include <limits.h>
#include <filesystem>
#include <string>
#include <fstream>
#include <cstddef>

#include "../includes/tcpserver_unix.hpp"
#include "../includes/potion.hpp"
#include "../includes/request.hpp"
#include "../includes/response.hpp"

#define KB 1024

namespace fs = std::filesystem;

void PotionApp::close_request(receive_struct_t receiveStruct, route_struct_t routeStruct, int socket) {
  server.close_connection(socket);
  
  if (receiveStruct.buffer != nullptr) {
    delete receiveStruct.buffer;
  }

  if (routeStruct.buffer != nullptr) {
    delete routeStruct.buffer;
  }
}


PotionApp::PotionApp(int port) : server(port) {

}

/*
void test() {

  fs::path current_file = fs::absolute(__FILE__);
  std::cout << current_file << std::endl;
  
  fs::path templates_folder = "../frontend/templates";
  fs::path path = current_file / templates_folder;
  std::string str = path.string();
  std::cout << str << std::endl;
  
  int i = last_index_of(str, '/');

  std::cout << i << std::endl;
  return;
  std::cout << path << std::endl;

  size_t fsize = fs::file_size(path);
  char buffer[fsize];
  std::ifstream file(path);
  file.read(buffer, fsize);



}

*/


void PotionApp::run () {

  //test();
  //return;
  
  ThreadPool threadPool;
  threadPool.start_threads(2, this);
  
  while (1) { //entire loop of app
    
    int socket = server.accept_connection();
    threadPool.add_job(socket);

  }

}



void PotionApp::handle_connection(int socket) {
  
  receive_struct_t receiveStruct = server.receive(60, socket, 2*KB);


  route_struct_t routeStruct;

  if (receiveStruct.bytes_read == 0) {
    std::string http_response = "HTTP/1.1 504 Gateway Timeout";
    server.send_str(http_response, socket);
    //close_request(receiveStruct, routeStruct, socket);
    delete receiveStruct.buffer;
    server.close_connection(socket);
    return;
  }

  Request request(receiveStruct);
  request.parse_headers();
  
  Response response(&request);

  
  std::string route = request.get_route();
  std::string method = request.get_method();

  if (!route_map.count(route)) {
    routeStruct = response.send_status_code(this, 404);
  }
  
  else if (!route_map[route].count(method)) {
    routeStruct = response.send_status_code(this, 405);
  }
  else if (request.is_accessory_file_request(route)) {
    routeStruct = response.serve_static_file(this, route);
  }
  else {
    route_handler_func_t* func = route_map[route][method];
    routeStruct = func(this, &request, &response);
  }

   

  server.send(routeStruct.buffer, routeStruct.buffer_size, socket);
  close_request(receiveStruct, routeStruct, socket);

  std::string req_out = "<" + method + " " + route + ">";
  //std::cout << req_out << std::endl;
  std::string static_folder = std::get<std::string>(config["STATIC_FOLDER"]);
  int read_timeout = std::get<int>(config["READ_TIMEOUT"]);
  std::cout << static_folder << " " << read_timeout << std::endl;
}
