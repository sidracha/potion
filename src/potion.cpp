
#include "../includes/tcpserver_unix.hpp"
#include "../includes/potion.hpp"
#include "../includes/request.hpp"

#define KB 1024




PotionApp::PotionApp(int port) : server(port) {

}

void PotionApp::print_num(int num) {
  std::cout << num << std::endl;
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
  

  receive_struct_t receiveStruct = server.receive(60, socket, 2*KB);
  
  if (receiveStruct.bytes_read == 0) {
    http_response = "HTTP/1.1 504 Gateway Timeout";
    server.send(http_response, socket);
    server.close_connection(socket);
    delete receiveStruct.buffer;
    return;
  }

  Request request(receiveStruct);
  request.parse_headers();
  
  std::string method = request.get_method();
  std::string route = request.get_route();
  

  //method = method.substr(1, method.length()-1);
  route = route.substr(0, route.length()-1);

  std::cout << route << std::endl;  
  route_handler_func_t* func;
  try {
    func = route_map[route][method];
  } catch (const std::exception& e) {
    std::cout << route << " " << method << " 404 or 405\n";
    char alt_resp[] = "HTTP/1.1 404 Not Found\r\n";
    server.send_file(alt_resp, 24, socket);
    delete receiveStruct.buffer;
    server.close_connection(socket);
    return;

  }
  
  route_struct_t routeStruct;

  routeStruct = func(this, 5); 
  server.send_file(routeStruct.buffer, routeStruct.buffer_size, socket);
  server.close_connection(socket);
  delete routeStruct.buffer;
  delete receiveStruct.buffer;
}
