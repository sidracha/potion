
#include <unistd.h>
#include <limits.h>
#include <filesystem>
#include <string>
#include <fstream>
#include <cstddef>


#include "../include/tcpserver_unix.hpp"
#include "../include/potion.hpp"
#include "../include/request.hpp"
#include "../include/response.hpp"
#include "../include/utils.hpp"


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
  
  int read_timeout = std::get<int>(config["READ_TIMEOUT"]);
  int read_size = std::get<int>(config["READ_SIZE"]);
  int buffer_size_max = std::get<int>(config["READ_SIZE_MAX"]);
  receive_struct_t receiveStruct = server.receive(socket, read_timeout, static_cast<size_t>(read_size*KB), static_cast<size_t>(buffer_size_max));

  //receive_struct_t receiveStruct = server.receive(std::get<int>(config["READ_TIMEOUT"]), socket, std::get<int>(config["READ_SIZE"]) * KB, 5);
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

  std::string sf = std::get<std::string>(config["STATIC_FOLDER"]);
  if (sf[0] == '/') {
    sf = sf.substr(1, sf.length()-1);
  }
  response.set_static_folder(sf);

  std::string route = request.get_route();
  std::string method = request.get_method();

  
  if (is_accessory_file_request(route)) {
    routeStruct = response.serve_static_file(route);
  }
  else if (!route_map.count(route)) {
    routeStruct = response.send_status_code(404);
  }
  else if (!route_map[route].count(method)) {
    routeStruct = response.send_status_code(405);
  }
  else {
    route_handler_func_t* func = route_map[route][method];
    routeStruct = func(this, &request, &response);
  }



  server.send(routeStruct.buffer, routeStruct.buffer_size, socket);
  close_request(receiveStruct, routeStruct, socket);

  std::string req_out = "<" + method + " " + route + ">";
  std::cout << req_out << std::endl;
  //std::string static_folder = std::get<std::string>(config["STATIC_FOLDER"]);
  //int read_timeout = std::get<int>(config["READ_TIMEOUT"]);
  //std::cout << static_folder << " " << read_timeout << std::endl;
  

}
