#include <map>
#include <iostream>
#include <cstdlib>

#include "potion.hpp"
#include "tcpserver_unix.hpp"

void PotionApp::set_route (std::string route, route_handler_func_t* func) {
  function_map[route] = func;
}

int PotionApp::execute_function (std::string route) {
  auto func = function_map[route];
  int result = func(5);
  return result;
}

void PotionApp::run () {
  int port = 8080;
      
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
  std::string data;
  TCPServer server(port);
  while (1) {
    server.acceptConnection();
    data = server.receive();
    std::cout << data << std::endl;
    server.send(httpResponse);
    server.closeConnection();
  }

}
