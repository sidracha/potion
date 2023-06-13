
#include "../includes/tcpserver_unix.hpp"
#include "../includes/potion.hpp"
#include "../includes/request.hpp"
#include "../includes/response.hpp"

#define KB 1024

void PotionApp::close_request(receive_struct_t receiveStruct, route_struct_t routeStruct, int socket) {
  server.close_connection(socket);
  
  if (routeStruct.buffer == NULL) {
  }

  if (receiveStruct.buffer != NULL) {
    delete receiveStruct.buffer;
  }

  if (routeStruct.buffer != NULL) {
    delete routeStruct.buffer;
  }
}



PotionApp::PotionApp(int port) : server(port) {

}

void PotionApp::print_num(int num) {
}

void PotionApp::run () {
  
  ThreadPool threadPool;
  threadPool.start_threads(10, this);
  
  while (1) { //entire loop of app
    
    int socket = server.accept_connection();
    threadPool.add_job(socket);

  }

}


void PotionApp::handle_request(int socket) {
  
    std::string html_body = "<html><body><h1>Hello, World!</h1></body></html>";

    std::string http_response =
      "HTTP/1.1 200 OK\n"
      "Content-Type: text/html\n"
      "Content-Length: " + std::to_string(html_body.length()) + "\n"
      "\n" +
      html_body + "\n"; 
  

  receive_struct_t receiveStruct = server.receive(10, socket, 2*KB);
  


  route_struct_t routeStruct;

  if (receiveStruct.bytes_read == 0) {
    http_response = "HTTP/1.1 504 Gateway Timeout";
    server.send_str(http_response, socket);
    close_request(receiveStruct, routeStruct, socket);
    return;
  }

  Request request(receiveStruct);
  request.parse_headers();
  
  std::string method = request.get_method();
  std::string route = request.get_route();
  
  std::cout << method << " " << route << std::endl;
  
  if (!route_map.count(route)) {
    routeStruct = send_status_code(404);
    server.send(routeStruct.buffer, routeStruct.buffer_size, socket);
    close_request(receiveStruct, routeStruct, socket);
    return;
  }
  if (!route_map[route].count(method)) {
    routeStruct = send_status_code(405);
    server.send(routeStruct.buffer, routeStruct.buffer_size, socket);
    close_request(receiveStruct, routeStruct, socket);
    return;
  }
  route_handler_func_t* func = route_map[route][method];
  routeStruct = func(this, 5);
  
  server.send(routeStruct.buffer, routeStruct.buffer_size, socket);
    
  close_request(receiveStruct, routeStruct, socket);
}
