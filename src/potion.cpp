
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
  std::string method = request.get_method();

  route_handler_func_t* func = route_map["/"]["GET"];
  func(this, 5);
  


  server.send(http_response, socket);
  
  delete receiveStruct.buffer;
}
