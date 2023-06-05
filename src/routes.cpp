#include <map>
#include <iostream>
#include <cstdlib>
#include <map>

#include "../includes/routes.hpp"
#include "../includes/tcpserver_unix.hpp"
#include "../includes/http.hpp"



void RoutingContainer::handle_request(int socket, TCPServer* server) {

  std::string httpResponse = R"(HTTP/1.1 200 OK
  Content-Type: text/html; charset=utf-8
  Content-Length: 55743
  Connection: keep-alive
  Cache-Control: s-maxage=300, public, max-age=0
  Content-Language: en-US
  Date: Thu, 06 Dec 2018 17:37:18 GMT
  ETag: "2e77ad1dc6ab0b53a2996dfd4653c1c3"
  Server: meinheld/0.6.1
  Strict-Transport-Security: max-age=63072000
  X-Content-Type-Options: nosniff
  X-Frame-Options: DENY
  X-XSS-Protection: 1; mode=block
  Vary: Accept-Encoding,Cookie
  Age: 7

  <!DOCTYPE html>
  <html lang="en">
  <head>
  <meta charset="utf-8">
  <title>A simple webpage</title>
  </head>
  <body>
  <h1>Simple HTML webpage</h1>
  <p>Hello, world!</p>
  </body>
  </html>
  )";
  receive_struct_t receiveStruct = server->receive(60, socket, 1028);
  if (receiveStruct.bytes_read == 0) {
    std::string alt_response = "HTTP/1.1 504 Gateway Timeout";
    server->send(alt_response, socket);
    server->close_connection(socket);
    delete receiveStruct.buffer;
    return;
  }
  //server->send(httpResponse, socket);
  
  Request request(receiveStruct);
  std::string method = request.get_method();
  route_handler_func_t* func = route_map["/"]["GET"];
  func(5);
  server->send(httpResponse, socket);


  server->close_connection(socket);


  delete receiveStruct.buffer;
}

void RoutingContainer::set_route(std::string route, route_handler_func_t* func, std::string method) {
  
  if (route_map[route].count(method)) { //key exists
    throw std::runtime_error("Muliple route definitions: " + method + " " + route);
  }

  route_map[route][method]= func;


}









